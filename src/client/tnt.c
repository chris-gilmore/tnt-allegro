#include "common.h"
#include <getopt.h>
#include <time.h>
#include <dirent.h>

// dnf: libconfig-devel
// apt: libconfig-dev
#include <libconfig.h>

// dnf: allegro5-devel
// apt: liballegro5-dev
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// dnf: allegro5-addon-image-devel
// apt: liballegro-image5-dev
#include <allegro5/allegro_image.h>

// dnf: allegro5-addon-ttf-devel
// apt: liballegro-ttf5-dev
//#include <allegro5/allegro_ttf.h>

// dnf: enet-devel
// apt: libenet-dev
#include <enet/enet.h>
#include "enet_common.h"

static FILE *fp;
static int record = false;
static int replay = false;
static bool save_frames = false;
static char *frames_dir = NULL;
static unsigned int framecount = 0;
int ringcount = 0;
unsigned int game_id = 0;
static unsigned char g_opponent = 0;
static unsigned int gametype = GAMETYPE_MARATHON;
static unsigned int landfilltype = LANDFILLTYPE_NONE;
char p0_name[9] = "PLAYER 0";
char p1_name[9] = "PLAYER 1";
char p2_name[9] = "PLAYER 2";
char p3_name[9] = "PLAYER 3";
static ENetHost *client;
static ENetPeer *server;
static int net_flag = false;
static int lag_flag = false;
static int intro_flag = false;
static int haluci_flag = false;
static unsigned int currentPieceFrames = 0;
int verbose_flag = false;
int g_screen = -1;
config_t g_images_cfg;
config_t g_anims_cfg;
config_t g_effects_cfg;

static void print_joystick_info(int i) {
  ALLEGRO_JOYSTICK *joy = al_get_joystick(i);
  int n;

  if (!joy)
    return;

  printf("Joystick[%d]: '%s'\n", i, al_get_joystick_name(joy));

  printf("  Buttons:");
  n = al_get_joystick_num_buttons(joy);
  for (int j = 0; j < n; j++) {
    printf(" '%s'", al_get_joystick_button_name(joy, j));
  }
  printf("\n");

  n = al_get_joystick_num_sticks(joy);
  for (int j = 0; j < n; j++) {
    printf("  Stick[%d]: '%s'\n", j, al_get_joystick_stick_name(joy, j));

    for (int a = 0; a < al_get_joystick_num_axes(joy, j); a++) {
      printf("    Axis[%d]: '%s'\n", a, al_get_joystick_axis_name(joy, j, a));
    }
  }
}

void must_init(bool test, const char *description) {
  if (test) return;

  printf("couldn't initialize %s\n", description);
  exit(EXIT_FAILURE);
}


// Enet stuff

static ENetHost *create_client(void) {
  ENetHost *client;

  client = enet_host_create(NULL /* create a client host */,
                            1    /* only allow 1 outgoing connection */,
                            2    /* allow up to 2 channels to be used, 0 and 1 */,
                            0    /* assume any amount of incoming bandwidth */,
                            0    /* assume any amount of outgoing bandwidth */);
  // 57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
  // 14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);

  if (client == NULL) {
    fprintf(stderr, "An error occurred while trying to create an ENet client host\n");
    exit(EXIT_FAILURE);
  }

  return client;
}

static ENetPeer *connect_client(ENetHost *client, char *host, int port) {
  ENetAddress address;
  ENetEvent event;
  ENetPeer *server;

  enet_address_set_host(&address, host);
  address.port = port;

  /* Initiate the connection, allocating the two channels 0 and 1. */
  server = enet_host_connect(client, &address, 2, 0);
  if (server == NULL) {
    fprintf(stderr, "Client: no available peers for initiating an ENet connection\n");
    exit(EXIT_FAILURE);
  }

  /* Wait up to 5 seconds for the connection attempt to succeed. */
  if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT) {
    printf("Client: connected to %x:%u\n", event.peer->address.host, event.peer->address.port);
  } else {
    /* Either the 5 seconds are up or a disconnect event was */
    /* received.  Reset the peer in the event the 5 seconds  */
    /* had run out without any significant event.            */
    enet_peer_reset(server);
    fprintf(stderr, "Client: connection to server failed\n");
    exit(EXIT_FAILURE);
  }

  return server;
}

static void disconnect_client(ENetHost *client, ENetPeer *server) {
  ENetEvent event;

  enet_peer_disconnect(server, 0);

  while (enet_host_service(client, &event, 3000) > 0) {
    switch (event.type) {
    case ENET_EVENT_TYPE_RECEIVE:
      // drop any packets received
      enet_packet_destroy(event.packet);
      break;
    case ENET_EVENT_TYPE_DISCONNECT:
      printf("Client: disconnection from server succeeded\n");
      return;
    }
  }

  // failed to disconnect gracefully, force the connection closed
  enet_peer_reset(server);
}


// Display stuff

#define BUFFER_W 400
#define BUFFER_H 300

s32 screen_1_width = BUFFER_W;
s32 screen_1_height = BUFFER_H;

//#define DISP_W 800
//#define DISP_H 600
#define DISP_W 960
#define DISP_H 720

static ALLEGRO_DISPLAY *disp;
static ALLEGRO_BITMAP *cfbuffer;

static void disp_init(void) {
  al_add_new_bitmap_flag(ALLEGRO_NO_PRESERVE_TEXTURE);

  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  disp = al_create_display(DISP_W, DISP_H);
  must_init(disp, "display");

  cfbuffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  must_init(cfbuffer, "bitmap buffer");

  al_init_image_addon();
}

static void disp_deinit(void) {
  al_destroy_bitmap(cfbuffer);
  al_destroy_display(disp);
}

static void disp_pre_draw(void) {
  al_set_target_bitmap(cfbuffer);
}

static void disp_post_draw(void) {
  static char filename[256];
  static unsigned int last_framecount = 0;

  al_set_target_backbuffer(disp);
  al_draw_scaled_bitmap(cfbuffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

  if (save_frames) {
    while (last_framecount < framecount) {
      if (lag_flag) {
        last_framecount += 2;
      } else {
        last_framecount++;
      }
      snprintf(filename, sizeof(filename), "%s/image-%08d.png", frames_dir, last_framecount);
      al_save_bitmap(filename, al_get_backbuffer(disp));
    }
  }

  al_flip_display();
}


// Keyboard stuff

#define KEY_SEEN     1
#define KEY_RELEASED 2
static unsigned char key[ALLEGRO_KEY_MAX];

static void keyboard_init(void) {
  memset(key, 0, sizeof(key));
}

static void keyboard_update(ALLEGRO_EVENT* event) {
  switch(event->type) {
  case ALLEGRO_EVENT_TIMER:
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++)
      key[i] &= KEY_SEEN;
    break;
  case ALLEGRO_EVENT_KEY_DOWN:
    key[event->keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
    break;
  case ALLEGRO_EVENT_KEY_UP:
    key[event->keyboard.keycode] &= KEY_RELEASED;
    break;
  }
}


// Joystick stuff

typedef struct {
  u8 btn_a;
  u8 btn_b;
  u8 trig_l;
  u8 trig_r;
  u8 trig_z;
  u8 btn_start;
  bool dpad_as_stick;
  u8 dpad_stick_idx;
  u8 dpad_btn_l;
  u8 dpad_btn_r;
  u8 dpad_btn_u;
  u8 dpad_btn_d;
  bool cbtns_as_stick;
  u8 cbtns_stick_idx;
  u8 cbtns_btn_l;
  u8 cbtns_btn_r;
  u8 cbtns_btn_u;
  u8 cbtns_btn_d;
} CtrlCfg;

CtrlCfg ctrlCfg[4];

void joystick_init(int i) {
  ALLEGRO_JOYSTICK *joy = al_get_joystick(i);

  print_joystick_info(i);

  if (!joy)
    return;

  if (strcmp(al_get_joystick_name(joy), "ShanWan     Hyperkin Adapter") == 0) {
    // N64 controller
    ctrlCfg[i].btn_a = 1;
    ctrlCfg[i].btn_b = 2;
    ctrlCfg[i].trig_l = 4;
    ctrlCfg[i].trig_r = 5;
    ctrlCfg[i].trig_z = 6;
    ctrlCfg[i].btn_start = 9;
    ctrlCfg[i].dpad_as_stick = true;
    ctrlCfg[i].dpad_stick_idx = 2;
    ctrlCfg[i].cbtns_as_stick = true;
    ctrlCfg[i].cbtns_stick_idx = 1;
  } else if (strcmp(al_get_joystick_name(joy), "USB,2-axis 8-button gamepad  ") == 0) {
    // iBuffalo classic usb gamepad
    ctrlCfg[i].btn_a = 1;
    ctrlCfg[i].btn_b = 3;
    ctrlCfg[i].trig_l = 4;
    ctrlCfg[i].trig_r = 5;
    ctrlCfg[i].trig_z = 6;
    ctrlCfg[i].btn_start = 7;
    ctrlCfg[i].dpad_as_stick = true;
    ctrlCfg[i].dpad_stick_idx = 0;
    ctrlCfg[i].cbtns_as_stick = false;
    ctrlCfg[i].cbtns_btn_l = 2;
    ctrlCfg[i].cbtns_btn_r = 0;
  } else if (strcmp(al_get_joystick_name(joy), "8Bitdo FC30 Pro    8Bitdo FC30 Pro") == 0) {
    // 8Bitdo
    ctrlCfg[i].btn_a = 1;
    ctrlCfg[i].btn_b = 4;
    ctrlCfg[i].trig_l = 8;
    ctrlCfg[i].trig_r = 9;
    ctrlCfg[i].trig_z = 10;
    ctrlCfg[i].btn_start = 11;
    ctrlCfg[i].dpad_as_stick = true;
    ctrlCfg[i].dpad_stick_idx = 4;
  } else if (strcmp(al_get_joystick_name(joy), "Sony Interactive Entertainment Wireless Controller") == 0) {
    // PS4 controller over usb
    ctrlCfg[i].btn_a = 0;     // square button
    ctrlCfg[i].btn_b = 3;     // X button
    ctrlCfg[i].trig_l = 4;    // L1 trigger
    ctrlCfg[i].trig_r = 5;    // R1 trigger
    ctrlCfg[i].trig_z = 12;   // right analog stick button
    ctrlCfg[i].btn_start = 9; // options button
    ctrlCfg[i].dpad_as_stick = true;
    ctrlCfg[i].dpad_stick_idx = 3; // dpad
    ctrlCfg[i].cbtns_as_stick = false;
    ctrlCfg[i].cbtns_btn_l = 2;
    ctrlCfg[i].cbtns_btn_r = 1;
  } else if (strcmp(al_get_joystick_name(joy), "Microsoft X-Box 360 pad") == 0) {
    // Generic brand Nintendo Switch controller over usb (shows up as X-Box 360?)
    ctrlCfg[i].btn_a = 0;     // B button
    ctrlCfg[i].btn_b = 2;     // Y button
    ctrlCfg[i].trig_l = 4;    // L1 trigger
    ctrlCfg[i].trig_r = 5;    // R1 trigger
    ctrlCfg[i].trig_z = 10;   // right analog stick button
    ctrlCfg[i].btn_start = 8; // home button
    ctrlCfg[i].dpad_as_stick = true;
    ctrlCfg[i].dpad_stick_idx = 3; // dpad
  } else if (strcmp(al_get_joystick_name(joy), "SealieComputing N64 RetroPort") == 0) {
    // RetroUSB N64 usb adapter, dpad registers as 4 distinct buttons rather than a stick with axes
    ctrlCfg[i].btn_a = 7;
    ctrlCfg[i].btn_b = 6;
    ctrlCfg[i].trig_l = 13;
    ctrlCfg[i].trig_r = 12;
    ctrlCfg[i].trig_z = 5;
    ctrlCfg[i].btn_start = 4;
    ctrlCfg[i].dpad_as_stick = false;
    ctrlCfg[i].dpad_btn_l = 1;
    ctrlCfg[i].dpad_btn_r = 0;
    ctrlCfg[i].dpad_btn_u = 3;
    ctrlCfg[i].dpad_btn_d = 2;
  } else if (strcmp(al_get_joystick_name(joy), "Microsoft X-Box 360 pad 0") == 0) {
    // Steam Deck (shows up as X-Box 360 pad 0)
    ctrlCfg[i].btn_a = 0;     // clockwise rotation
    ctrlCfg[i].btn_b = 1;     // counter-clockwise rotation
    ctrlCfg[i].trig_l = 4;    // hold
    ctrlCfg[i].trig_r = 5;    // xswap
    ctrlCfg[i].trig_z = 3;    // not implemented
    ctrlCfg[i].btn_start = 7; // start
    ctrlCfg[i].dpad_as_stick = true;
    ctrlCfg[i].dpad_stick_idx = 3;
  }
}

void joystick_update(ALLEGRO_EVENT* event) {
  switch(event->type) {
  case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
    al_reconfigure_joysticks();
    for (int i = 0; i < 4; i++) {
      joystick_init(i);
    }
    break;
  }
}


// HUD stuff

ALLEGRO_FONT *hud_font;

void hud_init(void) {
  hud_font = al_create_builtin_font();
  /*
  al_init_ttf_addon();
  // https://www.dafont.com/rollerball-1975.font
  hud_font = al_load_ttf_font("rollerball_1975.ttf", 12, ALLEGRO_TTF_MONOCHROME);
  */
  must_init(hud_font, "hud_font");
}

void hud_deinit(void) {
  al_destroy_font(hud_font);
}

void hud_draw(void) {
  if (D_800CFEE8 == 13) {
    al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 3, 3, 0, "FrameCount: %u, RingCount: %d", framecount, ringcount);
    //} else if (D_800CFEE8 == 9 || D_800CFEE8 == 11) {
    //al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 3, 3, 0, "FrameCount: %u, Current piece frames: %u", framecount, currentPieceFrames);
  } else {
    al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 3, 3, 0, "FrameCount: %u", framecount);
  }
}


// ContPad stuff

void snapshot_contpad(int i, OSContPad *contpad) {
  ALLEGRO_JOYSTICK_STATE jst;
  ALLEGRO_JOYSTICK *joy = al_get_joystick(i);

  if (!joy) {
    return;
  }

  al_get_joystick_state(joy, &jst);

  /*
  printf("\n");
  for (int j = 0; j < al_get_joystick_num_buttons(joy); j++) {
    printf("%d: jst.button[%d] = %d\n", i, j, jst.button[j]);
  }
  for (int k = 0; k < al_get_joystick_num_sticks(joy); k++) {
    for (int j = 0; j < al_get_joystick_num_axes(joy, k); j++) {
      printf("%d: jst.stick[%d].axis[%d] = %f\n", i, k, j, jst.stick[k].axis[j]);
    }
  }
  */

  if (jst.button[ctrlCfg[i].btn_a]     >= 16384) contpad->button |= 0x8000;  // A_BUTTON     / CONT_A
  if (jst.button[ctrlCfg[i].btn_b]     >= 16384) contpad->button |= 0x4000;  // B_BUTTON     / CONT_B
  if (jst.button[ctrlCfg[i].trig_l]    >= 16384) contpad->button |= 0x0020;  // L_TRIG       / CONT_L
  if (jst.button[ctrlCfg[i].trig_r]    >= 16384) contpad->button |= 0x0010;  // R_TRIG       / CONT_R
  if (jst.button[ctrlCfg[i].trig_z]    >= 16384) contpad->button |= 0x2000;  // Z_TRIG       / CONT_G
  if (jst.button[ctrlCfg[i].btn_start] >= 16384) contpad->button |= 0x1000;  // START_BUTTON / CONT_START

  if (ctrlCfg[i].dpad_as_stick) {
    if (jst.stick[ctrlCfg[i].dpad_stick_idx].axis[0] < -0.5)      contpad->button |= 0x0200;  // L_JPAD / CONT_LEFT
    else if (jst.stick[ctrlCfg[i].dpad_stick_idx].axis[0] > 0.5) contpad->button |= 0x0100;  // R_JPAD / CONT_RIGHT
    if (jst.stick[ctrlCfg[i].dpad_stick_idx].axis[1] < -0.5)      contpad->button |= 0x0800;  // U_JPAD / CONT_UP
    else if (jst.stick[ctrlCfg[i].dpad_stick_idx].axis[1] > 0.5) contpad->button |= 0x0400;  // D_JPAD / CONT_DOWN
  } else {
    if (jst.button[ctrlCfg[i].dpad_btn_l] >= 16384)      contpad->button |= 0x0200;  // L_JPAD / CONT_LEFT
    else if (jst.button[ctrlCfg[i].dpad_btn_r] >= 16384) contpad->button |= 0x0100;  // R_JPAD / CONT_RIGHT
    if (jst.button[ctrlCfg[i].dpad_btn_u] >= 16384)      contpad->button |= 0x0800;  // U_JPAD / CONT_UP
    else if (jst.button[ctrlCfg[i].dpad_btn_d] >= 16384) contpad->button |= 0x0400;  // D_JPAD / CONT_DOWN
  }

  if (ctrlCfg[i].cbtns_as_stick) {
    if (jst.stick[ctrlCfg[i].cbtns_stick_idx].axis[0] < -0.5)      contpad->button |= 0x0002;  // L_CBUTTONS / CONT_C
    else if (jst.stick[ctrlCfg[i].cbtns_stick_idx].axis[0] > 0.5) contpad->button |= 0x0001;  // R_CBUTTONS / CONT_F
    if (jst.stick[ctrlCfg[i].cbtns_stick_idx].axis[1] < -0.5)      contpad->button |= 0x0008;  // U_CBUTTONS / CONT_E
    else if (jst.stick[ctrlCfg[i].cbtns_stick_idx].axis[1] > 0.5) contpad->button |= 0x0004;  // D_CBUTTONS / CONT_D
  } else {
    if (jst.button[ctrlCfg[i].cbtns_btn_l] >= 16384)      contpad->button |= 0x0002;  // L_CBUTTONS / CONT_C
    else if (jst.button[ctrlCfg[i].cbtns_btn_r] >= 16384) contpad->button |= 0x0001;  // R_CBUTTONS / CONT_F
    if (jst.button[ctrlCfg[i].cbtns_btn_u] >= 16384)      contpad->button |= 0x0008;  // U_CBUTTONS / CONT_E
    else if (jst.button[ctrlCfg[i].cbtns_btn_d] >= 16384) contpad->button |= 0x0004;  // D_CBUTTONS / CONT_D
  }
}

void print_contpad(int i, OSContPad *contpad) {
  printf("[%d] contpad.button = %016b\n", i, contpad->button);
}

static ControllerQueue *controller_queues[4];

void contq_dequeue(void) {
  // From 010870.c, FUN_010870_interesting_stuff_large_liner()
  while (func_800A3534(&g_PV_ptr->contQ) != 0) {
    func_800A33E4(&g_PV_ptr->contQ);
  }
  g_PV_ptr->unk1C = g_PV_ptr->contQ.unk14;
  g_PV_ptr->unk24 = (g_PV_ptr->unk20 ^ -1) & g_PV_ptr->unk1C->unk0;
  g_PV_ptr->unk20 = g_PV_ptr->unk1C->unk0;

  // check button A
  //printf("%d\n", g_PV_ptr->contQ.unk14->unk40);
  // check left trigger
  //printf("%d\n", g_PV_ptr->contQ.unk14->unk2C);
}

static bool send_receive(ENetHost *client) {
  ENetEvent event;
  ServerMessage *msg;
  OSContPad contpad;
  static unsigned int frmcnt = 0;
  static unsigned int record_framecount = 0;
  bool draw_flag = false;
  static bool in_lobby = true;
  unsigned char num_ready_players;

  while (enet_host_service(client, &event, 0) > 0) {
    if (event.type == ENET_EVENT_TYPE_RECEIVE) {
      msg = (ServerMessage*)event.packet->data;

      if (record && !in_lobby) {
        if (lag_flag) {
          record_framecount += 2;
        } else {
          record_framecount++;
        }
        fprintf(fp, "%u", record_framecount);
      }
      for (int i = 0; i < MAX_PLAYER_COUNT; i++) {
        contpad.button = msg->button[i];
        //printf("Player %d button: %u\n", i, contpad.button);

        if (record && !in_lobby) {
          fprintf(fp, " %u", contpad.button);
        }

        FUN_069580_800A3300_nineliner_mod300(controller_queues[i], &contpad);
      }
      if (record && !in_lobby) {
        fprintf(fp, "\n");

        fprintf(fp, "%u %u %u %u %u\n", 0, 0, 0, 0, 0);
      }

      enet_packet_destroy(event.packet);

      if (lag_flag) {
        frmcnt += 2;
      } else {
        frmcnt++;
      }
      frametime_update(frmcnt);
      for (int i = 0; i < 4; i++) {
        g_PV_ptr = &g_PV_arr[i];
        contq_dequeue();
      }

      if (in_lobby) {
        num_ready_players = 0;
        for (int i = 0; i < 4; i++) {
          g_PV_ptr = &g_PV_arr[i];
          if (g_PV_ptr->unk1C->unk34 != 0) {  // Z_TRIG / CONT_G
            num_ready_players++;
          }
        }
        if (num_ready_players >= D_800CFED4) {
          func_80090E08();
          in_lobby = false;
        }
      } else {
        D_801109F4 = frametime_delta();
        Game_line_782_game_c(&g_game);
        draw_flag = true;
      }
    }
  }
  return draw_flag;
}

static bool contq_enqueue(void) {
  OSContPad contpad;

  contpad.button = 0x0000;

  if (key[ALLEGRO_KEY_D])     contpad.button |= 0x8000;  // A_BUTTON     / CONT_A
  if (key[ALLEGRO_KEY_S])     contpad.button |= 0x4000;  // B_BUTTON     / CONT_B
  if (key[ALLEGRO_KEY_Q])     contpad.button |= 0x0020;  // L_TRIG       / CONT_L
  if (key[ALLEGRO_KEY_E])     contpad.button |= 0x0010;  // R_TRIG       / CONT_R
  if (key[ALLEGRO_KEY_W])     contpad.button |= 0x2000;  // Z_TRIG       / CONT_G
  if (key[ALLEGRO_KEY_ENTER]) contpad.button |= 0x1000;  // START_BUTTON / CONT_START

  if (key[ALLEGRO_KEY_J])     contpad.button |= 0x0200;  // L_JPAD       / CONT_LEFT
  if (key[ALLEGRO_KEY_L])     contpad.button |= 0x0100;  // R_JPAD       / CONT_RIGHT
  if (key[ALLEGRO_KEY_I])     contpad.button |= 0x0800;  // U_JPAD       / CONT_UP
  if (key[ALLEGRO_KEY_K])     contpad.button |= 0x0400;  // D_JPAD       / CONT_DOWN

  if (key[ALLEGRO_KEY_A])     contpad.button |= 0x0002;  // L_CBUTTONS   / CONT_C
  if (key[ALLEGRO_KEY_F])     contpad.button |= 0x0001;  // R_CBUTTONS   / CONT_F

  if (net_flag) {
    snapshot_contpad(0, &contpad);

    //print_contpad(0, &contpad);

    ClientMessage msg = { .seq_no = framecount, .button = contpad.button };
    ENetPacket *packet = enet_packet_create(&msg, sizeof(msg), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(server, 0, packet);
    return send_receive(client);
  } else {
    if (record) {
      fprintf(fp, "%u", framecount);
    }
    //for (int i = 0; i < 4; i++) {
    for (int i = 0; i < D_800CFED4; i++) {
      //if (i == 1 || i == 2) {  // 4TEST
      snapshot_contpad(i, &contpad);
      //}

      //print_contpad(i, &contpad);

      if (record) {
        fprintf(fp, " %u", contpad.button);
      }

      FUN_069580_800A3300_nineliner_mod300(controller_queues[i], &contpad);

      contpad.button = 0x0000;
    }
    if (record) {
      fprintf(fp, "\n");
    }
    return true;
  }
}

static char line[200];
static unsigned int frmcnt = 0;
static unsigned int button[4] = { 0, 0, 0, 0 };

static bool replay_contq_enqueue(bool *done_ptr) {
  OSContPad contpad;

  //for (int i = 0; i < 4; i++) {
  for (int i = 0; i < D_800CFED4; i++) {
    contpad.button = button[i];
    FUN_069580_800A3300_nineliner_mod300(controller_queues[i], &contpad);
  }

  if (!fgets(line, sizeof(line), fp)) {
    *done_ptr = true;
    return false;
  }

  sscanf(line, "%u %u %u %u %u", &frmcnt, &button[0], &button[1], &button[2], &button[3]);
  if (frmcnt == 0) {
    if (fgets(line, sizeof(line), fp)) {
      sscanf(line, "%u %u %u %u %u", &frmcnt, &button[0], &button[1], &button[2], &button[3]);
    } else {
      *done_ptr = true;
    }
    return true;
  } else {
    return false;
  }
}


// Player stuff

void player_init(void) {
  s16 i;

  // From bootmain.c, main_another_but_diff_400x300()
  func_800A9E44(NULL, NULL);  // init fx
  FUN_80053538_fiveliner();
  FUN_80053500_fiveliner();
  //inits_bunch_of_stuff_q_allocs_heap();
  for (i = 0; i < 4; i++) {
    g_PV_ptr = &g_PV_arr[i];
    FUN_069580_800A34A8_tenliner_allocs_heap(&g_PV_ptr->contQ);  // init contpad buttons and controller queue
    PV_set_controller_no(i);
  }
  for (i = 0; i < 4; i++) {
    controller_queues[i] = &g_PV_arr[i].contQ;
  }
  //createSuperThread(&superThread, &scheduler, controller_queues, 4);
  //FUN_001500_motorInit(&superThread);
  //FUN_001050_Create_and_Start_ControllerThread(&superThread, 5, 11);
  Audio_InitAudio();

  // From bootmain.c, main_infinite_loop_at_end_3()
  load_from_sram(FALSE);

  wonders2_80045e50_sets_num_won_compl_q();  // TODO
}

void player_deinit(void) {
  s16 i;
  ControllerQueue *contQ_ptr;

  for (i = 0; i < 4; i++) {
    contQ_ptr = controller_queues[i];
    n64HeapUnalloc(contQ_ptr->unk14);
    n64HeapUnalloc(contQ_ptr->_ControllerQueue);
  }

  func_800AA514();  // deinit fx
}


// Game stuff

void game_init(unsigned short num_players) {
  register Game *game_ptr = &g_game;
  static const char *gametype_str[] = { "Marathon", "Sprint", "Ultra" };
  static const char *landfilltype_str[] = { "None", "HotPotato", "Directed" };
  static const char *opponent_str[] = { "Off", "Easy", "Medium", "Hard", "Very hard", "Master" };

  func_800905E8(0);

  D_800CFEE8 = 4;  // main menu

  if (intro_flag) {
    D_800CFEE8 = 3;  // intro: 2 = spinning_n64_3d_logo, 1 = bps_and_h2o_logo, 3 = animation_and_tetris_start
  } else if (haluci_flag) {
    D_800D3CF0 = 4;  // haluci mode
  } else {
    if (g_opponent == 0) {
      D_800CFED4 = num_players;
      game_ptr->landfill.type = landfilltype;
    } else {
      aiplayer_gameinit_related(2, gametype, g_opponent - 1);
      D_800CFED4 = 2;  // num players is 2
      game_ptr->landfill.type = LANDFILLTYPE_DIRECTED;
    }
    D_800D3CF0 = 1;  // game mode
    game_ptr->gameType = gametype;
    printf("Num players: %d\n", D_800CFED4);
    printf("Opponent: '%s'\n", opponent_str[g_opponent]);
    printf("Game type: '%s'\n", gametype_str[game_ptr->gameType]);
    printf("Garbage type: '%s'\n", landfilltype_str[game_ptr->landfill.type]);
  }

  {
    strncpy(game_ptr->players[0].node.name, p0_name, 8);
    game_ptr->players[0].node.name[8] = 0;

    strncpy(game_ptr->players[1].node.name, p1_name, 8);
    game_ptr->players[1].node.name[8] = 0;

    strncpy(game_ptr->players[2].node.name, p2_name, 8);
    game_ptr->players[2].node.name[8] = 0;

    strncpy(game_ptr->players[3].node.name, p3_name, 8);
    game_ptr->players[3].node.name[8] = 0;
  }
}

void game_deinit(void) {
  if (g_game.is_active) {
    Game_Deinit();
  }
}


void update_metrics(void) {
  static bool isCurrentPieceActive = false;

  if (g_game.unk0 == 0 && g_game.tetris_ptr_arr[0] != NULL) {
    if (g_game.tetris_ptr_arr[0]->board.currentPiece.state == 0) {
      isCurrentPieceActive = false;
    } else if (g_game.tetris_ptr_arr[0]->board.currentPiece.state == 1) {
      if (isCurrentPieceActive == false) {
        isCurrentPieceActive = true;
        currentPieceFrames = 0;
      }
      if (lag_flag) {
        currentPieceFrames += 2;
      } else {
        currentPieceFrames++;
      }
    }
  }
}


// Main loop

static void main_loop(ALLEGRO_EVENT_QUEUE* queue) {
  bool done = false;
  bool redraw = false;
  ALLEGRO_EVENT event;

  draw_buffer = 0;

  if (replay) {
    if (fgets(line, sizeof(line), fp)) {
      sscanf(line, "%u %u %u %u %u", &frmcnt, &button[0], &button[1], &button[2], &button[3]);
    } else {
      done = true;
    }
  }

  while (!done) {
    al_wait_for_event(queue, &event);

    switch (event.type) {
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_EVENT_TIMER:
      if (key[ALLEGRO_KEY_ESCAPE]) {
        done = true;
      }

      if (replay) {
        if (!redraw) {
          if (lag_flag) {
            framecount += 2;
          } else {
            framecount++;
          }
          // assert framecount == frmcnt

          update_metrics();

          redraw = replay_contq_enqueue(&done);
        }
      } else {
        if (lag_flag) {
          framecount += 2;
        } else {
          framecount++;
        }

        update_metrics();

        redraw = contq_enqueue();
      }

      break;
    }

    keyboard_update(&event);
    joystick_update(&event);

    if (redraw) {
      if (net_flag || al_is_event_queue_empty(queue) || done) {
        disp_pre_draw();

        al_clear_to_color(al_map_rgb(0, 0, 0));

        if (net_flag) {
          Game_render_stuff_line_850(&g_game);
        } else {
          if (record) {
            fprintf(fp, "%u %u %u %u %u\n", 0, 0, 0, 0, 0);
          }

          // From 00E2A0.c, has_rounds_and_floors_large_liner()
          frametime_update(framecount);
          //for (int i = 0; i < 4; i++) {
          for (int i = 0; i < D_800CFED4; i++) {
            g_PV_ptr = &g_PV_arr[i];
            contq_dequeue();
          }
          FUN_032F00_MVC_control_menu_choice_process();
          if (D_800CFEE0 != 0) {
            func_800A9010(&g_gdl);  // display fps measurement
          }
          D_800CFED8++;

          if (lag_flag) {
            // push game elapsed time up 20 jiffies
            if (g_game.unkE4E8 == 0) {
              g_game.unkE4E8 = 20;
            }
          }
        }

        hud_draw();
        disp_post_draw();
        redraw = false;

        draw_buffer ^= 1;
      }
    }
  }
}


static void print_usage(const char *prog_name) {
  printf("Usage: %s [options] [FILE [DIR]]\n", prog_name);
  printf("\nPositional arguments:\n");
  printf("  FILE           Record moves to FILE if does not exist, else replay moves from FILE\n");
  printf("  DIR            Save frames to DIR if replaying moves from FILE\n");
  printf("\nOptions:\n");
  printf("  -h, --help     show this help message\n");
  printf("  -v, --verbose  enable verbose output\n");
  printf("  -n NUMPLAYERS  (default: 1)\n");
  printf("  -o OPPONENT    (default: Off) 1=Easy 2=Medium 3=Hard 4=Very hard 5=Master\n");
  printf("  -0 NAME        (default: 'PLAYER 0')\n");
  printf("  -1 NAME        (default: 'PLAYER 1')\n");
  printf("  -2 NAME        (default: 'PLAYER 2')\n");
  printf("  -3 NAME        (default: 'PLAYER 3')\n");
  printf("  -s SCREEN      (default: random) 0=Mayan 1=Greek 2=Egyptian 3=Celtic 4=African 5=Japanese 6=Russian 7=Finale\n");
  printf("  -g GAMEID      (default: random) GAMEID modulo 0x0C000000\n");
  printf("\ngame mode:\n");
  printf("  Choose one of these game modes.  (default: Marathon)\n\n");
  printf("  --sprint\n");
  printf("  --ultra\n");
  printf("\ngarbage mode:\n");
  printf("  Choose one of these garbage modes.  (default: None)\n\n");
  printf("  --hotpotato\n");
  printf("  --directed\n");
}


// Main

enum {
  OPT_HOST = 1000,
  OPT_PORT,
};

int main(int argc, char *argv[]) {
  int c;
  char *nopt = NULL;
  char *oopt = NULL;
  char *p0opt = NULL;
  char *p1opt = NULL;
  char *p2opt = NULL;
  char *p3opt = NULL;
  char *sopt = NULL;
  char *gopt = NULL;
  char *hostopt = NULL;
  char *portopt = NULL;
  static struct option long_options[] =
    {
      {"help",      no_argument,       NULL, 'h'},
      {"verbose",   no_argument,       NULL, 'v'},
      {"sprint",    no_argument,       &gametype, GAMETYPE_SPRINT},
      {"ultra",     no_argument,       &gametype, GAMETYPE_ULTRA},
      {"hotpotato", no_argument,       &landfilltype, LANDFILLTYPE_HOTPOTATO},
      {"directed",  no_argument,       &landfilltype, LANDFILLTYPE_DIRECTED},
      {"net",       no_argument,       &net_flag, true},
      {"host",      required_argument, NULL, OPT_HOST},
      {"port",      required_argument, NULL, OPT_PORT},
      {"lag",       no_argument,       &lag_flag, true},
      {"intro",     no_argument,       &intro_flag, true},
      {"haluci",    no_argument,       &haluci_flag, true},
      {NULL, 0, NULL, 0}
    };

  while ((c = getopt_long(argc, argv, "hvn:o:0:1:2:3:s:g:", long_options, NULL)) != -1) {
    switch (c) {
    case 0:
      break;
    case 'h':
      print_usage(argv[0]);
      return EXIT_SUCCESS;
    case 'v':
      verbose_flag = true;
      break;
    case 'n':
      nopt = optarg;
      break;
    case 'o':
      oopt = optarg;
      break;
    case '0':
      p0opt = optarg;
      break;
    case '1':
      p1opt = optarg;
      break;
    case '2':
      p2opt = optarg;
      break;
    case '3':
      p3opt = optarg;
      break;
    case 's':
      sopt = optarg;
      break;
    case 'g':
      gopt = optarg;
      break;
    case OPT_HOST:
      hostopt = optarg;
      break;
    case OPT_PORT:
      portopt = optarg;
      break;
    case '?':
      print_usage(argv[0]);
      return EXIT_FAILURE;
    default:
      abort();
    }
  }

  if (optind < argc) {
    if (access(argv[optind], F_OK) == 0) {  // file exists
      fp = fopen(argv[optind], "r");
      if (fp == NULL) {
        printf("Cannot open file: '%s'\n", argv[optind]);
      } else {
        printf("Replaying moves from file: '%s'\n", argv[optind]);
        replay = true;
        if (optind + 1 < argc) {
          DIR *dir = opendir(argv[optind + 1]);
          if (dir) {
            closedir(dir);
            printf("Saving frames to dir: '%s'\n", argv[optind + 1]);
            save_frames = true;
            frames_dir = strdup(argv[optind + 1]);
          } else {
            printf("Dir '%s' does not exist or permission denied\n", argv[optind + 1]);
          }
        }
      }
    } else {  // file does not exist
      fp = fopen(argv[optind], "w");
      if (fp == NULL) {
        printf("Cannot open file: '%s'\n", argv[optind]);
      } else {
        printf("Recording moves to file: '%s'\n", argv[optind]);
        record = true;
      }
    }
  }

  srand(time(NULL));
  FUN_026900_sets_g8011FA70_to_arg0(osGetTime());  // sets seed for FUN_026900_PRNG_1()

  unsigned short num_players = 1;
  if (nopt != NULL) {
    num_players = strtoul(nopt, NULL, 0) % 4;
    if (num_players == 0) {
      num_players = 4;
    }
  }

  if (oopt != NULL) {
    g_opponent = strtoul(oopt, NULL, 0) % 5;
    if (g_opponent == 0) {
      g_opponent = 5;
    }
  }

  if (p0opt != NULL) {
    strncpy(p0_name, p0opt, 8);
    p0_name[8] = 0;
  }
  if (p1opt != NULL) {
    strncpy(p1_name, p1opt, 8);
    p1_name[8] = 0;
  }
  if (p2opt != NULL) {
    strncpy(p2_name, p2opt, 8);
    p2_name[8] = 0;
  }
  if (p3opt != NULL) {
    strncpy(p3_name, p3opt, 8);
    p3_name[8] = 0;
  }
  printf("Player 0 name: '%s'\n", p0_name);
  printf("Player 1 name: '%s'\n", p1_name);
  printf("Player 2 name: '%s'\n", p2_name);
  printf("Player 3 name: '%s'\n", p3_name);

  if (sopt != NULL) {
    g_screen = strtoul(sopt, NULL, 0) % 8;
  }

  if (gopt != NULL) {
    game_id = strtoul(gopt, NULL, 0);
  } else {
    game_id = osGetTime();
  }
  printf("Game id: '0x%08x'\n", game_id);

  char *host = "localhost";
  int port = DEFAULT_PORT;
  if (hostopt != NULL) {
    host = hostopt;
  }
  if (portopt != NULL) {
    port = strtoul(portopt, NULL, 0);
  }

  if (net_flag) {
    printf("host: %s\n", host);
    printf("port: %d\n", port);

    if (enet_initialize() != 0) {
      fprintf(stderr, "An error occurred while initializing ENet.\n");
      return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    client = create_client();
    server = connect_client(client, host, port);
  }

  config_init(&g_images_cfg);
  if(!config_read_file(&g_images_cfg, "images.cfg")) {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&g_images_cfg), config_error_line(&g_images_cfg), config_error_text(&g_images_cfg));
    config_destroy(&g_images_cfg);
    return EXIT_FAILURE;
  }

  config_init(&g_anims_cfg);
  if(!config_read_file(&g_anims_cfg, "anims.cfg")) {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&g_anims_cfg), config_error_line(&g_anims_cfg), config_error_text(&g_anims_cfg));
    config_destroy(&g_anims_cfg);
    return EXIT_FAILURE;
  }

  config_init(&g_effects_cfg);
  if(!config_read_file(&g_effects_cfg, "effects.cfg")) {
    fprintf(stderr, "%s:%d - %s\n", config_error_file(&g_effects_cfg), config_error_line(&g_effects_cfg), config_error_text(&g_effects_cfg));
    config_destroy(&g_effects_cfg);
    return EXIT_FAILURE;
  }

  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");
  must_init(al_install_joystick(), "joystick");

  ALLEGRO_TIMER *timer;
  if (lag_flag) {
    timer = al_create_timer(1.0 / 30.0);
  } else {
    timer = al_create_timer(1.0 / 60.0);
  }
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  must_init(queue, "queue");

  disp_init();

  hud_init();

  player_init();

  game_init(num_players);

  must_init(al_init_primitives_addon(), "primitives");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_joystick_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  keyboard_init();

  for (int i = 0; i < 4; i++) {
    joystick_init(i);
  }

  al_start_timer(timer);
  main_loop(queue);

  if (fp != NULL) fclose(fp);
  if (frames_dir != NULL) free(frames_dir);

  game_deinit();
  player_deinit();
  hud_deinit();
  disp_deinit();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  if (net_flag) {
    disconnect_client(client, server);
    enet_host_destroy(client);
  }

  config_destroy(&g_images_cfg);
  config_destroy(&g_anims_cfg);
  config_destroy(&g_effects_cfg);

  return EXIT_SUCCESS;
}

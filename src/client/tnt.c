#include "common.h"
#include <getopt.h>
#include <libconfig.h>
#include <time.h>

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


////////////////////////////////////////
// TODO: move this out of here
////////////////////////////////////////
u8 D_800CFD48 = TRUE;
s8 D_800CF838 = 7;  // max unlocked screen
////////////////////////////////////////


static FILE *fp;
static int record = false;
static int replay = false;
static int save_frames = false;
static char *frames_dir = NULL;
static unsigned int framecount = 0;
unsigned int game_id = 0;
static unsigned int gametype = GAMETYPE_SPRINT;
char p0_name[9] = "PLAYER 0";
char p1_name[9] = "PLAYER 1";
char p2_name[9] = "PLAYER 2";
char p3_name[9] = "PLAYER 3";
static ENetHost *client;
static ENetPeer *server;
static int net_flag = false;

static void print_joystick_info(ALLEGRO_JOYSTICK *joy) {
  int i, n, a;

  if (!joy)
    return;

  printf("Joystick: '%s'\n", al_get_joystick_name(joy));

  printf("  Buttons:");
  n = al_get_joystick_num_buttons(joy);
  for (i = 0; i < n; i++) {
    printf(" '%s'", al_get_joystick_button_name(joy, i));
  }
  printf("\n");

  n = al_get_joystick_num_sticks(joy);
  for (i = 0; i < n; i++) {
    printf("  Stick %d: '%s'\n", i, al_get_joystick_stick_name(joy, i));

    for (a = 0; a < al_get_joystick_num_axes(joy, i); a++) {
      printf("    Axis %d: '%s'\n",
             a, al_get_joystick_axis_name(joy, i, a));
    }
  }
}

void must_init(bool test, const char *description) {
  if (test) return;

  printf("couldn't initialize %s\n", description);
  exit(1);
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

#define DISP_W 640
#define DISP_H 480

static ALLEGRO_DISPLAY* disp;
static ALLEGRO_BITMAP* buffer;

static void disp_init(unsigned short num_players) {
  al_add_new_bitmap_flag(ALLEGRO_NO_PRESERVE_TEXTURE);

  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  disp = al_create_display(DISP_W, DISP_H);
  must_init(disp, "display");

  buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  must_init(buffer, "bitmap buffer");

  al_init_image_addon();
}

static void disp_deinit(void) {
  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
}

static void disp_pre_draw(void) {
  al_set_target_bitmap(buffer);
}

static void disp_post_draw(void) {
  static char filename[256];
  static unsigned int last_framecount = 0;

  al_set_target_backbuffer(disp);
  al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

  if (save_frames) {
    while (last_framecount < framecount) {
      last_framecount++;
      sprintf(filename, "%s/image-%08d.png", frames_dir, last_framecount);
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
  u8 dpad;
} CtrlCfg;

CtrlCfg ctrlCfg;

void joystick_init(ALLEGRO_JOYSTICK *joy) {
  print_joystick_info(joy);

  if (!joy)
    return;

  if (strcmp(al_get_joystick_name(joy), "8Bitdo FC30 Pro    8Bitdo FC30 Pro") == 0) {
    // 8Bitdo
    ctrlCfg.btn_a = 1;
    ctrlCfg.btn_b = 4;
    ctrlCfg.trig_l = 8;
    ctrlCfg.trig_r = 9;
    ctrlCfg.trig_z = 10;
    ctrlCfg.btn_start = 11;
    ctrlCfg.dpad = 4;
  } else if (strcmp(al_get_joystick_name(joy), "Sony Interactive Entertainment Wireless Controller") == 0) {
    // PS4 controller over usb
    ctrlCfg.btn_a = 0;     // square button
    ctrlCfg.btn_b = 3;     // X button
    ctrlCfg.trig_l = 4;    // L1 trigger
    ctrlCfg.trig_r = 5;    // R1 trigger
    ctrlCfg.trig_z = 12;   // right analog stick button
    ctrlCfg.btn_start = 9; // options button
    ctrlCfg.dpad = 3;      // dpad
  } else if (strcmp(al_get_joystick_name(joy), "Microsoft X-Box 360 pad") == 0) {
    // Generic brand Nintendo Switch controller over usb (shows up as X-Box 360?)
    ctrlCfg.btn_a = 0;     // B button
    ctrlCfg.btn_b = 2;     // Y button
    ctrlCfg.trig_l = 4;    // L1 trigger
    ctrlCfg.trig_r = 5;    // R1 trigger
    ctrlCfg.trig_z = 10;   // right analog stick button
    ctrlCfg.btn_start = 8; // home button
    ctrlCfg.dpad = 3;      // dpad
  } else {
    // N64 controller
    ctrlCfg.btn_a = 1;
    ctrlCfg.btn_b = 2;
    ctrlCfg.trig_l = 4;
    ctrlCfg.trig_r = 5;
    ctrlCfg.trig_z = 6;
    ctrlCfg.btn_start = 9;
    ctrlCfg.dpad = 2;
  }
}

void joystick_update(ALLEGRO_EVENT* event) {
  switch(event->type) {
  case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
    al_reconfigure_joysticks();
    for (int i = 0; i < 4; i++) {
      joystick_init(al_get_joystick(i));
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
  al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 3, 3, 0, "FrameCount: %u", framecount);
}


// ContPad stuff

void snapshot_contpad(ALLEGRO_JOYSTICK *joy, OSContPad *contpad) {
  ALLEGRO_JOYSTICK_STATE jst;
  int i, j;

  if (!joy) {
    return;
  }

  al_get_joystick_state(joy, &jst);

  /*
  printf("\n");
  for (i = 0; i < al_get_joystick_num_buttons(joy); i++) {
    printf("jst.button[%d] = %d\n", i, jst.button[i]);
  }
  for (j = 0; j < al_get_joystick_num_sticks(joy); j++) {
    for (i = 0; i < al_get_joystick_num_axes(joy, j); i++) {
      printf("jst.stick[%d].axis[%d] = %f\n", j, i, jst.stick[j].axis[i]);
    }
  }
  */

  if (jst.button[ctrlCfg.btn_a]     >= 16384) contpad->button |= 0x8000;    // A_BUTTON     / CONT_A
  if (jst.button[ctrlCfg.btn_b]     >= 16384) contpad->button |= 0x4000;    // B_BUTTON     / CONT_B
  if (jst.button[ctrlCfg.trig_l]    >= 16384) contpad->button |= 0x0020;    // L_TRIG       / CONT_L
  if (jst.button[ctrlCfg.trig_r]    >= 16384) contpad->button |= 0x0010;    // R_TRIG       / CONT_R
  if (jst.button[ctrlCfg.trig_z]    >= 16384) contpad->button |= 0x2000;    // Z_TRIG       / CONT_G
  if (jst.button[ctrlCfg.btn_start] >= 16384) contpad->button |= 0x1000;    // START_BUTTON / CONT_START

  if (jst.stick[ctrlCfg.dpad].axis[0] < 0) contpad->button |= 0x0200;       // L_JPAD       / CONT_LEFT
  else if (jst.stick[ctrlCfg.dpad].axis[0] > 0) contpad->button |= 0x0100;  // R_JPAD       / CONT_RIGHT
  if (jst.stick[ctrlCfg.dpad].axis[1] < 0) contpad->button |= 0x0800;       // U_JPAD       / CONT_UP
  else if (jst.stick[ctrlCfg.dpad].axis[1] > 0) contpad->button |= 0x0400;  // D_JPAD       / CONT_DOWN
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
        record_framecount++;
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

      frmcnt++;
      func_800A3A8C(frmcnt);
      for (int i = 0; i < 4; i++) {
        g_PV_ptr = &g_PV_arr[i];
        contq_dequeue();
      }

      if (in_lobby) {
        num_ready_players = 0;
        for (int i = 0; i < 4; i++) {
          g_PV_ptr = &g_PV_arr[i];
          if (g_PV_ptr->unk1C->unk30 != 0) {  // R_TRIG / CONT_R
            num_ready_players++;
          }
        }
        if (num_ready_players > 1) {
          func_80090E08();
          in_lobby = false;
        }
      } else {
        D_801109F4 = func_800A3AF0();
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

  if (net_flag) {
    snapshot_contpad(al_get_joystick(0), &contpad);

    //print_contpad(0, &contpad);

    ClientMessage msg = { .seq_no = framecount, .button = contpad.button };
    ENetPacket *packet = enet_packet_create(&msg, sizeof(msg), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(server, 0, packet);
    return send_receive(client);
  } else {
    if (record) {
      fprintf(fp, "%u", framecount);
    }
    //for (int i = 0; i < D_800CFED4; i++) {
    for (int i = 0; i < 4; i++) {
      snapshot_contpad(al_get_joystick(i), &contpad);

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

  //for (int i = 0; i < D_800CFED4; i++) {
  for (int i = 0; i < 4; i++) {
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
}

void player_deinit(void) {
  s16 i;
  ControllerQueue *contQ_ptr;

  for (i = 0; i < 4; i++) {
    contQ_ptr = controller_queues[i];
    n64HeapUnalloc(contQ_ptr->unk14);
    n64HeapUnalloc(contQ_ptr->_ControllerQueue);
  }
}


// Game stuff

void game_init(unsigned short num_players) {
  register Game *game_ptr = &g_game;

  D_800CFED4 = num_players;
  game_ptr->gameType = gametype;
  D_800CFEE8 = 4;  // MVC menu choice

  func_800905E8(0);

  {
    int i;
    char *src;

    i = 0;
    src = p0_name;
    memset(game_ptr->players[0].name, 0, 9);
    while (*src != 0 && i < 8) game_ptr->players[0].name[i++] = *src++;

    i = 0;
    src = p1_name;
    memset(game_ptr->players[1].name, 0, 9);
    while (*src != 0 && i < 8) game_ptr->players[1].name[i++] = *src++;

    i = 0;
    src = p2_name;
    memset(game_ptr->players[2].name, 0, 9);
    while (*src != 0 && i < 8) game_ptr->players[2].name[i++] = *src++;

    i = 0;
    src = p3_name;
    memset(game_ptr->players[3].name, 0, 9);
    while (*src != 0 && i < 8) game_ptr->players[3].name[i++] = *src++;
  }
}

void game_deinit(void) {
  Game_Deinit();
}


// Main loop

static void main_loop(ALLEGRO_EVENT_QUEUE* queue) {
  bool done = false;
  bool redraw = false;
  ALLEGRO_EVENT event;

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
          framecount++;
          // assert framecount == frmcnt
          redraw = replay_contq_enqueue(&done);
        }
      } else {
        framecount++;
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

          // From 00E440.c, has_rounds_and_floors_large_liner()
          func_800A3A8C(framecount);
          //for (int i = 0; i < D_800CFED4; i++) {
          for (int i = 0; i < 4; i++) {
            g_PV_ptr = &g_PV_arr[i];
            contq_dequeue();
          }
          FUN_032F00_MVC_control_menu_choice_process();
        }

        hud_draw();
        disp_post_draw();
        redraw = false;
      }
    }
  }
}


// Main

config_t g_images_cfg;
config_t g_anims_cfg;

int main(int argc, char **argv) {
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

  char *host = "localhost";
  int port = DEFAULT_PORT;

  static const char *gametype_str[] = { "Marathon", "Sprint", "Ultra" };

  int c;
  char *gopt = NULL;
  char *nopt = NULL;
  char *hopt = NULL;
  char *popt = NULL;
  static struct option long_options[] =
    {
      {"marathon", no_argument,       &gametype, GAMETYPE_MARATHON},
      {"sprint",   no_argument,       &gametype, GAMETYPE_SPRINT},
      {"ultra",    no_argument,       &gametype, GAMETYPE_ULTRA},
      {"gameid",   required_argument, NULL, 'g'},
      {"name",     required_argument, NULL, 'n'},
      {"net",      no_argument,       &net_flag, true},
      {"host",     required_argument, NULL, 'h'},
      {"port",     required_argument, NULL, 'p'},
      {NULL, 0, NULL, 0}
    };
  int option_index = 0;

  while ((c = getopt_long(argc, argv, "g:n:h:p:", long_options, &option_index)) != -1) {
    switch (c) {
    case 0:
      break;
    case 'g':
      gopt = optarg;
      break;
    case 'n':
      nopt = optarg;
      break;
    case 'h':
      hopt = optarg;
      break;
    case 'p':
      popt = optarg;
      break;
    case '?':
      break;
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
          printf("Saving frames to dir: '%s'\n", argv[optind + 1]);
          save_frames = true;
          frames_dir = strdup(argv[optind + 1]);
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

  if (gopt != NULL) {
    game_id = strtoul(gopt, NULL, 0);
  } else {
    game_id = osGetTime();
  }
  printf("Game id: '0x%08x'\n", game_id);

  printf("Game type: '%s'\n", gametype_str[gametype]);

  if (nopt != NULL) {
    int i = 0;
    char *src = nopt;

    memset(p0_name, 0, sizeof(p0_name));
    while (*src != 0  && i < 8) p0_name[i++] = *src++;
  }
  printf("Player 0 name: '%s'\n", p0_name);
  printf("Player 1 name: '%s'\n", p1_name);
  printf("Player 2 name: '%s'\n", p2_name);
  printf("Player 3 name: '%s'\n", p3_name);

  if (hopt != NULL) {
    host = hopt;
  }
  if (popt != NULL) {
    port = strtoul(popt, NULL, 0);
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

  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");
  must_init(al_install_joystick(), "joystick");

  ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
  must_init(queue, "queue");

  if (net_flag) {
    disp_init(2);
  } else {
    disp_init(1);
  }

  hud_init();

  player_init();

  if (net_flag) {
    game_init(2);
  } else {
    game_init(1);
  }

  must_init(al_init_primitives_addon(), "primitives");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_joystick_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  keyboard_init();

  for (int i = 0; i < 4; i++) {
    joystick_init(al_get_joystick(i));
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
  return EXIT_SUCCESS;
}

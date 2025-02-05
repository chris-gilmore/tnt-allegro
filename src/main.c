#include "common.h"
#include <getopt.h>

// dnf: allegro5-devel
// apt: liballegro5-dev
#include<allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

// dnf: allegro5-addon-ttf-devel
// apt: liballegro-ttf5-dev
//#include <allegro5/allegro_ttf.h>


////////////////////////////////////////
// TODO: move this out of here
////////////////////////////////////////
ALLEGRO_FONT* font;
void displayText_XY_RGBA_2(Gfx **arg0, void *arg1, s16 x, s16 y, char *text, s32 red, s32 green, s32 blue, s32 alpha) {
  al_draw_textf(font, al_map_rgba(red, green, blue, alpha), x, y, 0, text);
}
u8 D_800CFD48 = TRUE;
s8 D_800CF838 = 0;
////////////////////////////////////////


static FILE *fp;
static int record = false;
static int replay = false;
static unsigned int framecount = 0;
unsigned int seed = 0;
static unsigned int gametype = GAMETYPE_SPRINT;
char p0_name[9] = "";

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
  if(test) return;

  printf("couldn't initialize %s\n", description);
  exit(1);
}


// Display stuff

#define BUFFER_W 400
#define BUFFER_H 300

#define DISP_W 640
#define DISP_H 480

ALLEGRO_DISPLAY* disp;
ALLEGRO_BITMAP* buffer;

void disp_init(void) {
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  disp = al_create_display(DISP_W, DISP_H);
  must_init(disp, "display");

  buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  must_init(buffer, "bitmap buffer");
}

void disp_deinit(void) {
  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
}

void disp_pre_draw(void) {
  al_set_target_bitmap(buffer);
}

void disp_post_draw(void) {
  al_set_target_backbuffer(disp);
  al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

  al_flip_display();
}


// Keyboard stuff

#define KEY_SEEN     1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init(void) {
  memset(key, 0, sizeof(key));
}

void keyboard_update(ALLEGRO_EVENT* event) {
  switch(event->type) {
  case ALLEGRO_EVENT_TIMER:
    for(int i = 0; i < ALLEGRO_KEY_MAX; i++)
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
    joystick_init(al_get_joystick(0));
    break;
  }
}


// ContPad stuff

OSContPad contpad;

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

void print_contpad(OSContPad *contpad) {
  printf("contpad.button = %016b\n", contpad->button);
}

static ControllerQueue *controller_queues[4];

int contq_enqueue(void) {
  contpad.button = 0x0000;

  if (key[ALLEGRO_KEY_D])     contpad.button |= 0x8000;    // A_BUTTON     / CONT_A
  if (key[ALLEGRO_KEY_S])     contpad.button |= 0x4000;    // B_BUTTON     / CONT_B
  if (key[ALLEGRO_KEY_Q])     contpad.button |= 0x0020;    // L_TRIG       / CONT_L
  if (key[ALLEGRO_KEY_E])     contpad.button |= 0x0010;    // R_TRIG       / CONT_R
  if (key[ALLEGRO_KEY_W])     contpad.button |= 0x2000;    // Z_TRIG       / CONT_G
  if (key[ALLEGRO_KEY_ENTER]) contpad.button |= 0x1000;    // START_BUTTON / CONT_START

  if (key[ALLEGRO_KEY_J])     contpad.button |= 0x0200;    // L_JPAD       / CONT_LEFT
  if (key[ALLEGRO_KEY_L])     contpad.button |= 0x0100;    // R_JPAD       / CONT_RIGHT
  if (key[ALLEGRO_KEY_I])     contpad.button |= 0x0800;    // U_JPAD       / CONT_UP
  if (key[ALLEGRO_KEY_K])     contpad.button |= 0x0400;    // D_JPAD       / CONT_DOWN

  snapshot_contpad(al_get_joystick(0), &contpad);

  //print_contpad(&contpad);

  if (record) {
    fprintf(fp, "%u %u\n", framecount, contpad.button);
  }

  FUN_069580_800A3300_nineliner_mod300(controller_queues[0], &contpad);
}

static char line[200];
static unsigned int frmcnt = 0;
static unsigned int button = 0;

int replay_contq_enqueue(bool *done_ptr) {
  contpad.button = button;
  FUN_069580_800A3300_nineliner_mod300(controller_queues[0], &contpad);

  if (!fgets(line, sizeof(line), fp)) {
    *done_ptr = true;
    return false;
  }

  sscanf(line, "%u %u", &frmcnt, &button);
  if (frmcnt == 0) {
    if (fgets(line, sizeof(line), fp)) {
      sscanf(line, "%u %u", &frmcnt, &button);
    } else {
      *done_ptr = true;
    }
    return true;
  } else {
    return false;
  }
}

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


// HUD stuff

ALLEGRO_FONT* hud_font;

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
  al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 1, 1, 0, "FrameCount: %u", framecount);
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
  //Audio_InitAudio();
}

void player_deinit(void) {
  s16 i;
  ControllerQueue *contQ_ptr;

  for (i = 0; i < 4; i++) {
    contQ_ptr = controller_queues[i];
    n64HeapUnalloc((void *)contQ_ptr->unk14);
    n64HeapUnalloc((void *)contQ_ptr->_ControllerQueue);
  }
}


// Game stuff

void game_init(void) {
  register Game *game_ptr = &g_game;

  D_800CFED4 = 1;  // num players
  game_ptr->gameType = gametype;
  D_800CFEE8 = 4;  // MVC menu choice
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
      sscanf(line, "%u %u", &frmcnt, &button);
    } else {
      done = true;
    }
  }

  while (!done) {
    al_wait_for_event(queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      //printf("timer.count: %u\n", event.timer.count);

      if (replay) {
        if (!redraw) {
          framecount++;
          // assert framecount == frmcnt
          redraw = replay_contq_enqueue(&done);
        }
      } else {
        framecount++;
        contq_enqueue();
        redraw = true;
      }

      if(key[ALLEGRO_KEY_ESCAPE]) {
        done = true;
      }
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    }

    keyboard_update(&event);
    joystick_update(&event);

    if(redraw && (al_is_event_queue_empty(queue) || done)) {
      disp_pre_draw();
      al_clear_to_color(al_map_rgb(0x20, 0x20, 0x20));

      // qlen = func_800A3534(&g_PV_ptr->contQ)
      // assert qlen > 0
      {
        if (record) {
          fprintf(fp, "%u %u\n", 0, 0);
        }

        contq_dequeue();

        // From 00E440.c, has_rounds_and_floors_large_liner()
        func_800A3A8C(framecount);
        FUN_032F00_MVC_control_menu_choice_process();
      }

      hud_draw();

      disp_post_draw();
      redraw = false;
    }
  }
}


// Main

int main(int argc, char **argv) {
  static const char *gametype_str[] = { "Marathon", "Sprint", "Ultra" };

  int c;
  char *sopt = NULL;
  char *nopt = NULL;
  static struct option long_options[] =
    {
      {"marathon", no_argument,       &gametype, GAMETYPE_MARATHON},
      {"sprint",   no_argument,       &gametype, GAMETYPE_SPRINT},
      {"ultra",    no_argument,       &gametype, GAMETYPE_ULTRA},
      {"seed",     required_argument, NULL, 's'},
      {"name",     required_argument, NULL, 'n'},
      {NULL, 0, NULL, 0}
    };
  int option_index = 0;

  while ((c = getopt_long(argc, argv, "s:n:", long_options, &option_index)) != -1) {
    switch (c) {
    case 0:
      break;
    case 's':
      sopt = optarg;
      break;
    case 'n':
      nopt = optarg;
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

  if (sopt != NULL) {
    seed = strtoul(sopt, NULL, 0);
  }
  printf("Seed: '0x%08x'\n", seed);

  printf("Game type: '%s'\n", gametype_str[gametype]);

  memset(p0_name, 0, sizeof(p0_name));
  if (nopt != NULL) {
    int i = 0;
    char *src = nopt;
    while (*src && i < 8) p0_name[i++] = *src++;
  }
  printf("Player 0 name: '%s'\n", p0_name);


  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");
  must_init(al_install_joystick(), "joystick");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

  font = al_create_builtin_font();

  disp_init();

  hud_init();

  player_init();
  game_init();

  must_init(al_init_primitives_addon(), "primitives");

  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_joystick_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));

  keyboard_init();

  joystick_init(al_get_joystick(0));

  al_start_timer(timer);
  main_loop(queue);

  if (fp != NULL) fclose(fp);

  game_deinit();
  player_deinit();
  hud_deinit();
  disp_deinit();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  al_destroy_font(font);

  return 0;
}

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
/*
// $ dnf install allegro5-addon-ttf-devel
#include <allegro5/allegro_ttf.h>
*/

#include "common.h"

typedef struct {
  u8 btn_a;
  u8 btn_b;
  u8 trig_l;
  u8 trig_r;
  u8 trig_z;
  u8 btn_start;
  u8 dpad;
} CtrlCfg;


u8 *n64HeapAlloc(s32 size) {
  return malloc(size);
}
void n64HeapUnalloc(u8 *pBlock) {
  free(pBlock);
}

void rmonPrintf(const char* fmt, ...) {
  int ans;
  va_list ap;

  va_start(ap, fmt);
  ans = vprintf(fmt, ap);
  va_end(ap);
}

void debug_print_reason_routine(u8 *arg0, u8 *arg1) {  // dbgprntrrl
  printf("Reason: %s\n Routine: %s\n", arg0, arg1);
}

void debug_print2(const u8 *arg0, const u8 *arg1) {
  /*
  printf("%25s | %s\n", arg1, arg0);
  */
}

ALLEGRO_FONT* font;

void displayText_XY_RGBA_2(Gfx **arg0, void *arg1, s16 x, s16 y, u8 *text, s32 red, s32 green, s32 blue, s32 alpha) {
  al_draw_textf(font, al_map_rgba(red, green, blue, alpha), x, y, 0, text);
}


u16 D_800CFED4 = 1;


////////////////////////////////////////


u32 framecount = 0;


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

void disp_init() {
  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

  disp = al_create_display(DISP_W, DISP_H);
  must_init(disp, "display");

  buffer = al_create_bitmap(BUFFER_W, BUFFER_H);
  must_init(buffer, "bitmap buffer");
}

void disp_deinit() {
  al_destroy_bitmap(buffer);
  al_destroy_display(disp);
}

void disp_pre_draw() {
  al_set_target_bitmap(buffer);
}

void disp_post_draw() {
  al_set_target_backbuffer(disp);
  al_draw_scaled_bitmap(buffer, 0, 0, BUFFER_W, BUFFER_H, 0, 0, DISP_W, DISP_H, 0);

  al_flip_display();
}


// Keyboard stuff

#define KEY_SEEN     1
#define KEY_RELEASED 2
unsigned char key[ALLEGRO_KEY_MAX];

void keyboard_init() {
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

  contpad->button = 0x0000;

  if (jst.button[ctrlCfg.btn_a]     >= 16384) contpad->button |= 0x8000;    // A_BUTTON     / CONT_A
  if (jst.button[ctrlCfg.btn_b]     >= 16384) contpad->button |= 0x4000;    // B_BUTTON     / CONT_B
  if (jst.button[ctrlCfg.trig_l]    >= 16384) contpad->button |= 0x0020;    // L_TRIG       / CONT_L
  if (jst.button[ctrlCfg.trig_r]    >= 16384) contpad->button |= 0x0010;    // R_TRIG       / CONT_R
  if (jst.button[ctrlCfg.trig_z]    >= 16384) contpad->button |= 0x2000;    // Z_TRIG       / CONT_G
  if (jst.button[ctrlCfg.btn_start] >= 16384) contpad->button |= 0x1000;    // START_BUTTON / CONT_START

  if (jst.stick[ctrlCfg.dpad].axis[0] < 0) contpad->button |= 0x0200;       // L_JPAD / CONT_LEFT
  else if (jst.stick[ctrlCfg.dpad].axis[0] > 0) contpad->button |= 0x0100;  // R_JPAD / CONT_RIGHT
  if (jst.stick[ctrlCfg.dpad].axis[1] < 0) contpad->button |= 0x0800;       // U_JPAD / CONT_UP
  else if (jst.stick[ctrlCfg.dpad].axis[1] > 0) contpad->button |= 0x0400;  // D_JPAD / CONT_DOWN
}

void print_contpad(OSContPad *contpad) {
  printf("contpad.button = %016b\n", contpad->button);
}

static ControllerQueue *controller_queues[4];

void contq_enqueue() {
  snapshot_contpad(al_get_joystick(0), &contpad);

  //print_contpad(&contpad);

  FUN_069580_800A3300_nineliner_mod300(controller_queues[0], &contpad);
}

void contq_dequeue() {
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


// Cursor stuff

float x, y;

void cursor_init() {
  x = 100;
  y = 100;
}

void cursor_update() {
  if(key[ALLEGRO_KEY_UP])
    y--;
  if(key[ALLEGRO_KEY_DOWN])
    y++;
  if(key[ALLEGRO_KEY_LEFT])
    x--;
  if(key[ALLEGRO_KEY_RIGHT])
    x++;

  if (contpad.button & 0x0200) {         // L_JPAD / CONT_LEFT
    x--;
  } else if (contpad.button & 0x0100) {  // R_JPAD / CONT_RIGHT
    x++;
  }
  if (contpad.button & 0x0800) {         // U_JPAD / CONT_UP
    y--;
  } else if (contpad.button & 0x0400) {  // D_JPAD / CONT_DOWN
    y++;
  }
}

void cursor_draw() {
  al_draw_filled_rectangle(x, y, x + 10, y + 10, al_map_rgb(255, 0, 0));
}


// HUD stuff

ALLEGRO_FONT* hud_font;

void hud_init() {
  hud_font = al_create_builtin_font();
  //al_init_ttf_addon();
  // https://www.dafont.com/rollerball-1975.font
  //hud_font = al_load_ttf_font("rollerball_1975.ttf", 12, ALLEGRO_TTF_MONOCHROME);
  must_init(hud_font, "hud_font");
}

void hud_deinit() {
  al_destroy_font(hud_font);
}

void hud_update() {
}

void hud_draw() {
  al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 1, 1, 0, "X: %.1f Y: %.1f   FrameCount: %d", x, y, framecount);
  //al_draw_textf(hud_font, al_map_rgb_f(1, 1, 1), 1, 1, 0, "FrameCount: %d", framecount);
}


// Player stuff

void player_init() {
  s16 i;

  FUN_80053538_fiveliner();
  FUN_80053500_fiveliner();
  //inits_bunch_of_stuff_q_allocs_heap();
  for (i = 0; i < 4; i++) {
    g_PV_ptr = &g_PV_arr[i];
    FUN_069580_800A34A8_tenliner_allocs_heap(&g_PV_ptr->contQ);  // init contpad buttons and something else (8 * 300)
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

void player_deinit() {
  s16 i;
  ControllerQueue *contQ_ptr;

  for (i = 0; i < 4; i++) {
    contQ_ptr = controller_queues[i];
    n64HeapUnalloc((void *)contQ_ptr->unk14);
    n64HeapUnalloc((void *)contQ_ptr->_ControllerQueue);
  }
}


u32 D_801109F4;
s32 D_800D0550;

// Game stuff

// handicap values
u8 D_800CFF00[] = {
  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  0,  0,
  0,  5, 10, 15, 20, 25, 30, 35, 40, 45,  0,  0,
  0, 10, 20, 30, 40, 50, 60, 70, 80, 90,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0, 28,  0,  0,  0, 32,  0,  0,  0, 36,  0,
  0,  0, 40,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
};
u8 D_800CFF50 = 1;
Game g_game;

static s32 Game_80051104_sevenliner_num_players(Game *game_ptr) {
  register u32 i;
  register s32 var_a2;
  register u8 playercount = g_playercount;

  var_a2 = 0;
  for (i = 0; i < playercount; i++) {
    if (game_ptr->tetris_ptr_arr[i]->unk2) {
      var_a2++;
    }
  }
  return var_a2;
}

static void Game_800515f8_twoliner(Game *game_ptr) {
  if (game_ptr->unk3 != 0) {
    game_ptr->unk1 = 1;
  }
}

static void Game_ControllerRepeat_Update(Game *game_ptr) {
  register s32 i;
  register PlayerVars *temp_s1;
  register UnkStruct_1 *temp_s2;

  temp_s1 = &g_PV_arr[0];
  temp_s2 = &temp_s1->unk28;
  temp_s2->unk88 = temp_s1->unk1C->unk0;
  temp_s2->unk8C = temp_s1->unk24;
  debug_print2("ControllerRepeat_Update", "GU");
  FUN_026900_GU_or_ControllerRepeat_Update(temp_s2, temp_s2->unk88, D_801109F4);
}

void game_init() {
  register Game *game_ptr = &g_game;
  GameVars gameVars;
  register UnkStruct_1 *temp_s5;

  game_ptr->gameType = GAMETYPE_SPRINT;
  //game_ptr->gameType = GAMETYPE_ULTRA;
  //game_ptr->gameType = GAMETYPE_MARATHON;
  game_ptr->unkE4F8 = 7;  // which screen? (0..7)

  game_ptr->is_active = TRUE;
  D_800CFF50 = 1;
  game_ptr->numPlayers = 1;
  game_ptr->unkE4E8 = 0;  // gameElapsedTime
  game_ptr->topOutCount = 0;
  game_ptr->unk7 = 120;  // 120 jiffies (2 seconds delay after end of game before you can exit)
  switch (game_ptr->gameType) {
  case GAMETYPE_MARATHON:
    break;
  case GAMETYPE_SPRINT:
    game_ptr->unkE4F0 = 10800;  // 3 minutes (in jiffies)
    break;
  case GAMETYPE_ULTRA:
    game_ptr->unkE4F4 = 150;
    break;
  default:
    debug_print_reason_routine("Unknown GAMETYPE", "game_init");
    break;
  }
  game_ptr->unk0 = 0;
  game_ptr->unk3 = 0;
  g_playercount = 1;

  game_ptr->unkE4FC.alpha = 0.0f;
  game_ptr->unkE4FC.unk8 = 255.0f;
  game_ptr->unkE4FC.unk4 = (255.0f - game_ptr->unkE4FC.alpha) / 16.0f;
  game_ptr->unkE508 = TRUE;

  gameVars.seed = 0;
  gameVars.unk4 = &game_ptr->unkE080;
  gameVars.unk8 = game_ptr->unkE4F8;  // which screen? (0..7)
  gameVars.gameType = game_ptr->gameType;


  game_ptr->tetris_ptr_arr[0] = (Tetris *)n64HeapAlloc(sizeof(Tetris));
  Game_SetGlobalPointers(0);
  PlayerVars_SetGlobalPointers(0);

  temp_s5 = &g_PV_ptr->unk28;
  FUN_026900_80060ad4_oneliner_calls_fun(temp_s5);
  FUN_026900_80060b04_twelveliner_loops_32t(temp_s5, 0xF00, 8, 4);     // JPAD (U, D, R, L) only
  FUN_026900_80060b04_twelveliner_loops_32t(temp_s5, 0xC000, 16, 16);  // Buttons A and B only

  g_PV_ptr->unk20 = g_PV_ptr->unk24 = 0;
  gameVars.handicap = 0;

  Tetris_Init(game_ptr->tetris_ptr_arr[0], &gameVars);


  FUN_80041260_twoliner();
}

void game_deinit() {
  register Game *game_ptr = &g_game;

  if (!game_ptr->is_active) {
    debug_print_reason_routine("oops", "game_deinit");
  }
  game_ptr->is_active = FALSE;

  //FUN_027BF0_Deinit(0);
  //aiplayer_80042b3c_calls_heap_unalloc();
  //FUN_8004129c_fourliner();

  Game_SetGlobalPointers(0);
  Tetris_Deinit(game_ptr->tetris_ptr_arr[0]);
  n64HeapUnalloc((void *)game_ptr->tetris_ptr_arr[0]);
  game_ptr->tetris_ptr_arr[0] = NULL;

  //gamefinish_800534A4_fiveliner();
  //MultisquareGlow_8006b384_oneliner_calls_fun();
  //func_800763B4();
  //FUN_SRAM_n64HeapUnalloc_and_set_to_NULL(&game_ptr->unk8);  // deinit font?
  //Landfill_Deinit(&game_ptr->landfill);
  //CubeTiles_Deinit(&game_ptr->cubeTiles);
  //func_80075F5C(&game_ptr->unkE080);

  g_playercount = 0;
  game_ptr->unk0 = 3;
  rmonPrintf("Game_Deinit() : Done\n");
}

void _game_update(Game *game_ptr) {
  Game_SetGlobalPointers(0);
  PlayerVars_SetGlobalPointers(0);

  if ((D_800CFEE8 == 0xC) && (g_PV_arr[0].unk24 != 0)) {
    D_800D0550 = 4000;
  }

  Tetris_Update(game_ptr->tetris_ptr_arr[0]);
}

void game_update() {
  register Game *game_ptr = &g_game;

  if (!game_ptr->is_active) {
    debug_print_reason_routine("oops", "game_update");
  }
  if (game_ptr->unk0 != 1) {
    game_ptr->unk1 = 0;
    if (game_ptr->unk3 == 0) {
      if (Game_80051104_sevenliner_num_players(game_ptr) != 0) {
        game_ptr->unkE4E8 = game_ptr->unkE4E8 + D_801109F4;
      }
      /*
      func_800763EC(D_801109F4);
      */

      Game_ControllerRepeat_Update(game_ptr);

      /*
      if (game_ptr->unk0 == 0) {
        aiplayer_8004311c_largefunction();
      }
      if (D_800CFEE8 != 0xC) {
        Game_800519b4_thirtyliner(game_ptr);
      }
      */
      Game_800515f8_twoliner(game_ptr);
      if (game_ptr->unk1 != 1) {
        if (game_ptr->unk0 == 0) {
          _game_update(game_ptr);
        }
        /*
        Game_QueryGameOver(game_ptr);
        */
      }
    }
  }
}

void game_draw() {
  register Game *game_ptr = &g_game;

  if (!game_ptr->is_active) {
    debug_print_reason_routine("oops", "game_draw");
  }
  if (game_ptr->unk0 != 1) {
    FUN_027BF0_800636C0_display_game_stats_screen_q();
    g_landfill_ptr = &game_ptr->landfill;
    //func_80072A84();  // landfill render

    Game_SetGlobalPointers(0);
    PlayerVars_SetGlobalPointers(0);
    Tetris_Render(game_ptr->tetris_ptr_arr[0]);
  }
}


// Main loop

static void main_loop(ALLEGRO_EVENT_QUEUE* queue) {
  bool done = false;
  bool redraw = true;
  ALLEGRO_EVENT event;

  while (true) {
    al_wait_for_event(queue, &event);

    switch(event.type) {
    case ALLEGRO_EVENT_TIMER:
      framecount++;

      //D_801109F4 = func_800A3AF0();
      D_801109F4 = 1;

      contq_enqueue();
      contq_dequeue();
      game_update();
      cursor_update();
      hud_update();

      if(key[ALLEGRO_KEY_ESCAPE])
        done = true;

      redraw = true;
      break;

    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    }

    if(done)
      break;

    keyboard_update(&event);
    joystick_update(&event);

    if(redraw && al_is_event_queue_empty(queue)) {
      disp_pre_draw();
      al_clear_to_color(al_map_rgb(0x20, 0x20, 0x20));

      cursor_draw();

      game_draw();

      hud_draw();

      disp_post_draw();
      redraw = false;
    }
  }
}


// Main

int main() {
  must_init(al_init(), "allegro");
  must_init(al_install_keyboard(), "keyboard");
  must_init(al_install_joystick(), "joystick");

  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
  //ALLEGRO_TIMER* timer = al_create_timer(1.0 / 20.0);
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
  cursor_init();

  joystick_init(al_get_joystick(0));

  al_start_timer(timer);
  main_loop(queue);

  game_deinit();
  player_deinit();
  hud_deinit();
  disp_deinit();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
  al_destroy_font(font);

  return 0;
}

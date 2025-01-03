#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include "common.h"

void rmonPrintf(const char* fmt, ...) {
  int ans;
  va_list ap;

  va_start(ap, fmt);
  ans = vprintf(fmt, ap);
  va_end(ap);
}

u8 *n64HeapAlloc(s32 size) {
  return malloc(size);
}
void n64HeapUnalloc(u8 *pBlock) {
  free(pBlock);
}

// playervars
u16 D_800CFED4 = 1;
void func_80075DF4(void) {}  // cubetiles

void debug_print_reason_routine(u8 *arg0, u8 *arg1) {  // dbgprntrrl
  printf("Reason: %s\n Routine: %s\n", arg0, arg1);
}

void debug_print2(const u8 *arg0, const u8 *arg1) {
  /*
  printf("%25s | %s\n", arg1, arg0);
  */
}

OSMesg D_801235B0;  // audio
void *Audio2_Play_SFX(OSMesg *, s32 *, u8) {}
s32 D_800D3A90;

// TODO: will need to decomp these 003E40 funcs
u8 FUN_003E40_8003dbc0_twentyliner_nested_loops(u8, u8, u8) { return FALSE; }
u8 FUN_003E40_8003dda8_twentyfiveliner_nested_loops(u8, u8, u8) { return FALSE; }

u32 D_801109F4;
s32 D_800D0550;

// game

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

  /*
  printf("temp_s2->unk80 = %d\n", temp_s2->unk80);
  printf("temp_s2->unk84 = %d\n", temp_s2->unk84);
  printf("temp_s2->unk88 = %d\n", temp_s2->unk88);
  printf("temp_s2->unk8C = %d\n", temp_s2->unk8C);
  */
}


u8 D_800CFEE8 = 0xF;

// TODO: decomp these
void LineScan_80069830_elevenliner_loops_20_times(LineScan *) {}
void LineScan_800698e0_largeliner_loops_20_times_plays_sfx(LineScan *) {}

// 01D6E0
Gfx *g_gdl;
void func_8005BBFC(Gfx **) {}
void func_8005BE40(Gfx **) {}

void displayText_XY_RGBA_2(Gfx **, void *, s16, s16, u8 *, s32, s32, s32, s32) {}

// 066700
s32 func_800A2EF0(f32 arg0) { return arg0; }

// pfgfx
PfGfx *g_pfGfx_ptr;
void GameCamera_Render(void) {}
Point *PFGFX_Init(Point *arg0, PfGfx *arg1) { return arg0; }
void PFGFX_Playfield_Init(u8) {}


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

void joystick_update(ALLEGRO_EVENT* event) {
  switch(event->type) {
  case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
    al_reconfigure_joysticks();
    print_joystick_info(al_get_joystick(0));
    break;
  }
}


// ContPad stuff

OSContPad contpad;

void snapshot_contpad(ALLEGRO_JOYSTICK *joy, OSContPad *contpad) {
  ALLEGRO_JOYSTICK_STATE jst;
  int i;

  if (joy == NULL) {
    return;
  }

  al_get_joystick_state(joy, &jst);

  /*
  printf("\n");
  for (i = 0; i < al_get_joystick_num_buttons(joy); i++) {
    printf("jst.button[%d] = %d\n", i, jst.button[i]);
  }
  for (i = 0; i < al_get_joystick_num_axes(joy, 2); i++) {
    printf("jst.stick[2].axis[%d] = %f\n", i, jst.stick[2].axis[i]);
  }
  */

  contpad->button = 0x0000;

  if (jst.button[1] >= 16384) contpad->button |= 0x8000;         // A_BUTTON     / CONT_A
  if (jst.button[2] >= 16384) contpad->button |= 0x4000;         // B_BUTTON     / CONT_B
  if (jst.button[4] >= 16384) contpad->button |= 0x0020;         // L_TRIG       / CONT_L
  if (jst.button[5] >= 16384) contpad->button |= 0x0010;         // R_TRIG       / CONT_R
  if (jst.button[6] >= 16384) contpad->button |= 0x2000;         // Z_TRIG       / CONT_G
  if (jst.button[9] >= 16384) contpad->button |= 0x1000;         // START_BUTTON / CONT_START

  if (jst.stick[2].axis[0] < 0) contpad->button |= 0x0200;       // L_JPAD       / CONT_LEFT
  else if (jst.stick[2].axis[0] > 0) contpad->button |= 0x0100;  // R_JPAD       / CONT_RIGHT
  if (jst.stick[2].axis[1] < 0) contpad->button |= 0x0800;       // U_JPAD       / CONT_UP
  else if (jst.stick[2].axis[1] > 0) contpad->button |= 0x0400;  // D_JPAD       / CONT_DOWN
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

ALLEGRO_FONT* font;

void hud_init() {
  font = al_create_builtin_font();
  must_init(font, "font");
}

void hud_deinit() {
  al_destroy_font(font);
}

void hud_update() {
}

void hud_draw() {
  al_draw_textf(font, al_map_rgb_f(1, 1, 1), 1, 1, 0, "X: %.1f Y: %.1f   FrameCount: %d", x, y, framecount);
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
    n64HeapUnalloc((u8 *)contQ_ptr->unk14);
    n64HeapUnalloc((u8 *)contQ_ptr->_ControllerQueue);
  }
}


// Game stuff

void game_init() {
  register Game *game_ptr = &g_game;
  GameVars gameVars;
  register UnkStruct_1 *temp_s5;

  game_ptr->gameType = GAMETYPE_SPRINT;
  game_ptr->unkE4F8 = 7;  // which screen? (0..7)

  game_ptr->active = TRUE;
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

  gameVars.seed = 3;
  gameVars.unk4 = &game_ptr->unkE080;
  gameVars.unk8 = game_ptr->unkE4F8;  // which screen? (0..7)
  gameVars.gameType = game_ptr->gameType;


  game_ptr->tetris_ptr_arr[0] = (Tetris *)n64HeapAlloc(sizeof(Tetris));
  Game_SetGlobalPointers(0);
  PlayerVars_SetGlobalPointers(0);

  temp_s5 = &g_PV_ptr->unk28;  // UnkStruct_1
  FUN_026900_80060ad4_oneliner_calls_fun(temp_s5);
  FUN_026900_80060b04_twelveliner_loops_32t(temp_s5, 0xF00, 8, 4);  // JPAD (U, D, R, L) only
  FUN_026900_80060b04_twelveliner_loops_32t(temp_s5, 0xC000, 16, 16);  // Buttons A and B only

  g_PV_ptr->unk20 = g_PV_ptr->unk24 = 0;
  gameVars.handicap = 0;

  Tetris_Init(game_ptr->tetris_ptr_arr[0], &gameVars);
}

void game_deinit() {
  register Game *game_ptr = &g_game;

  // TODO: change this to is_active
  if (!game_ptr->active) {
    debug_print_reason_routine("oops", "game_deinit");
  }
  game_ptr->active = FALSE;

  //FUN_027BF0_Deinit(0);
  //aiplayer_80042b3c_calls_heap_unalloc();
  //FUN_8004129c_fourliner();

  Game_SetGlobalPointers(0);
  Tetris_Deinit(game_ptr->tetris_ptr_arr[0]);
  n64HeapUnalloc((u8 *)game_ptr->tetris_ptr_arr[0]);
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

  if (!game_ptr->active) {
    debug_print_reason_routine("oops", "game_update");
  }
  if (game_ptr->unk0 != 1) {
    game_ptr->unk1 = 0;
    if (game_ptr->unk3 == 0) {
      /*
      if (Game_80051104_sevenliner_num_players(game_ptr) != 0) {
        game_ptr->unkE4E8 = game_ptr->unkE4E8 + D_801109F4;
      }
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
      Game_800515f8_twoliner(game_ptr);
      */
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

  if (!game_ptr->active) {
    debug_print_reason_routine("oops", "game_draw");
  }
  if (game_ptr->unk0 != 1) {
    //FUN_027BF0_800636C0_display_game_stats_screen_q();
    g_landfill_ptr = &game_ptr->landfill;
    //func_80072A84();

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
      al_clear_to_color(al_map_rgb(0,0,0));

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
  //ALLEGRO_TIMER* timer = al_create_timer(1.0 / 1.0);
  must_init(timer, "timer");

  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  must_init(queue, "queue");

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

  print_joystick_info(al_get_joystick(0));

  al_start_timer(timer);
  main_loop(queue);

  game_deinit();
  player_deinit();
  hud_deinit();
  disp_deinit();
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);

  return 0;
}

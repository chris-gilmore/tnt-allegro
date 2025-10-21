#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;
extern int g_screen;
extern f32 D_8012903C_f;

////////////////////////////////////////

extern u16 draw_buffer;
extern s8 D_800CF830;
extern s8 D_800CF834;
extern s8 D_800CF838;
extern s8 D_800CF83C;
extern u8 D_800CFD48;
extern u8 D_800CFD4C;

////////////////////////////////////////

Font D_80128EB0;
Font D_80128F28;
Font D_80128FA0;
static char *D_80129018;  // (str) lines dumped to game pak
static void *D_8012901C;
static void *D_80129020;
static void *D_80129024;
static void *D_80129028;
static UnkStruct_78 *D_8012902C[1];

u8 D_800D3CF0 = 0;
s32 D_800D3CF4 = 0;
UnkStruct_77 *D_800D3CF8 = NULL;
void *D_800D3CFC = NULL;
s32 D_800D3D00[4] = { 1, 1, 1, 1 };
s32 D_800D3D10[4] = { 1, 1, 1, 1 };
static s32 D_800D3D20 = 0;
static s8 D_800D3D24 = 0;
static f32 D_800D3D28 = 1;
static s32 D_800D3D2C = 0;
static u8 D_800D3D30 = FALSE;
u8 D_800D3D34 = 0;
static s32 D_800D3D38 = 1;
static Font *D_800D3D3C[3] = { &D_80128EB0, &D_80128F28, &D_80128FA0 };
static char *D_800D3D48[16] = {
  "MOROCCO.",
  "DVIE.",
  "POLYASIA.",
  "FLOPPY.",
  "PYRAMID.",
  "GIALI.",
  "THREAD6.",
  "HALUCI.",
  "MAYAN.",
  "GREEK.",
  "EGYPT.",
  "CELTIC.",
  "AFRICA.",
  "JAPAN.",
  "KALINKA.",
  "TITLE.",
};
static u8 D_800D3D88 = FALSE;
static s32 D_800D3D8C = 0;  // unused
static s32 D_800D3D90 = 0;
static u8 D_800D3D94 = 0;
static u8 handicap[4] = { 0, 0, 0, 0 };
static u8 D_800D3D9C = 10;
static char D_800D3DA0[45] = {
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
  'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3',
  '4', '5', '6', '7', '8', '9', ':', '%', '?', '"', '(', ')', ' ', '[', '\\'
};

static s32 D_800D3DD0 = 0;  // lines dumped to game pak
static u8 D_800D3DD4 = 0;
u8 D_800D3DD8 = 0;
static s32 D_800D3DDC = 0;  // unused
static s32 D_800D3DE0 = 0;  // unused
static s32 D_800D3DE4 = 8;
static s32 D_800D3DE8 = 0;    // cpak note extension name incrementer
static u8 D_800D3DEC = 0x1A;  // cpak note extension name base 'A' (N64 font code)
static s32 D_800D3DF0 = 0;
static s32 D_800D3DF4 = 0;
static s32 D_800D3DF8 = 0;
static s32 D_800D3DFC = 0;
static s32 D_800D3E00 = 0;
static s32 D_800D3E04 = 0;
static s32 D_800D3E08 = 0;
static s32 D_800D3E0C = 0;
static s32 D_800D3E10 = 0;
static s32 D_800D3E14 = 0;
static s32 D_800D3E18 = 0;
static s32 D_800D3E1C = 0;
static s32 D_800D3E20 = 0;

static f32 D_800D3E24 = 0;
static f32 D_800D3E28 = 0.05;
static f32 D_800D3E2C = 0;
static f32 D_800D3E30 = 1.0/9;
static s32 D_800D3E34 = 0;
static s32 D_800D3E38 = 0;  // unused
static s32 D_800D3E3C = 0;  // unused
static s32 D_800D3E40 = 8;

static void   func_8008FF78(UnkStruct_78 *);
static void   func_8009098C(UnkStruct_78 *);
static void   func_80090AC0(UnkStruct_78 *);
static s32    func_80091440(UnkStruct_78 *, s32, s32 *);
static s32    func_80091744(UnkStruct_78 *, s32, s32 *);
static void   func_80091A8C(UnkStruct_78 *);
static void   func_80091D60(GUI_Textbox *, UnkStruct_78 *, s32, f32);
static void   func_80099674(UnkStruct_78 *);

void func_8008F280(UnkStruct_78 *arg0, s32 img_id, s32 width, s32 height, void *arg4) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  if (img_id == -1) {
    arg0->img = arg4;
  } else {
    arg0->img = al_load_bitmap(config_setting_get_string_elem(images, img_id));

  }
  arg0->width = width;
  arg0->height = height;
  arg0->unk114 = 0;
  arg0->unk134 = 0;
  arg0->unk128 = 0;
  arg0->unk120 = 0;
  func_8009F2DC(arg0);
}

void func_8008F360(UnkStruct_78 *arg0, UnkStruct_77 *arg1, u32 *arg2) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  u8 i, j;
  GUI_Slider  *gui_slider;
  GUI_Toggle  *gui_toggle;
  GUI_Textbox *gui_textbox;
  s32 tmp;

  arg0->unk124 = arg1;
  i = 0;
  main_8004A34C_threeliner();

  rmonPrintf("\n");
  for (i = 0; (arg0->unk124[i].unk24 & GUI_QUIT) != GUI_QUIT; i++) {
    // DEBUG: print gui elements
    func_8009D400(arg0->unk124[i].unk24);

    if ((arg0->unk124[i].unk24 & GUI_NULL) != GUI_NULL) {
      arg0->unk124[i].unk0.a = 0xA0;
    }
    if (arg0->unk124[i].unk24 & GUI_SLIDER) {
      gui_slider = arg0->unk124[i].unk30;

      if (gui_slider->ids[0] != 0) {
        gui_slider->track.data.img = al_load_bitmap(config_setting_get_string_elem(images, gui_slider->ids[0]));

        gui_slider->marks[0].data.img = al_load_bitmap(config_setting_get_string_elem(images, gui_slider->ids[2]));
      }

      for (j = 0; j < gui_slider->num_ticks; j++) {
        gui_slider->marks[j].data.img = gui_slider->marks[0].data.img;
      }
    }

    if (arg0->unk124[i].unk24 & GUI_TOGGLE) {
      gui_toggle = arg0->unk124[i].unk30;

      for (j = 0; j < gui_toggle->num; j++) {
        if (gui_toggle->ids[j * 2] != 0) {
          gui_toggle->unk4[j].data.img = al_load_bitmap(config_setting_get_string_elem(images, gui_toggle->ids[j * 2]));
        }
      }
    }

    if (arg0->unk124[i].unk24 & GUI_TEXTBOX) {
      gui_textbox = arg0->unk124[i].unk30;
      gui_textbox->unk14.data.img = al_load_bitmap(config_setting_get_string_elem(images, gui_textbox->id));
    }

    if (arg0->unk124[i].unk24 & GUI_PIC) {
      if (arg2[i * 2] != 0) {
        arg0->unk124[i].unk0.data.img = al_load_bitmap(config_setting_get_string_elem(images, arg2[i * 2]));
      }
    }
  }

  if (D_800D5D48 == arg1) {
    D_800D3D00[0] = 3;
    D_800D3D00[1] = 4;
    D_800D3D00[2] = 5;
    D_800D3D00[3] = 6;
    D_800D3D10[0] = 3;
    D_800D3D10[1] = 4;
    D_800D3D10[2] = 5;
    D_800D3D10[3] = 6;
  }

  if (D_800D5850 == arg1) {
    D_800D3D00[0] = 3;
    D_800D3D00[1] = 0;
    D_800D3D00[2] = 0;
    D_800D3D00[3] = 0;
    D_800D3D10[0] = 3;
    D_800D3D10[1] = 0;
    D_800D3D10[2] = 0;
    D_800D3D10[3] = 0;
  }

  if (D_800D5180 == arg1) {
    D_800D3D00[0] = 5;
    D_800D3D10[0] = 5;
    D_800D5170.cur = 0;
    D_800D5180[8].unk0.x = 5;
  }

  if (D_800D42B4 == arg1) {
    /*
    FUN_001050_8003b5d0_controller_sendrecvmsg(&superThread);
    tmp = FUN_001050_getControllerStatus(&superThread, 0);
    if (tmp & CONT_CARD_ON) {
    tmp = FUN_001050_cpakInit(&superThread, 0);
    } else {
    */
    for (i = 0; (arg0->unk124[i].unk24 & GUI_QUIT) != GUI_QUIT; i++) {
      if (arg0->unk124[i + 1].unk24 & GUI_QUIT) {
        arg0->unk124[i + 1].unk0.x = 5;
        D_800D3D10[0] = D_800D3D00[0];
        break;
      }
    }
    D_800D42B4[3].unk24 = GUI_NULL;
    D_800D42B4[4].unk24 = GUI_NULL;
    /*
    }
    */
    for (i = 0; (arg0->unk124[i].unk24 & GUI_QUIT) != GUI_QUIT; i++) {
      if (arg0->unk124[i + 1].unk24 & GUI_QUIT) {
        if (arg0->unk124[i + 1].unk0.x == 8) {
          arg0->unk124[i + 1].unk0.x = 5;
        }
        D_800D3D10[0] = D_800D3D00[0];
        break;
      }
    }
    D_800D42B4[8].unk24 = GUI_NULL;
  }

  if (!D_800D3D88 && (D_800D4E1C == arg1)) {
    for (i = 0; (arg0->unk124[i].unk24 & GUI_QUIT) != GUI_QUIT; i++) {
      if (arg0->unk124[i + 1].unk24 & GUI_QUIT) {
        arg0->unk124[i + 1].unk0.x = 3;
        D_800D3D10[0] = D_800D3D00[0];
        break;
      }
    }
    if (g_sram_ptr->song == 0) {
      j = 15;
    } else {
      j = g_sram_ptr->song - 1;
    }
    for (i = 0; D_800D3D48[j][i] != '.'; i++) {
      D_800D2DC8.name[i] = D_800D3D48[j][i];
    }
    D_800D2DC8.name[i] = 0;
  }

  if ((arg0->unk124 == D_800D5850) || (arg0->unk124 == D_800D5D48) || (arg0->unk124 == D_800D42B4) || (arg0->unk124 == D_800D5180)) {
    if (D_80129024 == NULL) {
      D_80129024 = al_load_bitmap(config_setting_get_string_elem(images, IMG_GAMECART));
    }
    if (D_80129020 == NULL) {
      D_80129020 = al_load_bitmap(config_setting_get_string_elem(images, IMG_GAMEPAK));
    }
    if (D_80129028 == NULL) {
      D_80129028 = al_load_bitmap(config_setting_get_string_elem(images, IMG_RECTANGLE));
    }
  }

  D_800D3D38 = 1;
}

static void func_8008FF78(UnkStruct_78 *arg0) {
  u8 i, j;
  GUI_Slider  *gui_slider;
  GUI_Toggle  *gui_toggle;
  GUI_Textbox *gui_textbox;

  main_8004A34C_threeliner();
  if ((arg0->unk124 == D_800D5850) || (arg0->unk124 == D_800D5D48) || (arg0->unk124 == D_800D42B4) || (arg0->unk124 == D_800D5180)) {
    if (D_80129028 != NULL) {
      al_destroy_bitmap(D_80129028);
      D_80129028 = NULL;
    }
    if (D_80129020 != NULL) {
      al_destroy_bitmap(D_80129020);
      D_80129020 = NULL;
    }
    if (D_80129024 != NULL) {
      al_destroy_bitmap(D_80129024);
      D_80129024 = NULL;
    }
  }

  for (i = 0; (arg0->unk124[i].unk24 & GUI_QUIT) != GUI_QUIT; i++) {
    if (arg0->unk124[i].unk24 & GUI_SLIDER) {
      gui_slider = arg0->unk124[i].unk30;
      if (gui_slider->ids[0] != 0) {
        al_destroy_bitmap(gui_slider->track.data.img);
        al_destroy_bitmap(gui_slider->marks[0].data.img);
      }
    }

    if (arg0->unk124[i].unk24 & GUI_TOGGLE) {
      gui_toggle = arg0->unk124[i].unk30;
      for (j = 0; j < gui_toggle->num; j++) {
        if (gui_toggle->ids[j * 2] != 0) {
          if (gui_toggle->unk4[j].data.img != NULL) {
            al_destroy_bitmap(gui_toggle->unk4[j].data.img);
            gui_toggle->unk4[j].data.img = NULL;
          }
        }
      }
    }

    if (arg0->unk124[i].unk24 & GUI_TEXTBOX) {
      gui_textbox = arg0->unk124[i].unk30;
      al_destroy_bitmap(gui_textbox->unk14.data.img);
    }

    if (arg0->unk124[i].unk24 & GUI_PIC) {
      if (arg0->unk124[i].unk0.data.img != NULL) {
        al_destroy_bitmap(arg0->unk124[i].unk0.data.img);
        arg0->unk124[i].unk0.data.img = NULL;
      }
    }
  }
}

void func_8009035C(UnkStruct_77 *arg0, u32 *arg1) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  s32 i;
  UnkStruct_1 *sp30;

  for (i = 0; i < 4; i++) {
    sp30 = &g_PV_arr[i].unk28;
    FUN_026900_80060ad4_oneliner_calls_fun(sp30);
    FUN_026900_80060b04_twelveliner_loops_32t(sp30, 0xF00, 32, 10);   // JPAD (U, D, R, L) only
    FUN_026900_80060b04_twelveliner_loops_32t(sp30, 0xC000, 16, 16);  // Buttons A and B only
    g_PV_arr[0].unk20 = g_PV_arr[i].unk24 = 0;  // (bug?) why [0]?
  }
  D_800CFED4 = 4;
  D_800D3CF0 = 0;
  func_8008F360(&D_801290D0, arg0, arg1);

  //D_801290D0.img = n64HeapAlloc(240008);
  D_801290D0.img = al_create_bitmap(400, 300);

  //func_800A8FC8(D_801290D0.img, 120004, 0);
  ALLEGRO_BITMAP* cfbuffer = al_get_target_bitmap();
  al_set_target_bitmap(D_801290D0.img);
  al_clear_to_color(al_map_rgba(0, 0, 0, 0));
  al_set_target_bitmap(cfbuffer);

  func_8008F280(&D_801290D0, -1, 400, 300, D_801290D0.img);

  D_8012901C = al_load_bitmap(config_setting_get_string_elem(images, IMG_CURSOR));
  Font_Init46Char(&D_80128EB0, IMG_FONT_A);
  Font_Init46Char(&D_80128F28, IMG_FONT_B);
  Font_Init46Char(&D_80128FA0, IMG_FONT_C);
  func_8009FA2C(&D_801290D0);
  D_800D3CF8 = NULL;
  Audio_LoadSFX(&D_800D3988);
  for (i = 0; i < 4; i++) {
    D_800D3FF8[3 + i].unk0.a = 0xA0;
    D_800D3FF8[3 + i].unk0.r = 0xFF;
    D_800D3FF8[3 + i].unk0.g = 0xFF;
    D_800D3FF8[3 + i].unk0.b = 0xFF;
  }
}

void func_800905E8(u8 arg0) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  s32 i;
  UnkStruct_1 *sp30;

  for (i = 0; i < 4; i++) {
    sp30 = &g_PV_arr[i].unk28;
    FUN_026900_80060ad4_oneliner_calls_fun(sp30);
    FUN_026900_80060b04_twelveliner_loops_32t(sp30, 0xF00, 32, 10);   // JPAD (U, D, R, L) only
    FUN_026900_80060b04_twelveliner_loops_32t(sp30, 0xC000, 16, 16);  // Buttons A and B only
    g_PV_arr[0].unk20 = g_PV_arr[i].unk24 = 0;  // (bug?) why [0]?
  }

  func_800A3550();  // init rand
  D_800CFED4 = 4;
  D_800D3CF0 = 0;
  D_80129030 = 400;
  D_80129034 = 300;
  D_80129038 = 50;
  //D_8012903C = 37;
  D_8012903C_f = 37.5;
  func_800A36F0(-50, 50);
  func_8008F360(&D_801290D0, D_800D3FF8, D_800D3FB0);

  //D_801290D0.img = n64HeapAlloc(240008);
  D_801290D0.img = al_create_bitmap(400, 300);

  //func_800A8FC8(D_801290D0.img, 120004, 0);
  ALLEGRO_BITMAP* cfbuffer = al_get_target_bitmap();
  al_set_target_bitmap(D_801290D0.img);
  al_clear_to_color(al_map_rgba(0, 0, 0, 0));
  al_set_target_bitmap(cfbuffer);

  func_8008F280(&D_801290D0, -1, 400, 300, D_801290D0.img);

  Audio_LoadSFX(&D_800D3988);
  func_800A36F0(-50, 50);
  func_800A36F0(-50, 50);
  D_8012902C[0] = &D_801290D0;
  if (arg0 == 0) {
    D_800D3D00[0] = 3;
    D_800D3D00[1] = 0;
    D_800D3D00[2] = 0;
    D_800D3D00[3] = 0;
    D_800D3D10[0] = 3;
    D_800D3D10[1] = 0;
    D_800D3D10[2] = 0;
    D_800D3D10[3] = 0;
  }
  D_800D3CF4 = 0;
  D_8012901C = al_load_bitmap(config_setting_get_string_elem(images, IMG_CURSOR));
  for (i = 0; i < 4; i++) {
    D_800D3FF8[3 + i].unk0.a = 0xA0;
    D_800D3FF8[3 + i].unk0.r = 0xFF;
    D_800D3FF8[3 + i].unk0.g = 0xFF;
    D_800D3FF8[3 + i].unk0.b = 0xFF;
  }
  Font_Init46Char(&D_80128EB0, IMG_FONT_A);
  Font_Init46Char(&D_80128F28, IMG_FONT_B);
  Font_Init46Char(&D_80128FA0, IMG_FONT_C);
  func_8009FA2C(&D_801290D0);
  D_800D3CF8 = NULL;
}

static void func_8009098C(UnkStruct_78 *arg0) {
  main_8004A34C_threeliner();
  if (D_80128EB0.image != NULL) {
    Font_Deinit(&D_80128EB0);
  }
  if (D_80128F28.image != NULL) {
    Font_Deinit(&D_80128F28);
  }
  if (D_80128FA0.image != NULL) {
    Font_Deinit(&D_80128FA0);
  }
  if (arg0->img != NULL) {
    al_destroy_bitmap(arg0->img);
    arg0->img = NULL;
  }
  func_8009F338(arg0);
}

void func_80090A44(void) {
  s32 i;

  main_8004A34C_threeliner();
  for (i = 0; i < 3; i++) {
    // empty
  }
  if (D_8012901C != NULL) {
    al_destroy_bitmap(D_8012901C);
    D_8012901C = NULL;
  }
  func_8008FF78(&D_801290D0);
  func_8009098C(&D_801290D0);
  D_800D3CF8 = NULL;
}

static void func_80090AC0(UnkStruct_78 *arg0) {
  s32 i;

  if ((arg0->unk114 != 0) && (D_800D3CF8 != NULL)) {
    for (i = 0; (arg0->unk124[i].unk24 & GUI_QUIT) != GUI_QUIT; i++) {
      if (arg0->unk124[i + 1].unk24 & GUI_QUIT) {
        arg0->unk124[i + 1].unk0.x = D_800D3D00[0];
        D_800D3D10[0] = D_800D3D00[0];
        break;
      }
    }

    main_8004A34C_threeliner();
    func_8008FF78(&D_801290D0);
    func_8009098C(&D_801290D0);
    func_8008F360(&D_801290D0, D_800D3CF8, D_800D3CFC);

    //D_801290D0.img = n64HeapAlloc(240008);
    D_801290D0.img = al_create_bitmap(400, 300);

    //func_800A8FC8(D_801290D0.img, 120004, 0);
    ALLEGRO_BITMAP* cfbuffer = al_get_target_bitmap();
    al_set_target_bitmap(D_801290D0.img);
    al_clear_to_color(al_map_rgba(0, 0, 0, 0));
    al_set_target_bitmap(cfbuffer);

    func_8008F280(&D_801290D0, -1, 400, 300, D_801290D0.img);

    Font_Init46Char(&D_80128EB0, IMG_FONT_A);
    Font_Init46Char(&D_80128F28, IMG_FONT_B);
    Font_Init46Char(&D_80128FA0, IMG_FONT_C);
    D_800D3CF4 = 0;
    D_800D3CF8 = NULL;

    if (D_800D3D90 == 0) {
      if ((D_800CFEE8 != 11) && (D_800CFEE8 != 10)) {
        func_8009FA2C(&D_801290D0);
      }
    } else {
      D_800D3D90 = 0;
    }

    if (arg0->unk124 == D_800D5850) {
      D_800D3D00[0] = 3;
      D_800D3D10[0] = D_800D3D00[0];
      return;
    }

    if (arg0->unk124 == D_800D5D48) {
      D_800D3D00[0] = 3;
      D_800D3D10[0] = D_800D3D00[0];
      return;
    }

    for (i = 0; (arg0->unk124[i].unk24 & GUI_QUIT) != GUI_QUIT; i++) {
      if (arg0->unk124[i + 1].unk24 & GUI_QUIT) {
        D_800D3D00[0] = arg0->unk124[i + 1].unk0.x;
        D_800D3D10[0] = D_800D3D00[0];
        break;
      }
    }
  }
}

void func_80090E08(void) {
  s32 i;
  s32 sp48;  // unused
  GUI_Textbox *gui_textbox_1;
  GUI_Textbox *gui_textbox_2;
  GUI_Textbox *gui_textbox_3;
  GUI_Textbox *gui_textbox_4;
  GUI_Textbox *gui_textbox_5;
  register Game *game_ptr = &g_game;
  s32 sp2C;  // unused
  s32 sp28;  // unused
  UnkStruct_1 *sp24;

  if (D_800D3CF0 == 1) {  // game mode
    main_8004A34C_threeliner();
    func_80090A44();
    D_800CFEE8 = 9;
    if (D_800CF838 >= 7) {
      game_ptr->unkE4F8 = func_800A35EC(0, 7);
    } else {
      game_ptr->unkE4F8 = func_800A35EC(0, D_800CF838);
    }

    if (g_screen != -1) {
      game_ptr->unkE4F8 = g_screen;
    }
    printf("Screen: '%d'\n", game_ptr->unkE4F8);

    FUN_027BF0_check_music_settings_and_play(game_ptr->unkE4F8);
    Audio_LoadSFX(&D_800D3A90);
    Game_Init(D_800CFED4, handicap);
    if (D_800D3D20 != 0) {
      D_800D3D20 = 0;
    }
    D_800D3CF0 = 0;
    main_8004A34C_threeliner();

  } else if (D_800D3CF0 == 3) {  // attract mode
    printf("-- attract mode\n");

    /*
    main_8004A34C_threeliner();
    func_80090A44();
    if (func_800A35EC(0, 10) < 8) {
      D_800CFEE8 = 12;
      g_game.landfill.type = LANDFILLTYPE_NONE;
      g_game.gameType = GAMETYPE_MARATHON;
      if (D_800CF838 >= 7) {
        game_ptr->unkE4F8 = func_800A35EC(0, 7);
      } else {
        game_ptr->unkE4F8 = func_800A35EC(0, D_800CF838);
      }
      FUN_027BF0_check_music_settings_and_play(game_ptr->unkE4F8);
      Audio_LoadSFX(&D_800D3A90);
      func_8007A078(&D_800D2D80, 0);
      aiplayer_gameinit_related(1, 0, 6);
      D_800CFED4 = 1;
      Game_Init(1, handicap);
      D_800D3CF0 = 0;
    } else {
      D_800CFEE8 = 3;
      D_800CFD48 = TRUE;
      D_800CFD4C = TRUE;
    }
    */

  } else if (D_800D3CF0 == 2) {  // wonders progress
    printf("-- wonders progress\n");

    /*
    if (D_800D3D9C == 5) {
      main_8004A34C_threeliner();
      func_80090A44();
    }
    if (D_800D3D9C-- == 0) {
      D_800D3D9C = 10;
      wonders1_anim_related(D_800CF830);
      D_801109F0 = 4;
      D_800CFEE8 = 7;
      D_800D3CF0 = 0;
    }
    */

  } else if (D_800D3CF0 == 4) {  // haluci mode
    main_8004A34C_threeliner();
    func_80090A44();
    D_800CFEE8 = 13;
    func_8007CF40(1);  // haluci_init(1);
    D_800D3CF0 = 0;

  } else if (D_800D3CF0 == 5) {  // scroll credits
    main_8004A34C_threeliner();
    func_80090A44();
    D_800CFEE8 = 16;
    D_800D3CF0 = 0;

  } else {
    if (D_800D5D48 == D_801290D0.unk124) {
      gui_textbox_1 = D_801290D0.unk124[3].unk30;
      gui_textbox_2 = D_801290D0.unk124[4].unk30;
      gui_textbox_3 = D_801290D0.unk124[5].unk30;
      gui_textbox_4 = D_801290D0.unk124[6].unk30;
      if (((gui_textbox_1->unk5C == 0xFF) && (gui_textbox_1->node->pack & 0x10) &&
           (gui_textbox_2->unk5C == 0xFF) &&
           (gui_textbox_3->unk5C != 0xFF) &&
           (gui_textbox_4->unk5C != 0xFF)) ||
          ((gui_textbox_1->unk5C == 0xFF) && (gui_textbox_1->node->pack & 0x10) &&
           (gui_textbox_2->unk5C == 0xFF) &&
           (gui_textbox_3->unk5C == 0xFF) &&
           (gui_textbox_4->unk5C != 0xFF)) ||
          ((gui_textbox_1->unk5C == 0xFF) && (gui_textbox_1->node->pack & 0x10) &&
           (gui_textbox_2->unk5C == 0xFF) &&
           (gui_textbox_3->unk5C == 0xFF) &&
           (gui_textbox_4->unk5C == 0xFF))) {
        if (D_800D3D94 == 0) {
          D_800D3D34 = 1;
        } else {
          D_800D3D34 = 0;
        }
      } else {
        D_800D3D34 = 0;
      }
    }

    if (D_800D5850 == D_801290D0.unk124) {
      gui_textbox_5 = D_801290D0.unk124[3].unk30;
      if (gui_textbox_5->unk5C == 0xFF) {
        if (gui_textbox_5->node->pack & 0x10) {
          D_800D3D34 = 1;
        } else {
          D_800D3D34 = 0;
        }
      } else {
        D_800D3D34 = 0;
      }
    }

    for (i = 0; i < 4; i++) {
      sp24 = &g_PV_arr[i].unk28;
      sp24->unk88 = g_PV_arr[i].unk1C->unk0;
      sp24->unk8C = g_PV_arr[i].unk24;
      debug_print2("ControllerRepeat_Update", "MainMenu");
      FUN_026900_GU_or_ControllerRepeat_Update(sp24, sp24->unk88, func_800A3AF0());
    }

    func_8009D5E4();
  }
}

static s32 func_80091440(UnkStruct_78 *arg0, s32 arg1, s32 *arg2) {
  register UnkStruct_77 *temp_s0 = arg0->unk124;
  s32 sp28;
  s32 sp24;

  func_800A35EC(0, 0xFF);
  if (D_800D3D94 != 0) {
    Audio2_Play_SFX(&D_801235B0, &D_800D3988, 3);
    return arg1;
  }

  if (arg0->unk114 == 0) {
    func_8009DDF4(arg0);
    if (D_800D3D20 != 0) {
      D_800D3D20 = 0;
    }
  }

  for (sp28 = 0; (temp_s0[sp28].unk24 & GUI_QUIT) != GUI_QUIT; sp28++) {
    if (temp_s0[sp28].unk24 & GUI_NULL) {
      continue;
    }

    temp_s0[sp28].unk0.a = 0xA0;
    temp_s0[sp28].unk0.r = 0xFF;
    temp_s0[sp28].unk0.g = 0xFF;
    temp_s0[sp28].unk0.b = 0xFF;
  }
  sp24 = sp28 - 1;

  temp_s0[arg1].unk0.a = 0xA0;
  temp_s0[arg1].unk0.r = 0xFF;
  temp_s0[arg1].unk0.g = 0xFF;
  temp_s0[arg1].unk0.b = 0xFF;

  *arg2 = arg1;

  sp28 = arg1 - 1;
  while (sp28 >= 0) {
    if (sp28 == 0) {
      sp28 = sp24;
    }
    if (temp_s0[sp28].unk24 & GUI_NULL) {
      if (temp_s0[sp28].unk24 & GUI_TEXTBOX) {
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 1);
        return sp28;
      }
    } else {
      Audio2_Play_SFX(&D_801235B0, &D_800D3988, 1);
      return sp28;
    }
    sp28--;
  }

  return arg1;
}

static s32 func_80091744(UnkStruct_78 *arg0, s32 arg1, s32 *arg2) {
  register UnkStruct_77 *temp_s0 = arg0->unk124;
  s32 sp28;
  s32 sp24;  // unused

  func_800A35EC(0, 0xFF);
  if (D_800D3D94 != 0) {
    Audio2_Play_SFX(&D_801235B0, &D_800D3988, 3);
    return arg1;
  }

  if (arg0->unk114 == 0) {
    func_8009DDF4(arg0);
    if (D_800D3D20 != 0) {
      D_800D3D20 = 0;
    }
  }

  for (sp28 = 0; (temp_s0[sp28].unk24 & GUI_QUIT) != GUI_QUIT; sp28++) {
    if (temp_s0[sp28].unk24 & GUI_NULL) {
      continue;
    }

    temp_s0[sp28].unk0.a = 0xA0;
    temp_s0[sp28].unk0.r = 0xFF;
    temp_s0[sp28].unk0.g = 0xFF;
    temp_s0[sp28].unk0.b = 0xFF;
  }

  *arg2 = arg1;

  sp28 = arg1 + 1;

  temp_s0[arg1].unk0.a = 0xA0;
  temp_s0[arg1].unk0.r = 0xFF;
  temp_s0[arg1].unk0.g = 0xFF;
  temp_s0[arg1].unk0.b = 0xFF;

  while ((temp_s0[sp28].unk24 & GUI_QUIT) != GUI_QUIT) {
    if (temp_s0[sp28 + 1].unk24 & GUI_QUIT) {
      sp28 = 0;
    }
    if (temp_s0[sp28].unk24 & GUI_NULL) {
      if (temp_s0[sp28].unk24 & GUI_TEXTBOX) {
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 1);
        return sp28;
      }
    } else {
      Audio2_Play_SFX(&D_801235B0, &D_800D3988, 1);
      return sp28;
    }
    sp28++;
  }

  return arg1;
}

static void func_80091A8C(UnkStruct_78 *arg0) {
  register UnkStruct_77 *temp_s0 = arg0->unk124;

  if ((temp_s0->unk2C != NULL) && (D_800D3CF8 == NULL)) {
    temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
    temp_s0[D_800D3D00[0]].unk0.r = 0xFF;
    temp_s0[D_800D3D00[0]].unk0.g = 0xFF;
    temp_s0[D_800D3D00[0]].unk0.b = 0xFF;
    temp_s0[D_800D3D10[0]].unk0.a = 0xA0;
    temp_s0[D_800D3D10[0]].unk0.r = 0xFF;
    temp_s0[D_800D3D10[0]].unk0.g = 0xFF;
    temp_s0[D_800D3D10[0]].unk0.b = 0xFF;
    D_800D3CF8 = temp_s0->unk2C;
    D_800D3CFC = temp_s0->unk30;
  }

  if (D_800D5850 == temp_s0) {
    FUN_SRAM_8007868c_tenliner_loop_arg0_t(D_800D57A4.node);
    D_800D57A4.node = &D_800D2D80;
    D_800D57A4.unk5D = 0xFE;
    D_800D57A4.unk60 = 0xFD;
    D_800D57A4.unk62 = 0;
  }

  if (D_800D5D48 == temp_s0) {
    FUN_SRAM_8007868c_tenliner_loop_arg0_t(D_800D5AC4.node);
    D_800D5AC4.node = &D_800D2D80;
    D_800D5AC4.unk5D = 0xFE;
    D_800D5AC4.unk60 = 0xFD;
    D_800D5B28.node = &D_800D2D80;
    D_800D5B8C.node = &D_800D2D80;
    D_800D5BF0.node = &D_800D2D80;
    func_800A2E2C();
  }

  if (D_800D5180 == temp_s0) {
    D_800D5014.node = FUN_SRAM_8007868c_tenliner_loop_arg0_t(D_800D5014.node);
    D_800D5014.node = &D_800D2DB0;
    D_800D5014.unk5D = 0xFE;
    D_800D5014.unk60 = 0xFC;
  }

  if (D_800D4E1C == temp_s0) {
    D_800D4CDC.node = FUN_SRAM_8007868c_tenliner_loop_arg0_t(D_800D4CDC.node);
    D_800D4CDC.node = &D_800D2DC8;
    D_800D4CDC.unk5D = 0xF7;
    D_800D4CDC.unk60 = 0xF9;
  }
}

static void func_80091D60(GUI_Textbox *arg0, UnkStruct_78 *arg1, s32 arg2, f32 arg3) {
  printf("-- func_80091D60\n");
}

static void func_80099674(UnkStruct_78 *arg0) {
  register UnkStruct_77 *temp_s0 = arg0->unk124;
  register s32 var_s1 = 0;
  register s32 var_s2;
  s32 spB8;  // cont_no; 3 to 0
  s32 spB4;  // y
  s32 spB0;  // x
  s32 spAC;  // y
  s32 spA8;  // a
  GUI_Toggle *gui_toggle_1;
  s32 spA0;  // x
  s32 sp9C;  // y
  s32 sp98;  // a
  s32 sp94;  // x
  s32 sp90;  // y
  s32 sp8C;  // r
  s32 sp88;  // g
  s32 sp84;  // b
  s32 sp80;  // a
  s32 i;
  GUI_Slider *gui_slider_1;
  GUI_Textbox *gui_textbox_1;
  GUI_Textbox *gui_textbox_2;
  GUI_Textbox *gui_textbox_3;
  s32 sp68;  // x
  s32 sp64;  // unused
  GUI_Textbox *gui_textbox_4;
  s32 sp5C;  // x
  UnkStruct_1 *sp58;
  GUI_Slider *gui_slider_2;
  GUI_Toggle *gui_toggle_2;

  D_800D3E24 += D_800D3E28;
  if (D_800D3E24 >= 1.0) {
    D_800D3E24 = 1.0;
    D_800D3E28 *= -1;
  }
  if (D_800D3E24 <= 0.6) {
    D_800D3E24 = 0.6;
    D_800D3E28 *= -1;
  }

  if (D_800D3FF8 == temp_s0) {
    D_800D3D30 = TRUE;
    D_800D3D2C++;
    if (D_800D3D2C == 1000) {
      D_800D3CF0 = 3;
      D_800D3D2C = 0;
    }
  } else {
    D_800D3D30 = FALSE;
    D_800D3D2C = 0;
  }

  if (D_800D3E40-- == 0) {

    /*
    FUN_001050_8003b5d0_controller_sendrecvmsg(&superThread);
    */

    D_800D3E40 = 8;

    /*
    if (FUN_001050_getControllerErrNo(&superThread, 0) != 0) {
    */
    if (D_800CFED4 < 1) {

      main_8004A34C_threeliner();
      func_80090A44();
      D_800CFEE8 = 0;  // does this enter haluci (no controller) mode?  yes
      D_800CFD48 = TRUE;
      return;
    }
    if (D_800D3D30) {

      /*
      if (FUN_001050_getControllerErrNo(&superThread, 1) != 0) {
      */
      if (D_800CFED4 < 2) {

        if (D_800D3D00[0] == 4) {
          D_800D3D10[0] = D_800D3D00[0];
          D_800D3D00[0] = 3;
        }
        D_800D3FF8[4].unk24 = GUI_CENTX | GUI_MENU | GUI_NULL | GUI_TITLE;
        D_800D3FF8[4].unk0.a = 0x64;
      } else {
        D_800D3FF8[4].unk24 = GUI_CENTX | GUI_MENU | GUI_TITLE;
        D_800D3FF8[4].unk0.a = 0xA0;
      }
    }
  }

  if (temp_s0 == NULL) {
    return;
  }

  func_8005BBFC(&g_gdl);
  if (arg0->unk114 != 0) {
    if (D_800D3E34 != 0) {
      if (D_800D3E2C > 0.0) {
        D_800D3E2C -= D_800D3E30 * func_800A3AF0();
      }
      if (D_800D3E2C < 0.0) {
        D_800D3E2C = 0;
      }
      func_8007E750();
      if (D_800D3E2C == 0.0) {
        D_800D3D24 = 2;
        if (D_800D3E34 == 1) {
          temp_s0->unk0.a = 0xFF;
          temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
          temp_s0[D_800D3D10[0]].unk0.a = 0xA0;
          func_80091A8C(arg0);
          D_800D3E2C = 0;
          D_800D3E34 = 0;
          func_8005BE40(&g_gdl);
          return;
        }
        if (D_800D3E34 == 2) {
          D_800D3E2C = 0;
          temp_s0->unk0.a = 0xFF;
          temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
          temp_s0[D_800D3D10[0]].unk0.a = 0xA0;
          D_800D3CF8 = temp_s0[D_800D3D00[0]].unk2C;
          D_800D3CFC = temp_s0[D_800D3D00[0]].unk30;
          D_800D3E34 = 0;
          func_8005BE40(&g_gdl);
          return;
        }
      }
    } else {
      if (D_800D3E2C < 1.0) {
        D_800D3E2C += D_800D3E30 * func_800A3AF0();
      }
      if (D_800D3E2C > 1.0) {
        D_800D3E2C = 1;
      }
    }

    for (; (temp_s0[var_s1].unk24 & GUI_QUIT) != GUI_QUIT; var_s1++) {
      if ((temp_s0[var_s1].unk24 & GUI_TOGGLE) && (var_s1 != 0) && !(temp_s0[var_s1].unk24 & GUI_NULL)) {
        gui_toggle_1 = temp_s0[var_s1].unk30;
        spB0 = gui_toggle_1->unk4[gui_toggle_1->cur].x;
        spAC = gui_toggle_1->unk4[gui_toggle_1->cur].y;
        spA8 = temp_s0[var_s1].unk0.a * D_800D3E2C;
        if (gui_toggle_1->ids[gui_toggle_1->cur] != 0) {
          weird_lots_of_magic_number_setting_66xrefs(&g_gdl, gui_toggle_1->unk4[gui_toggle_1->cur].data.img, gui_toggle_1->unk4[gui_toggle_1->cur].pal, spB0, spAC, gui_toggle_1->unk4[gui_toggle_1->cur].r, gui_toggle_1->unk4[gui_toggle_1->cur].g, gui_toggle_1->unk4[gui_toggle_1->cur].b, spA8);
        } else {
          displayText_XY_RGBA_2(&g_gdl, D_800D3D3C[temp_s0[var_s1].unk0.font], spB0, spAC, gui_toggle_1->unk4[gui_toggle_1->cur].data.str, gui_toggle_1->unk4[gui_toggle_1->cur].r, gui_toggle_1->unk4[gui_toggle_1->cur].g, gui_toggle_1->unk4[gui_toggle_1->cur].b, spA8);
        }
      }

      if ((temp_s0[var_s1].unk24 & GUI_PIC) && (var_s1 != 0)) {
        sp98 = temp_s0[var_s1].unk0.a * D_800D3E2C;
        spA0 = temp_s0[var_s1].unk0.x;
        sp9C = temp_s0[var_s1].unk0.y;
        if (temp_s0[var_s1].unk24 & GUI_CENTX) {
          spA0 = (screen_1_width >> 1) - (al_get_bitmap_width(temp_s0[var_s1].unk0.data.img) >> 1);
        }
        weird_lots_of_magic_number_setting_66xrefs(&g_gdl, temp_s0[var_s1].unk0.data.img, temp_s0[var_s1].unk0.pal, spA0, sp9C, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g, temp_s0[var_s1].unk0.b, sp98);
      }

      if ((temp_s0[var_s1].unk24 & GUI_SLIDER) && (var_s1 != 0) && !(temp_s0[var_s1].unk24 & GUI_NULL)) {
        gui_slider_1 = temp_s0[var_s1].unk30;
        if (temp_s0[var_s1].unk24 & GUI_CENTX) {
          sp94 = (screen_1_width >> 1) - (al_get_bitmap_width(gui_slider_1->track.data.img) >> 1);
        } else {
          sp94 = gui_slider_1->track.x;
        }
        sp90 = gui_slider_1->track.y;
        sp8C = gui_slider_1->track.r;
        sp88 = gui_slider_1->track.g;
        sp84 = gui_slider_1->track.b;
        sp80 = gui_slider_1->track.a * D_800D3E2C;
        weird_lots_of_magic_number_setting_66xrefs(&g_gdl, gui_slider_1->track.data.img, gui_slider_1->track.pal, sp94, sp90, sp8C, sp88, sp84, sp80);

        for (i = 0; i < gui_slider_1->num_ticks; i++) {
          sp94 = gui_slider_1->marks[i].x;
          sp90 = gui_slider_1->marks[i].y;
          if (gui_slider_1->cur == i) {
            sp8C = gui_slider_1->marks[i].r * D_800D3E24;
          } else {
            sp8C = gui_slider_1->marks[i].r;
          }
          sp88 = gui_slider_1->marks[i].g;
          sp84 = gui_slider_1->marks[i].b;
          if (i > gui_slider_1->cur) {
            sp80 = 0;
          } else {
            sp80 = 0xFF;
          }
          weird_lots_of_magic_number_setting_66xrefs(&g_gdl, gui_slider_1->marks[i].data.img, gui_slider_1->marks[i].pal, sp94, sp90, sp8C, sp88, sp84, sp80);
        }
      }

      for (spB8 = 3; spB8 >= 0; spB8--) {

        /*
        if ((FUN_001050_getControllerErrNo(&superThread, spB8) == 0) && ((spB8 != 3) || (FUN_001050_getControllerErrNo(&superThread, 2) == 0)) && (D_800D3D00[spB8] == var_s1) && (arg0->unk114 != 0)) {
        */
        if ((D_800CFED4 > spB8) && ((spB8 != 3) || (D_800CFED4 > 2)) && (D_800D3D00[spB8] == var_s1) && (arg0->unk114 != 0)) {

          if (temp_s0[var_s1].unk24 & GUI_TEXTBOX) {
            gui_textbox_1 = temp_s0[var_s1].unk30;
            switch (gui_textbox_1->unk5C) {
            case 0:
              temp_s0[var_s1].unk0.a = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.r = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.g = 0;
              temp_s0[var_s1].unk0.b = 0;
              break;
            case 1:
              temp_s0[var_s1].unk0.a = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.r = 0;
              temp_s0[var_s1].unk0.g = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.b = 0;
              break;
            case 2:
              temp_s0[var_s1].unk0.a = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.r = 0;
              temp_s0[var_s1].unk0.g = 0;
              temp_s0[var_s1].unk0.b = D_800D3E24 * 255;
              break;
            case 3:
              temp_s0[var_s1].unk0.a = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.r = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.g = D_800D3E24 * 255;
              temp_s0[var_s1].unk0.b = 0;
              break;
            default:
              temp_s0[D_800D3D10[spB8]].unk0.a = 0xA0;
              temp_s0[D_800D3D10[spB8]].unk0.g = 0xFF;
              temp_s0[D_800D3D10[spB8]].unk0.b = 0xFF;
              temp_s0[D_800D3D10[spB8]].unk0.r = 0xFF;
              temp_s0[var_s1].unk0.a = 0xFF;
              temp_s0[var_s1].unk0.r = 0xFF;
              temp_s0[var_s1].unk0.g = 0xFF;
              temp_s0[var_s1].unk0.b = 0xFF;
              break;
            }
            if (D_800D5D48 == temp_s0) {
              spB4 = 152;
            } else {
              spB4 = 132;
            }
            if (gui_textbox_1->unk5C != 0xFF) {
              gui_textbox_2 = temp_s0[var_s1].unk30;
              if (D_800D3D94 & (1 << gui_textbox_1->unk5C)) {
                weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_8012901C, NULL, ((gui_textbox_1->unk5 % 15) * 18) + 59, (((gui_textbox_1->unk5 / 15) * 23) + spB4) - 6, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g, temp_s0[var_s1].unk0.b, temp_s0[var_s1].unk0.a * D_800D3E2C);
              }
            }
            if (spB8 == 0) {
              temp_s0[var_s1].unk0.a = D_800D3E24 * 255;
            }
          } else if ((spB8 == 0) && !(temp_s0[var_s1].unk24 & GUI_NULL)) {
            temp_s0[D_800D3D10[spB8]].unk0.a = 0xA0;
            temp_s0[D_800D3D10[spB8]].unk0.r = 0xFF;
            temp_s0[D_800D3D10[spB8]].unk0.g = 0xFF;
            temp_s0[D_800D3D10[spB8]].unk0.b = 0xFF;
            temp_s0[var_s1].unk0.a = D_800D3E24 * 255;
            temp_s0[var_s1].unk0.g = D_800D3E24 * 255;
            temp_s0[var_s1].unk0.b = D_800D3E24 * 255;
          }
        }
      }

      if ((temp_s0[var_s1].unk24 & GUI_TEXTBOX) && (arg0->unk114 != 0)) {
        gui_textbox_3 = temp_s0[var_s1].unk30;
        if (D_800D3D94 != 0) {
          for (sp68 = 63, spB8 = 0; spB8 < 15; spB8++, sp68 += 18) {
            displayText_XY_RGBA_3(&g_gdl, &D_80128F28, (sp68 - (get_char_width(&D_80128F28, D_800D3DA0[spB8]) / 2)) + 9, spB4, D_800D3DA0[spB8], 0xFF, 0xFF, 0xFF, 0xFF);
            displayText_XY_RGBA_3(&g_gdl, &D_80128F28, (sp68 - (get_char_width(&D_80128F28, D_800D3DA0[spB8 + 15]) / 2)) + 9, spB4 + 23, D_800D3DA0[spB8 + 15], 0xFF, 0xFF, 0xFF, 0xFF);
            displayText_XY_RGBA_3(&g_gdl, &D_80128F28, (sp68 - (get_char_width(&D_80128F28, D_800D3DA0[spB8 + 30]) / 2)) + 9, spB4 + 46, D_800D3DA0[spB8 + 30], 0xFF, 0xFF, 0xFF, 0xFF);
          }
        }

        if (D_800D5D48 == temp_s0) {
          for (spB8 = 3; spB8 >= 0; spB8--) {

            /*
            if ((FUN_001050_getControllerErrNo(&superThread, spB8) == 0) && ((spB8 != 3) || (FUN_001050_getControllerErrNo(&superThread, 2) == 0)) && (spB8 + 3 == var_s1)) {
            */
            if ((D_800CFED4 > spB8) && ((spB8 != 3) || (D_800CFED4 > 2)) && (spB8 + 3 == var_s1)) {

              if (gui_textbox_3->unk5C == 0xFF) {
                if (D_800D3D00[0] == var_s1) {
                  displayText_XY_RGBA_2(&g_gdl, &D_80128F28, gui_textbox_3->unkC + 5, gui_textbox_3->unk10 + 8, gui_textbox_3->node->name, 0xFF, 255 * D_800D3E24, 255 * D_800D3E24, temp_s0[var_s1].unk0.a * D_800D3E2C);
                } else {
                  displayText_XY_RGBA_2(&g_gdl, &D_80128F28, gui_textbox_3->unkC + 5, gui_textbox_3->unk10 + 8, gui_textbox_3->node->name, 0xFF, 0xFF, 0xFF, temp_s0[var_s1].unk0.a * D_800D3E2C);
                }
              } else {
                weird_lots_of_magic_number_setting_66xrefs(&g_gdl, gui_textbox_3->unk14.data.img, NULL, gui_textbox_3->unkC, gui_textbox_3->unk10, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g, temp_s0[var_s1].unk0.b, temp_s0[var_s1].unk0.a * D_800D3E2C);
                displayText_XY_RGBA_2(&g_gdl, &D_80128F28, gui_textbox_3->unkC + 5, gui_textbox_3->unk10 + 8, gui_textbox_3->node->name, 0xFF, 255 * D_800D3E24, 255 * D_800D3E24, temp_s0[var_s1].unk0.a * D_800D3E2C * D_800D3E24);
              }
            }
          }
        } else if (gui_textbox_3->unk5C == 0xFF) {
          if (D_800D3D00[0] == var_s1) {
            displayText_XY_RGBA_2(&g_gdl, &D_80128F28, gui_textbox_3->unkC + 5, gui_textbox_3->unk10 + 8, gui_textbox_3->node->name, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g * D_800D3E24, temp_s0[var_s1].unk0.b * D_800D3E24, temp_s0[var_s1].unk0.a * D_800D3E2C);
          } else {
            displayText_XY_RGBA_2(&g_gdl, &D_80128F28, gui_textbox_3->unkC + 5, gui_textbox_3->unk10 + 8, gui_textbox_3->node->name, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g, temp_s0[var_s1].unk0.b, temp_s0[var_s1].unk0.a * D_800D3E2C);
          }
          if ((gui_textbox_3->unk60 == 0xFF) || (gui_textbox_3->unk60 == 0xFE) || (gui_textbox_3->unk60 == 0xFB) || (gui_textbox_3->unk60 == 0xFA) || (gui_textbox_3->unk60 == 0xF9) || (gui_textbox_3->unk60 == 0xF8) || (gui_textbox_3->unk60 == 0xFC)) {
            weird_lots_of_magic_number_setting_66xrefs(&g_gdl, gui_textbox_3->unk14.data.img, NULL, gui_textbox_3->unkC, gui_textbox_3->unk10, 0xFF, 0xFF, 0xFF, temp_s0[var_s1].unk0.a * D_800D3E2C);
          }
        } else {
          weird_lots_of_magic_number_setting_66xrefs(&g_gdl, gui_textbox_3->unk14.data.img, NULL, gui_textbox_3->unkC, gui_textbox_3->unk10, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g, temp_s0[var_s1].unk0.b, temp_s0[var_s1].unk0.a * D_800D3E2C);
          if (gui_textbox_3->unk5D != 1) {
            displayText_XY_RGBA_2(&g_gdl, &D_80128F28, gui_textbox_3->unkC + 5, gui_textbox_3->unk10 + 8, gui_textbox_3->node->name, 0xFF, 255 * D_800D3E24, 255 * D_800D3E24, temp_s0[var_s1].unk0.a * D_800D3E2C * D_800D3E24);
          }
        }
      }

      if (D_800D5D48 == D_801290D0.unk124) {
        if (D_800D3D34 == 1) {
          if (D_800D3D00[0] == 9) {
            temp_s0[9].unk0.r = D_800D3E24 * 150;
            temp_s0[9].unk0.g = (1.0 - D_800D3E24) * 255;
            temp_s0[9].unk0.b = (1.0 - D_800D3E24) * 255;
            temp_s0[9].unk0.a = D_800D3E24 * 255;
          } else {
            temp_s0[9].unk0.r = 0xFF;
            temp_s0[9].unk0.g = 0xFF;
            temp_s0[9].unk0.b = 0xFF;
            temp_s0[9].unk0.a = 0xA0;
          }
          temp_s0[9].unk24 &= ~GUI_NULL;
        } else {
          temp_s0[9].unk0.r = 0;
          temp_s0[9].unk0.g = 0;
          temp_s0[9].unk0.b = 0;
          temp_s0[9].unk0.a = 0;
          temp_s0[9].unk24 |= GUI_NULL;
        }
      }

      if (D_800D5850 == D_801290D0.unk124) {
        if (D_800D3D34 == 1) {
          if (D_800D3D00[0] == 6) {
            temp_s0[6].unk0.r = D_800D3E24 * 150;
            temp_s0[6].unk0.g = (1.0 - D_800D3E24) * 255;
            temp_s0[6].unk0.b = (1.0 - D_800D3E24) * 255;
            temp_s0[6].unk0.a = D_800D3E24 * 255;
          } else {
            temp_s0[6].unk0.r = 0xFF;
            temp_s0[6].unk0.g = 0xFF;
            temp_s0[6].unk0.b = 0xFF;
            temp_s0[6].unk0.a = 0xA0;
          }
          temp_s0[6].unk24 &= ~GUI_NULL;
        } else {
          temp_s0[6].unk0.r = 0;
          temp_s0[6].unk0.g = 0;
          temp_s0[6].unk0.b = 0;
          temp_s0[6].unk0.a = 0;
          temp_s0[6].unk24 |= GUI_NULL;
        }
      }

      if ((temp_s0[var_s1].unk24 & GUI_TEXTBOX) && (arg0->unk114 != 0)) {
        gui_textbox_4 = temp_s0[var_s1].unk30;
        if ((gui_textbox_4->unk5D != 1) && (gui_textbox_4->node->ptr != NULL) && (gui_textbox_4->unk60 != 0xFA)) {
          if (D_800D5D48 == D_801290D0.unk124) {
            if ((gui_textbox_4->node->pack & 0xF) == 0xC) {
              weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_80129020, NULL, gui_textbox_4->unkC + 128, gui_textbox_4->unk10 + 3, 0xFF, 0xFF, 0xFF, 255 * D_800D3E2C);
            } else {
              weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_80129024, NULL, gui_textbox_4->unkC + 128, gui_textbox_4->unk10 + 3, 0xFF, 0xFF, 0xFF, 255 * D_800D3E2C);
            }
            if ((FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) >= 10) {
              sp5C = displayText_XY_RGBA_3(&g_gdl, &D_80128F28, gui_textbox_4->unkC + 133, gui_textbox_4->unk10 + 8, ((FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) / 10) + 0x30, 0xFF, 0xFF, 0, 255 * D_800D3E2C);
              displayText_XY_RGBA_3(&g_gdl, &D_80128F28, sp5C, gui_textbox_4->unk10 + 8, ((FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) % 10) + 0x30, 0xFF, 0xFF, 0, 255 * D_800D3E2C);
            } else {
              displayText_XY_RGBA_3(&g_gdl, &D_80128F28, gui_textbox_4->unkC + 137, gui_textbox_4->unk10 + 8, (FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) + 0x30, 0xFF, 0xFF, 0, 255 * D_800D3E2C);
            }
          } else {
            if ((gui_textbox_4->node->pack & 0xF) == 0xC) {
              weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_80129020, NULL, gui_textbox_4->unkC + 128, gui_textbox_4->unk10 + 3, 0xFF, 0xFF, 0xFF, 255 * D_800D3E2C);
            } else {
              weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_80129024, NULL, gui_textbox_4->unkC + 128, gui_textbox_4->unk10 + 3, 0xFF, 0xFF, 0xFF, 255 * D_800D3E2C);
            }
            func_8005BBFC(&g_gdl);
            if ((FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) >= 10) {
              sp5C = displayText_XY_RGBA_3(&g_gdl, &D_80128F28, gui_textbox_4->unkC + 133, gui_textbox_4->unk10 + 8, ((FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) / 10) + 0x30, 0xFF, 0xFF, 0, 255 * D_800D3E2C);
              displayText_XY_RGBA_3(&g_gdl, &D_80128F28, sp5C, gui_textbox_4->unk10 + 8, ((FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) % 10) + 0x30, 0xFF, 0xFF, 0, 255 * D_800D3E2C);
            } else {
              displayText_XY_RGBA_3(&g_gdl, &D_80128F28, gui_textbox_4->unkC + 137, gui_textbox_4->unk10 + 8, (FUN_SRAM_80078300_twelveliner_div60_loop_30t_a(gui_textbox_4->node->ptr) + 1) +  0x30, 0xFF, 0xFF, 0, 255 * D_800D3E2C);
            }
          }
        }
      }

      if (temp_s0[var_s1].unk24 & GUI_TITLE) {
        if (temp_s0[var_s1].unk24 & GUI_CENTX) {
          displayText_XY_RGBA_2(&g_gdl, D_800D3D3C[temp_s0[var_s1].unk0.font], (screen_1_width >> 1) - (get_text_width(&D_80128EB0, temp_s0[var_s1].unk0.data.str) >> 1), temp_s0[var_s1].unk0.y, temp_s0[var_s1].unk0.data.str, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g, temp_s0[var_s1].unk0.b, temp_s0[var_s1].unk0.a * D_800D3E2C);
        } else {
          displayText_XY_RGBA_2(&g_gdl, D_800D3D3C[temp_s0[var_s1].unk0.font], temp_s0[var_s1].unk0.x, temp_s0[var_s1].unk0.y, temp_s0[var_s1].unk0.data.str, temp_s0[var_s1].unk0.r, temp_s0[var_s1].unk0.g, temp_s0[var_s1].unk0.b, temp_s0[var_s1].unk0.a * D_800D3E2C);
        }
      }
    }
  }

  if ((D_800CFEE4 == 0) && (D_800CFEE8 != 10) && (D_800CFEE8 != 16)) {
    sp58 = &g_PV_arr[0].unk28;

    if (temp_s0[D_800D3D00[0]].unk24 & GUI_WINDOW) {
      ((void (*)(void *, f32)) temp_s0[D_800D3D00[0]].unk28)(temp_s0[D_800D3D00[0]].unk30, D_800D3E2C);
    }

    if (g_PV_arr[0].unk24 & 0x1000) {  // START_BUTTON / CONT_START
      if ((D_800D5850 == D_801290D0.unk124) && (D_800D3D34 == 1)) {
        temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
        temp_s0[D_800D3D00[0]].unk0.r = 0xFF;
        temp_s0[D_800D3D00[0]].unk0.g = 0xFF;
        temp_s0[D_800D3D00[0]].unk0.b = 0xFF;
        ((void (*)(void *, f32)) temp_s0[6].unk28)(temp_s0[6].unk30, 0);
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 4);
        func_8005BE40(&g_gdl);
        D_800D57A4.unk61 = FALSE;
        return;
      }

      if ((D_800D5D48 == D_801290D0.unk124) && (D_800D3D34 == 1)) {
        temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
        temp_s0[D_800D3D00[0]].unk0.r = 0xFF;
        temp_s0[D_800D3D00[0]].unk0.g = 0xFF;
        temp_s0[D_800D3D00[0]].unk0.b = 0xFF;
        ((void (*)(void *, f32)) temp_s0[9].unk28)(temp_s0[9].unk30, 0);
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 4);
        func_8005BE40(&g_gdl);
        D_800D5AC4.unk61 = FALSE;
        D_800D5B28.unk61 = FALSE;
        D_800D5B8C.unk61 = FALSE;
        D_800D5BF0.unk61 = FALSE;
        return;
      }
    }

    if ((D_800D3E34 == 0) && !((temp_s0[D_800D3D00[0]].unk24 & GUI_TEXTBOX) || (arg0->unk114 == 0))) {
      if ((temp_s0[D_800D3D00[0]].unk24 & GUI_SLIDER) && (arg0->unk114 != 0)) {
        gui_slider_2 = temp_s0[D_800D3D00[0]].unk30;
        if (sp58->unk84 & 0x200) {  // L_JPAD / CONT_LEFT
          if (gui_slider_2->cur != 0) {
            gui_slider_2->cur--;
            if (temp_s0[D_800D3D00[0]].unk28 == NULL) {
              debug_print_reason_routine("gui func call in menu", "bad mojo");
            }
            ((void (*)(void *, f32)) temp_s0[D_800D3D00[0]].unk28)(temp_s0[D_800D3D00[0]].unk30, 0);
            Audio2_Play_SFX(&D_801235B0, &D_800D3988, 1);
          } else {
            return;
          }
        }
        if (sp58->unk84 & 0x100) {  // R_JPAD / CONT_RIGHT
          if (gui_slider_2->cur < gui_slider_2->num_ticks - 1) {
            gui_slider_2->cur++;
            if (temp_s0[D_800D3D00[0]].unk28 == NULL) {
              debug_print_reason_routine("gui func call in menu", "bad mojo");
            }
            ((void (*)(void *, f32)) temp_s0[D_800D3D00[0]].unk28)(temp_s0[D_800D3D00[0]].unk30, 0);
            Audio2_Play_SFX(&D_801235B0, &D_800D3988, 1);
          } else {
            return;
          }
        }
      }

      if ((temp_s0[D_800D3D00[0]].unk24 & GUI_TOGGLE) && (arg0->unk114 != 0) && ((g_PV_arr[0].unk24 & 0x200) || (g_PV_arr[0].unk24 & 0x100))) {
        gui_toggle_2 = temp_s0[D_800D3D00[0]].unk30;
        if (g_PV_arr[0].unk24 & 0x200) {  // L_JPAD / CONT_LEFT
          if (gui_toggle_2->cur == 0) {
            gui_toggle_2->cur = gui_toggle_2->num;
          }
          gui_toggle_2->cur--;
        }
        if (g_PV_arr[0].unk24 & 0x100) {  // R_JPAD / CONT_RIGHT
          gui_toggle_2->cur++;
          if (gui_toggle_2->cur >= gui_toggle_2->num) {
            gui_toggle_2->cur = 0;
          }
        }
        if (temp_s0[D_800D3D00[0]].unk28 != NULL) {
          ((void (*)(void *, f32)) temp_s0[D_800D3D00[0]].unk28)(temp_s0[D_800D3D00[0]].unk30, D_800D3E2C);
        }
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 1);
      }

      if ((temp_s0[D_800D3D00[0]].unk24 & GUI_FUNC) && (arg0->unk114 != 0) && ((g_PV_arr[0].unk24 & 0x8000) || (g_PV_arr[0].unk24 & 0x1000))) {
        if (D_800D3FF8 == D_801290D0.unk124) {
          if (g_PV_arr[0].unk24 & 0x1000) {  // START_BUTTON / CONT_START
            func_8005BE40(&g_gdl);
            return;
          }

          if (temp_s0[D_800D3D00[0]].unk28 == NULL) {
            debug_print_reason_routine("gui func call in menu", "bad mojo");
          }
          ((void (*)(void *, f32)) temp_s0[D_800D3D00[0]].unk28)(temp_s0[D_800D3D00[0]].unk30, 0);
          Audio2_Play_SFX(&D_801235B0, &D_800D3988, 2);
          func_8005BE40(&g_gdl);
          return;
        }

        if (temp_s0[D_800D3D00[0]].unk28 == NULL) {
          debug_print_reason_routine("gui func call in menu", "bad mojo");
        }
        ((void (*)(void *, f32)) temp_s0[D_800D3D00[0]].unk28)(temp_s0[D_800D3D00[0]].unk30, 0);
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 2);
        func_8005BE40(&g_gdl);
        return;
      }

      if ((temp_s0[D_800D3D00[0]].unk24 & GUI_MENU) && (arg0->unk114 != 0) && (g_PV_arr[0].unk24 & 0x8000) && (D_800D3CF8 == NULL)) {
        D_800D3E34 = 2;
        func_8007E9F8(9);
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 4);
      }

      if ((D_800D3E34 == 0) && (g_PV_arr[0].unk24 & 0x8000)) {
        D_800D3E2C = 0;
        func_8009DDF4(arg0);
        if (D_800D3D20 != 0) {
          D_800D3D20 = 0;
        }
        D_800D3D90 = 1;
      }

      if ((g_PV_arr[0].unk24 & 0x4000) && (D_800D3CF8 == NULL) && (temp_s0->unk2C != NULL)) {
        if ((D_800D5D48 == temp_s0) && D_800D5AC4.unk61) {
          D_800D5AC4.unk61 = FALSE;
          D_800D5AC4.unk5C = 0;
          D_800D5AC4.unk5D = 0;
          temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
          temp_s0[D_800D3D00[0]].unk0.r = 0xFF;
          temp_s0[D_800D3D00[0]].unk0.g = 0xFF;
          temp_s0[D_800D3D00[0]].unk0.b = 0xFF;
          D_800D3D10[0] = D_800D3D00[0];
          D_800D3D00[0] = 3;
          return;
        }

        if ((D_800D5850 == temp_s0) && D_800D57A4.unk61) {
          D_800D57A4.unk61 = FALSE;
          D_800D57A4.unk5C = 0;
          D_800D57A4.unk5D = 0;
          temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
          temp_s0[D_800D3D00[0]].unk0.r = 0xFF;
          temp_s0[D_800D3D00[0]].unk0.g = 0xFF;
          temp_s0[D_800D3D00[0]].unk0.b = 0xFF;
          D_800D3D10[0] = D_800D3D00[0];
          D_800D3D00[0] = 3;
          return;
        }

        func_8007E9F8(9);
        D_800D3E34 = 1;
        Audio2_Play_SFX(&D_801235B0, &D_800D3988, 5);
        return;
      }

      if (sp58->unk84 & 0x800) {  // U_JPAD / CONT_UP
        if (D_800D5D48 == temp_s0) {
          if (D_800D3D94 != 0) {
            Audio2_Play_SFX(&D_801235B0, &D_800D3988, 3);
            return;
          }

          if (D_800D3D00[0] == 7) {
            temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
            temp_s0[D_800D3D00[0]].unk0.r = 0xFF;
            temp_s0[D_800D3D00[0]].unk0.g = 0xFF;
            temp_s0[D_800D3D00[0]].unk0.b = 0xFF;
            D_800D3D00[0] = 3;
            return;
          }

          D_800D3D00[0] = func_80091440(arg0, D_800D3D00[0], &D_800D3D10[0]);
          D_800D3D2C = 0;
          return;
        }

        D_800D3D00[0] = func_80091440(arg0, D_800D3D00[0], &D_800D3D10[0]);
        D_800D3D2C = 0;
        return;
      }

      if (sp58->unk84 & 0x400) {  // D_JPAD / CONT_DOWN
        if (D_800D3D94 != 0) {
          Audio2_Play_SFX(&D_801235B0, &D_800D3988, 3);
          return;
        }

        if (D_800D5D48 == temp_s0) {
          if (D_800D3D00[0] == 3) {
            temp_s0[D_800D3D00[0]].unk0.a = 0xA0;
            temp_s0[D_800D3D00[0]].unk0.r = 0xFF;
            temp_s0[D_800D3D00[0]].unk0.g = 0xFF;
            temp_s0[D_800D3D00[0]].unk0.b = 0xFF;
            D_800D3D00[0] = 7;
            return;
          }

          D_800D3D00[0] = func_80091744(arg0, D_800D3D00[0], D_800D3D10);
          D_800D3D2C = 0;
          return;
        }

        D_800D3D00[0] = func_80091744(arg0, D_800D3D00[0], D_800D3D10);
        D_800D3D2C = 0;
        return;
      }
    }

    for (var_s2 = 0; var_s2 < 4; var_s2++) {

      /*
      if (((var_s2 != 3) || (FUN_001050_getControllerErrNo(&superThread, 2) == 0)) && (temp_s0[D_800D3D00[var_s2]].unk24 & GUI_TEXTBOX) && (arg0->unk114 != 0)) {
      */
      if (((var_s2 != 3) || (D_800CFED4 > 2)) && (temp_s0[D_800D3D00[var_s2]].unk24 & GUI_TEXTBOX) && (arg0->unk114 != 0)) {

        if (((GUI_Textbox *) temp_s0[D_800D3D00[var_s2]].unk30)->unk60 != 0xFD) {
          if (var_s2 == 0) {
            func_80091D60(temp_s0[D_800D3D00[var_s2]].unk30, arg0, var_s2, D_800D3E24);
          }
        } else {
          func_80091D60(temp_s0[D_800D3D00[var_s2]].unk30, arg0, var_s2, D_800D3E24);
        }
      }
    }
  }

  func_8005BE40(&g_gdl);
}

void func_8009D400(u16 arg0) {
  if (arg0 & GUI_TITLE) {
    rmonPrintf("GUI_TITLE ");
  }
  if (arg0 & GUI_PIC) {
    rmonPrintf("GUI_PIC ");
  }
  if (arg0 & GUI_FUNC) {
    rmonPrintf("GUI_FUNC ");
  }
  if (arg0 & GUI_NULL) {
    rmonPrintf("GUI_NULL ");
  }
  if (arg0 & GUI_MENU) {
    rmonPrintf("GUI_MENU ");
  }
  if (arg0 & GUI_DIS) {
    rmonPrintf("GUI_DIS ");
  }
  if (arg0 & GUI_CENTX) {
    rmonPrintf("GUI_CENTX ");
  }
  if (arg0 & GUI_CENTY) {
    rmonPrintf("GUI_CENTY ");
  }
  if (arg0 & GUI_NUM) {
    rmonPrintf("GUI_NUM ");
  }
  if (arg0 & GUI_TEXTBOX) {
    rmonPrintf("GUI_TEXTBOX ");
  }
  if (arg0 & GUI_TOGGLE) {
    rmonPrintf("GUI_TOGGLE ");
  }
  if (arg0 & GUI_WINDOW) {
    rmonPrintf("GUI_WINDOW ");
  }
  if (arg0 & GUI_SLIDER) {
    rmonPrintf("GUI_SLIDER ");
  }
  if (arg0 & GUI_QUIT) {
    rmonPrintf("GUI_QUIT ");
  }
  rmonPrintf("\n");
}

void func_8009D5E4(void) {
  UnkStruct_77 *sp3C;

  sp3C = D_801290D0.unk124;
  if (D_800D3D88) {
    main_8004A34C_threeliner();
    func_8008FF78(&D_801290D0);
    func_8009098C(&D_801290D0);
    rmonPrintf("Loading: %d\n", g_sram_ptr->song);
    Audio_80084e20_twentyliner(g_sram_ptr->song, &D_80120A70, 1);
    main_8004A34C_threeliner();
    func_8008F360(&D_801290D0, D_800D4E1C, D_800D4DD4);
    Font_Init46Char(&D_80128EB0, IMG_FONT_A);
    Font_Init46Char(&D_80128F28, IMG_FONT_B);
    Font_Init46Char(&D_80128FA0, IMG_FONT_C);
    main_8004A34C_threeliner();
    Audio2_GFXDone_SendPlayMessage(&D_80120A70);
    D_800D3D88 = FALSE;
  }

  if (D_801290D0.unk114 == 0) {
    func_800A0228(&D_801290D0);
  }

  if (D_801290D0.unk114 == 1) {
    al_destroy_bitmap(D_801290D0.img);
    D_801290D0.img = NULL;
    func_8009F338(&D_801290D0);
    D_801290D0.unk114 = 2;
  }

  func_80090AC0(D_8012902C[D_800D3CF4]);

  func_8005BBFC(&g_gdl);

  if (D_801290D0.unk114 == 0) {
    //gDPSetColorImage(g_gdl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, screen_1_width, OS_PHYSICAL_TO_K0(D_8012902C[D_800D3CF4]->img));
    ALLEGRO_BITMAP* cfbuffer = al_get_target_bitmap();
    al_set_target_bitmap(D_8012902C[D_800D3CF4]->img);

    weird_lots_of_magic_number_setting_66xrefs(&g_gdl, sp3C->unk0.data.img, sp3C->unk0.pal, sp3C->unk0.x, sp3C->unk0.y, sp3C->unk0.r, sp3C->unk0.g, sp3C->unk0.b, sp3C->unk0.a);

    //gDPSetColorImage(g_gdl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, screen_1_width, OS_PHYSICAL_TO_K0(cfb[draw_buffer]));
    al_set_target_bitmap(cfbuffer);
  } else {
    weird_lots_of_magic_number_setting_66xrefs(&g_gdl, sp3C->unk0.data.img, sp3C->unk0.pal, sp3C->unk0.x, sp3C->unk0.y, sp3C->unk0.r, sp3C->unk0.g, sp3C->unk0.b, sp3C->unk0.a);
  }
  func_8005BE40(&g_gdl);
  func_80099674(&D_801290D0);
}

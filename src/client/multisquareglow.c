#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_images_cfg;

static void *D_8011FBB0;

void MultisquareGlow_8006af00_eightliner(SquareGlow *squareGlow_ptr, s32 arg1) {
  if (!squareGlow_ptr->is_active) {
    return;
  }

  if (squareGlow_ptr->num_steps < arg1) {
    arg1 = squareGlow_ptr->num_steps;
  }
  squareGlow_ptr->num_steps -= arg1;
  if (squareGlow_ptr->num_steps == 0) {
    squareGlow_ptr->is_active = FALSE;
  }
  squareGlow_ptr->val += squareGlow_ptr->rate * arg1;
}

void MultisquareGlow_8006af70_nineliner(SquareGlow *squareGlow_ptr) {
  register s32 var_s0;

  if (!squareGlow_ptr->is_active) {
    return;
  }

  var_s0 = (sins(squareGlow_ptr->val) * 0xC4) >> 15;
  if (squareGlow_ptr->alpha != 0xFF) {
    var_s0 = (squareGlow_ptr->alpha * var_s0) >> 8;
  }
  func_8005BBFC(&g_gdl);
  weird_lots_of_magic_number_setting_66xrefs(&g_gdl, D_8011FBB0, NULL, squareGlow_ptr->location.x, squareGlow_ptr->location.y, 0xFF, 0xFF, 0xFF, var_s0);
  func_8005BE40(&g_gdl);
}

void MultisquareGlow_Init(SquareGlow *squareGlow_ptr, Point arg1, u8 unitSize) {
  u16 width;
  u16 height;

  squareGlow_ptr->is_active = TRUE;
  squareGlow_ptr->num_steps = 0x40;
  squareGlow_ptr->val = 0;
  squareGlow_ptr->rate = 0x8000 / squareGlow_ptr->num_steps;
  squareGlow_ptr->alpha = 0xFF;

  switch (unitSize) {
  case 11:
    squareGlow_ptr->size = 0;  // large
    if (D_8011FBB0 != NULL) {
      width = al_get_bitmap_width(D_8011FBB0);
      height = al_get_bitmap_height(D_8011FBB0);
    } else {
      width = 66;
      height = 66;
    }
    squareGlow_ptr->location.x = (arg1.x >> 2) - ((width - 44) >> 1);
    squareGlow_ptr->location.y = (arg1.y >> 2) - ((width - 44) >> 1);
    break;
  case 10:
    squareGlow_ptr->size = 1;  // medium
    if (D_8011FBB0 != NULL) {
      width = al_get_bitmap_width(D_8011FBB0);
      height = al_get_bitmap_height(D_8011FBB0);
    } else {
      width = 60;
      height = 60;
    }
    squareGlow_ptr->location.x = (arg1.x >> 2) - ((width - 40) >> 1);
    squareGlow_ptr->location.y = (arg1.y >> 2) - ((width - 40) >> 1);
    break;
  case 8:
    squareGlow_ptr->size = 2;  // small
    if (D_8011FBB0 != NULL) {
      width = al_get_bitmap_width(D_8011FBB0);
      height = al_get_bitmap_height(D_8011FBB0);
    } else {
      width = 50;
      height = 50;
    }
    squareGlow_ptr->location.x = (arg1.x >> 2) - ((width - 32) >> 1);
    squareGlow_ptr->location.y = (arg1.y >> 2) - ((width - 32) >> 1);
    break;
  default:
    debug_print_reason_routine("Invalid unitSize, multsiquareglow.c", "MultisquareGlow:Init");
    break;
  }
}

void MultisquareGlow_InitStaticMembers(u8 numPlayers) {
  config_setting_t *root, *images;
  root = config_root_setting(&g_images_cfg);
  images = config_setting_get_member(root, "images");

  main_8004A34C_threeliner();

  switch (numPlayers) {
  case 1:
    D_8011FBB0 = al_load_bitmap(config_setting_get_string_elem(images, IMG_SQUARE_GLOW));
    break;
  case 2:
    D_8011FBB0 = al_load_bitmap(config_setting_get_string_elem(images, IMG_SQUARE_2P_GLOW));
    break;
  case 3:
  case 4:
    D_8011FBB0 = al_load_bitmap(config_setting_get_string_elem(images, IMG_SQUARE_4P_GLOW));
    break;
  default:
    debug_print_reason_routine("Invalid numPlayers, multisquareglow.c", "MultisquareGlow_InitStaticMembers");
    break;
  }
}

void MultisquareGlow_8006b384_oneliner_calls_fun(void) {
  if (D_8011FBB0 != NULL) {
    al_destroy_bitmap(D_8011FBB0);
    D_8011FBB0 = NULL;
  }
}

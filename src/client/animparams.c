#include "common.h"
#include <libconfig.h>
#include <allegro5/allegro5.h>

extern config_t g_anims_cfg;

AnimParams D_800D1030 = {
  { // img_ids[30]
    ANIM_MAYAN_TEMPLE_FIRE_01,
    ANIM_MAYAN_TEMPLE_FIRE_02,
    ANIM_MAYAN_TEMPLE_FIRE_03,
    ANIM_MAYAN_TEMPLE_FIRE_04,
    ANIM_MAYAN_TEMPLE_FIRE_05,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_MAYAN_TEMPLE_FIRE_01_PAL,
    ANIM_MAYAN_TEMPLE_FIRE_02_PAL,
    ANIM_MAYAN_TEMPLE_FIRE_03_PAL,
    ANIM_MAYAN_TEMPLE_FIRE_04_PAL,
    ANIM_MAYAN_TEMPLE_FIRE_05_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  0,                      // image_cnt
  297, 89,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D10CC = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  2,                      // image_cnt
  301, 115,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1168 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  1,                      // image_cnt
  306, 141,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1204 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  4,                      // image_cnt
  328, 89,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D12A0 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  3,                      // image_cnt
  333, 115,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D133C = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  0,                      // image_cnt
  338, 141,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D13D8 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  0,                      // image_cnt
  278, 74,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1474 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  5,                      // num_images
  2,                      // image_cnt
  331, 74,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1510 = {
  { // img_ids[30]
    ANIM_JAPANESE_SPARKLE_01,
    ANIM_JAPANESE_SPARKLE_02,
    ANIM_JAPANESE_SPARKLE_03,
    ANIM_JAPANESE_SPARKLE_04,
    ANIM_JAPANESE_SPARKLE_05,
    ANIM_JAPANESE_SPARKLE_06,
    ANIM_JAPANESE_SPARKLE_07,
    ANIM_JAPANESE_SPARKLE_08,
    ANIM_JAPANESE_SPARKLE_09,
    ANIM_JAPANESE_SPARKLE_10,
    ANIM_JAPANESE_SPARKLE_11,
    ANIM_JAPANESE_SPARKLE_12,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_JAPANESE_SPARKLE_01_PAL,
    ANIM_JAPANESE_SPARKLE_02_PAL,
    ANIM_JAPANESE_SPARKLE_03_PAL,
    ANIM_JAPANESE_SPARKLE_04_PAL,
    ANIM_JAPANESE_SPARKLE_05_PAL,
    ANIM_JAPANESE_SPARKLE_06_PAL,
    ANIM_JAPANESE_SPARKLE_07_PAL,
    ANIM_JAPANESE_SPARKLE_08_PAL,
    ANIM_JAPANESE_SPARKLE_09_PAL,
    ANIM_JAPANESE_SPARKLE_10_PAL,
    ANIM_JAPANESE_SPARKLE_11_PAL,
    ANIM_JAPANESE_SPARKLE_12_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  12,                     // num_images
  0,                      // image_cnt
  17, 252,                // x, y
  NULL, NULL,             // **images, **palettes
  0, 0, 60, 0, 1,         // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D15AC = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  12,                     // num_images
  0,                      // image_cnt
  105, 258,               // x, y
  NULL, NULL,             // **images, **palettes
  0, 0, 80, 0, 1,         // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1648 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  12,                     // num_images
  0,                      // image_cnt
  220, 210,               // x, y
  NULL, NULL,             // **images, **palettes
  0, 0, 100, 0, 1,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D16E4 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  12,                     // num_images
  0,                      // image_cnt
  237, 246,               // x, y
  NULL, NULL,             // **images, **palettes
  0, 0, 115, 0, 1,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1780 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  12,                     // num_images
  0,                      // image_cnt
  301, 257,               // x, y
  NULL, NULL,             // **images, **palettes
  0, 0, 70, 0, 1,         // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D181C = {
  { // img_ids[30]
    ANIM_JAPANESE_WATER_01,
    ANIM_JAPANESE_WATER_02,
    ANIM_JAPANESE_WATER_03,
    ANIM_JAPANESE_WATER_04,
    ANIM_JAPANESE_WATER_05,
    ANIM_JAPANESE_WATER_06,
    ANIM_JAPANESE_WATER_07,
    ANIM_JAPANESE_WATER_08,
    ANIM_JAPANESE_WATER_09,
    ANIM_JAPANESE_WATER_10,
    ANIM_JAPANESE_WATER_11,
    ANIM_JAPANESE_WATER_12,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_JAPANESE_WATER_01_PAL,
    ANIM_JAPANESE_WATER_02_PAL,
    ANIM_JAPANESE_WATER_03_PAL,
    ANIM_JAPANESE_WATER_04_PAL,
    ANIM_JAPANESE_WATER_05_PAL,
    ANIM_JAPANESE_WATER_06_PAL,
    ANIM_JAPANESE_WATER_07_PAL,
    ANIM_JAPANESE_WATER_08_PAL,
    ANIM_JAPANESE_WATER_09_PAL,
    ANIM_JAPANESE_WATER_10_PAL,
    ANIM_JAPANESE_WATER_11_PAL,
    ANIM_JAPANESE_WATER_12_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  12,                     // num_images
  0,                      // image_cnt
  4, 256,                 // x, y
  NULL, NULL,             // **images, **palettes
  5, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D18B8 = {
  { // img_ids[30]
    ANIM_FINALE_BOILER,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_FINALE_BOILER_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  262, 67,                // x, y
  NULL, NULL,             // **images, **palettes
  11, 0, 30, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1954 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  262, 67,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 53, 0, 0,         // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D19F0 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  262, 67,                // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 42, 0, 0,         // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1A8C = {
  { // img_ids[30]
    ANIM_FINALE_LIGHT_BULB,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_FINALE_LIGHT_BULB_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 31,                 // x, y
  NULL, NULL,             // **images, **palettes
  20, 0, 20, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1B28 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 51,                 // x, y
  NULL, NULL,             // **images, **palettes
  15, 0, 12, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1BC4 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 91,                 // x, y
  NULL, NULL,             // **images, **palettes
  15, 0, 15, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1C60 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 111,                // x, y
  NULL, NULL,             // **images, **palettes
  10, 0, 23, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1CFC = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 150,                // x, y
  NULL, NULL,             // **images, **palettes
  10, 0, 17, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1D98 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 170,                // x, y
  NULL, NULL,             // **images, **palettes
  15, 0, 13, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1E34 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 210,                // x, y
  NULL, NULL,             // **images, **palettes
  15, 0, 27, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1ED0 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  1,                      // num_images
  0,                      // image_cnt
  12, 230,                // x, y
  NULL, NULL,             // **images, **palettes
  10, 0, 16, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D1F6C = {
  { // img_ids[30]
    ANIM_FINALE_GAUGE_NEEDLE_01,
    ANIM_FINALE_GAUGE_NEEDLE_02,
    ANIM_FINALE_GAUGE_NEEDLE_03,
    ANIM_FINALE_GAUGE_NEEDLE_04,
    ANIM_FINALE_GAUGE_NEEDLE_05,
    ANIM_FINALE_GAUGE_NEEDLE_06,
    ANIM_FINALE_GAUGE_NEEDLE_07,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_FINALE_GAUGE_NEEDLE_01_PAL,
    ANIM_FINALE_GAUGE_NEEDLE_02_PAL,
    ANIM_FINALE_GAUGE_NEEDLE_03_PAL,
    ANIM_FINALE_GAUGE_NEEDLE_04_PAL,
    ANIM_FINALE_GAUGE_NEEDLE_05_PAL,
    ANIM_FINALE_GAUGE_NEEDLE_06_PAL,
    ANIM_FINALE_GAUGE_NEEDLE_07_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  7,                      // num_images
  0,                      // image_cnt
  38, 101,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2008 = {
  { // img_ids[30]
    ANIM_CELTIC_LAMP_01,
    ANIM_CELTIC_LAMP_02,
    ANIM_CELTIC_LAMP_03,
    ANIM_CELTIC_LAMP_04,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_CELTIC_LAMP_01_PAL,
    ANIM_CELTIC_LAMP_02_PAL,
    ANIM_CELTIC_LAMP_03_PAL,
    ANIM_CELTIC_LAMP_04_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  4,                      // num_images
  0,                      // image_cnt
  212, 176,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 1,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D20A4 = {
  { // img_ids[30]
    ANIM_RUSSIAN_CANDLE_01,
    ANIM_RUSSIAN_CANDLE_02,
    ANIM_RUSSIAN_CANDLE_03,
    ANIM_RUSSIAN_CANDLE_04,
    ANIM_RUSSIAN_CANDLE_05,
    ANIM_RUSSIAN_CANDLE_06,
    ANIM_RUSSIAN_CANDLE_07,
    ANIM_RUSSIAN_CANDLE_08,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_RUSSIAN_CANDLE_01_PAL,
    ANIM_RUSSIAN_CANDLE_02_PAL,
    ANIM_RUSSIAN_CANDLE_03_PAL,
    ANIM_RUSSIAN_CANDLE_04_PAL,
    ANIM_RUSSIAN_CANDLE_05_PAL,
    ANIM_RUSSIAN_CANDLE_06_PAL,
    ANIM_RUSSIAN_CANDLE_07_PAL,
    ANIM_RUSSIAN_CANDLE_08_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  0,                      // image_cnt
  23, 259,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2140 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  2,                      // image_cnt
  53, 258,                // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D21DC = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  6,                      // image_cnt
  40, 266,                // x, y
  NULL, NULL,             // **images, **palettes
  3, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2278 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  1,                      // image_cnt
  75, 257,                // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2314 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  3,                      // image_cnt
  196, 266,               // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D23B0 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  5,                      // image_cnt
  203, 258,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D244C = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  2,                      // image_cnt
  231, 267,               // x, y
  NULL, NULL,             // **images, **palettes
  3, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D24E8 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  0,                      // image_cnt
  250, 259,               // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2584 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  7,                      // image_cnt
  271, 265,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2620 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  3,                      // image_cnt
  332, 259,               // x, y
  NULL, NULL,             // **images, **palettes
  3, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D26BC = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  4,                      // image_cnt
  337, 264,               // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2758 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  3,                      // image_cnt
  65, 228,                // x, y
  NULL, NULL,             // **images, **palettes
  3, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D27F4 = {
  { // img_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  8,                      // num_images
  4,                      // image_cnt
  211, 229,               // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2890 = {
  { // img_ids[30]
    ANIM_GREEK_FIRE_POT_01,
    ANIM_GREEK_FIRE_POT_02,
    ANIM_GREEK_FIRE_POT_03,
    ANIM_GREEK_FIRE_POT_04,
    ANIM_GREEK_FIRE_POT_05,
    ANIM_GREEK_FIRE_POT_06,
    ANIM_GREEK_FIRE_POT_07,
    ANIM_GREEK_FIRE_POT_08,
    ANIM_GREEK_FIRE_POT_09,
    ANIM_GREEK_FIRE_POT_10,
    ANIM_GREEK_FIRE_POT_11,
    ANIM_GREEK_FIRE_POT_12,
    ANIM_GREEK_FIRE_POT_25,
    ANIM_GREEK_FIRE_POT_13,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_GREEK_FIRE_POT_01_PAL,
    ANIM_GREEK_FIRE_POT_02_PAL,
    ANIM_GREEK_FIRE_POT_03_PAL,
    ANIM_GREEK_FIRE_POT_04_PAL,
    ANIM_GREEK_FIRE_POT_05_PAL,
    ANIM_GREEK_FIRE_POT_06_PAL,
    ANIM_GREEK_FIRE_POT_07_PAL,
    ANIM_GREEK_FIRE_POT_08_PAL,
    ANIM_GREEK_FIRE_POT_09_PAL,
    ANIM_GREEK_FIRE_POT_10_PAL,
    ANIM_GREEK_FIRE_POT_11_PAL,
    ANIM_GREEK_FIRE_POT_12_PAL,
    ANIM_GREEK_FIRE_POT_25_PAL,
    ANIM_GREEK_FIRE_POT_13_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  14,                     // num_images
  0,                      // image_cnt
  271, 15,                // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0x7F  // red, green, blue, alpha
};

AnimParams D_800D292C = {
  { // img_ids[30]
    ANIM_EGYPTIAN_COAL_POT_01,
    ANIM_EGYPTIAN_COAL_POT_02,
    ANIM_EGYPTIAN_COAL_POT_03,
    ANIM_EGYPTIAN_COAL_POT_04,
    ANIM_EGYPTIAN_COAL_POT_05,
    ANIM_EGYPTIAN_COAL_POT_06,
    ANIM_EGYPTIAN_COAL_POT_07,
    ANIM_EGYPTIAN_COAL_POT_08,
    ANIM_EGYPTIAN_COAL_POT_09,
    ANIM_EGYPTIAN_COAL_POT_10,
    ANIM_EGYPTIAN_COAL_POT_11,
    ANIM_EGYPTIAN_COAL_POT_12,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_EGYPTIAN_COAL_POT_01_PAL,
    ANIM_EGYPTIAN_COAL_POT_02_PAL,
    ANIM_EGYPTIAN_COAL_POT_03_PAL,
    ANIM_EGYPTIAN_COAL_POT_04_PAL,
    ANIM_EGYPTIAN_COAL_POT_05_PAL,
    ANIM_EGYPTIAN_COAL_POT_06_PAL,
    ANIM_EGYPTIAN_COAL_POT_07_PAL,
    ANIM_EGYPTIAN_COAL_POT_08_PAL,
    ANIM_EGYPTIAN_COAL_POT_09_PAL,
    ANIM_EGYPTIAN_COAL_POT_10_PAL,
    ANIM_EGYPTIAN_COAL_POT_11_PAL,
    ANIM_EGYPTIAN_COAL_POT_12_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  12,                     // num_images
  0,                      // image_cnt
  225, 230,               // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D29C8 = {
  { // img_ids[30]
    ANIM_EGYPTIAN_CANDLE_A_01,
    ANIM_EGYPTIAN_CANDLE_A_02,
    ANIM_EGYPTIAN_CANDLE_A_03,
    ANIM_EGYPTIAN_CANDLE_A_04,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_EGYPTIAN_CANDLE_A_01_PAL,
    ANIM_EGYPTIAN_CANDLE_A_02_PAL,
    ANIM_EGYPTIAN_CANDLE_A_03_PAL,
    ANIM_EGYPTIAN_CANDLE_A_04_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  4,                      // num_images
  2,                      // image_cnt
  51, 252,                // x, y
  NULL, NULL,             // **images, **palettes
  3, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2A64 = {
  { // img_ids[30]
    ANIM_EGYPTIAN_CANDLE_B_01,
    ANIM_EGYPTIAN_CANDLE_B_02,
    ANIM_EGYPTIAN_CANDLE_B_03,
    ANIM_EGYPTIAN_CANDLE_B_04,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_EGYPTIAN_CANDLE_B_01_PAL,
    ANIM_EGYPTIAN_CANDLE_B_02_PAL,
    ANIM_EGYPTIAN_CANDLE_B_03_PAL,
    ANIM_EGYPTIAN_CANDLE_B_04_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  4,                      // num_images
  0,                      // image_cnt
  215, 256,               // x, y
  NULL, NULL,             // **images, **palettes
  3, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2B00 = {
  { // img_ids[30]
    ANIM_EGYPTIAN_DUST_A_01,
    ANIM_EGYPTIAN_DUST_A_02,
    ANIM_EGYPTIAN_DUST_A_03,
    ANIM_EGYPTIAN_DUST_A_04,
    ANIM_EGYPTIAN_DUST_A_05,
    ANIM_EGYPTIAN_DUST_A_06,
    ANIM_EGYPTIAN_DUST_A_07,
    ANIM_EGYPTIAN_DUST_A_08,
    ANIM_EGYPTIAN_DUST_A_09,
    ANIM_EGYPTIAN_DUST_A_10,
    ANIM_EGYPTIAN_DUST_A_11,
    ANIM_EGYPTIAN_DUST_A_12,
    ANIM_EGYPTIAN_DUST_A_13,
    ANIM_EGYPTIAN_DUST_A_14,
    ANIM_EGYPTIAN_DUST_A_15,
    ANIM_EGYPTIAN_DUST_A_16,
    ANIM_EGYPTIAN_DUST_A_17,
    ANIM_EGYPTIAN_DUST_A_18,
    ANIM_EGYPTIAN_DUST_A_19,
    ANIM_EGYPTIAN_DUST_A_20,
    ANIM_EGYPTIAN_DUST_A_21,
    ANIM_EGYPTIAN_DUST_A_22,
    ANIM_EGYPTIAN_DUST_A_23,
    ANIM_EGYPTIAN_DUST_A_24,
    ANIM_EGYPTIAN_DUST_A_25,
    ANIM_EGYPTIAN_DUST_A_26,
    ANIM_EGYPTIAN_DUST_A_27,
    ANIM_EGYPTIAN_DUST_A_28,
    ANIM_EGYPTIAN_DUST_A_29,
    124
  },
  { // pal_ids[30]
    ANIM_EGYPTIAN_DUST_A_01_PAL,
    ANIM_EGYPTIAN_DUST_A_02_PAL,
    ANIM_EGYPTIAN_DUST_A_03_PAL,
    ANIM_EGYPTIAN_DUST_A_04_PAL,
    ANIM_EGYPTIAN_DUST_A_05_PAL,
    ANIM_EGYPTIAN_DUST_A_06_PAL,
    ANIM_EGYPTIAN_DUST_A_07_PAL,
    ANIM_EGYPTIAN_DUST_A_08_PAL,
    ANIM_EGYPTIAN_DUST_A_09_PAL,
    ANIM_EGYPTIAN_DUST_A_10_PAL,
    ANIM_EGYPTIAN_DUST_A_11_PAL,
    ANIM_EGYPTIAN_DUST_A_12_PAL,
    ANIM_EGYPTIAN_DUST_A_13_PAL,
    ANIM_EGYPTIAN_DUST_A_14_PAL,
    ANIM_EGYPTIAN_DUST_A_15_PAL,
    ANIM_EGYPTIAN_DUST_A_16_PAL,
    ANIM_EGYPTIAN_DUST_A_17_PAL,
    ANIM_EGYPTIAN_DUST_A_18_PAL,
    ANIM_EGYPTIAN_DUST_A_19_PAL,
    ANIM_EGYPTIAN_DUST_A_20_PAL,
    ANIM_EGYPTIAN_DUST_A_21_PAL,
    ANIM_EGYPTIAN_DUST_A_22_PAL,
    ANIM_EGYPTIAN_DUST_A_23_PAL,
    ANIM_EGYPTIAN_DUST_A_24_PAL,
    ANIM_EGYPTIAN_DUST_A_25_PAL,
    ANIM_EGYPTIAN_DUST_A_26_PAL,
    ANIM_EGYPTIAN_DUST_A_27_PAL,
    ANIM_EGYPTIAN_DUST_A_28_PAL,
    ANIM_EGYPTIAN_DUST_A_29_PAL,
    380
  },
  21,                     // num_images
  0,                      // image_cnt
  21, 1,                  // x, y
  NULL, NULL,             // **images, **palettes
  2, 0, 3, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2B9C = {
  { // img_ids[30]
    ANIM_EGYPTIAN_DUST_B_01,
    ANIM_EGYPTIAN_DUST_B_02,
    ANIM_EGYPTIAN_DUST_B_03,
    ANIM_EGYPTIAN_DUST_B_04,
    ANIM_EGYPTIAN_DUST_B_05,
    ANIM_EGYPTIAN_DUST_B_06,
    ANIM_EGYPTIAN_DUST_B_07,
    ANIM_EGYPTIAN_DUST_B_08,
    ANIM_EGYPTIAN_DUST_B_09,
    ANIM_EGYPTIAN_DUST_B_10,
    ANIM_EGYPTIAN_DUST_B_11,
    ANIM_EGYPTIAN_DUST_B_12,
    ANIM_EGYPTIAN_DUST_B_13,
    ANIM_EGYPTIAN_DUST_B_14,
    ANIM_EGYPTIAN_DUST_B_15,
    ANIM_EGYPTIAN_DUST_B_16,
    ANIM_EGYPTIAN_DUST_B_17,
    ANIM_EGYPTIAN_DUST_B_18,
    ANIM_EGYPTIAN_DUST_B_19,
    ANIM_EGYPTIAN_DUST_B_20,
    ANIM_EGYPTIAN_DUST_B_21,
    ANIM_EGYPTIAN_DUST_B_22,
    ANIM_EGYPTIAN_DUST_B_23,
    ANIM_EGYPTIAN_DUST_B_24,
    ANIM_EGYPTIAN_DUST_B_25,
    ANIM_EGYPTIAN_DUST_B_26,
    ANIM_EGYPTIAN_DUST_B_27,
    ANIM_EGYPTIAN_DUST_B_28,
    ANIM_EGYPTIAN_DUST_B_29,
    164
  },
  { // pal_ids[30]
    ANIM_EGYPTIAN_DUST_B_01_PAL,
    ANIM_EGYPTIAN_DUST_B_02_PAL,
    ANIM_EGYPTIAN_DUST_B_03_PAL,
    ANIM_EGYPTIAN_DUST_B_04_PAL,
    ANIM_EGYPTIAN_DUST_B_05_PAL,
    ANIM_EGYPTIAN_DUST_B_06_PAL,
    ANIM_EGYPTIAN_DUST_B_07_PAL,
    ANIM_EGYPTIAN_DUST_B_08_PAL,
    ANIM_EGYPTIAN_DUST_B_09_PAL,
    ANIM_EGYPTIAN_DUST_B_10_PAL,
    ANIM_EGYPTIAN_DUST_B_11_PAL,
    ANIM_EGYPTIAN_DUST_B_12_PAL,
    ANIM_EGYPTIAN_DUST_B_13_PAL,
    ANIM_EGYPTIAN_DUST_B_14_PAL,
    ANIM_EGYPTIAN_DUST_B_15_PAL,
    ANIM_EGYPTIAN_DUST_B_16_PAL,
    ANIM_EGYPTIAN_DUST_B_17_PAL,
    ANIM_EGYPTIAN_DUST_B_18_PAL,
    ANIM_EGYPTIAN_DUST_B_19_PAL,
    ANIM_EGYPTIAN_DUST_B_20_PAL,
    ANIM_EGYPTIAN_DUST_B_21_PAL,
    ANIM_EGYPTIAN_DUST_B_22_PAL,
    ANIM_EGYPTIAN_DUST_B_23_PAL,
    ANIM_EGYPTIAN_DUST_B_24_PAL,
    ANIM_EGYPTIAN_DUST_B_25_PAL,
    ANIM_EGYPTIAN_DUST_B_26_PAL,
    ANIM_EGYPTIAN_DUST_B_27_PAL,
    ANIM_EGYPTIAN_DUST_B_28_PAL,
    ANIM_EGYPTIAN_DUST_B_29_PAL,
    420
  },
  29,                     // num_images
  0,                      // image_cnt
  248, 6,                 // x, y
  NULL, NULL,             // **images, **palettes
  1, 0, 200, 0, 0,        // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

AnimParams D_800D2C38 = {
  { // img_ids[30]
    ANIM_AFRICAN_VOLCANO_SMOKE_01,
    ANIM_AFRICAN_VOLCANO_SMOKE_02,
    ANIM_AFRICAN_VOLCANO_SMOKE_03,
    ANIM_AFRICAN_VOLCANO_SMOKE_04,
    ANIM_AFRICAN_VOLCANO_SMOKE_05,
    ANIM_AFRICAN_VOLCANO_SMOKE_06,
    ANIM_AFRICAN_VOLCANO_SMOKE_07,
    ANIM_AFRICAN_VOLCANO_SMOKE_08,
    ANIM_AFRICAN_VOLCANO_SMOKE_09,
    ANIM_AFRICAN_VOLCANO_SMOKE_10,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  { // pal_ids[30]
    ANIM_AFRICAN_VOLCANO_SMOKE_01_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_02_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_03_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_04_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_05_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_06_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_07_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_08_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_09_PAL,
    ANIM_AFRICAN_VOLCANO_SMOKE_10_PAL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
  },
  10,                     // num_images
  0,                      // image_cnt
  256, 13,                // x, y
  NULL, NULL,             // **images, **palettes
  3, 0, 0, 0, 0,          // num_intra_frames, intra_frame_cnt, num_inter_frames, inter_frame_cnt, fade_alpha
  0.0, 0.0,               // fade_rate, alpha_val
  0xFF, 0xFF, 0xFF, 0xFF  // red, green, blue, alpha
};

void func_800764A0(AnimParams *dest, AnimParams *src) {
  dest->images = src->images;
  dest->palettes = src->palettes;
}

void func_800764B8(AnimParams *animParams) {
  s32 i;

  config_setting_t *root, *anims;
  root = config_root_setting(&g_anims_cfg);
  anims = config_setting_get_member(root, "anims");

  main_8004A34C_threeliner();

  animParams->images = (void **) n64HeapAlloc(animParams->num_images * sizeof(void *));
  animParams->palettes = (void **) n64HeapAlloc(animParams->num_images * sizeof(void *));

  for (i = 0; i < animParams->num_images; i++) {
    animParams->images[i] = al_load_bitmap(config_setting_get_string_elem(anims, animParams->img_ids[i]));
  }
  if (animParams->fade_alpha) {
    animParams->fade_rate = 1.0 / (f32) (animParams->num_images / 2);
    animParams->alpha_val = 0.0;
  }
}

void func_800766C8(AnimParams *animParams) {
  s32 i;

  for (i = animParams->num_images - 1; i >= 0; i--) {
    if (animParams->images[i] != NULL) {
      al_destroy_bitmap(animParams->images[i]);
    }
  }
  if (animParams->images != NULL) {
    n64HeapUnalloc(animParams->images);
  }
  if (animParams->palettes != NULL) {
    n64HeapUnalloc(animParams->palettes);
  }
}

void func_800767C0(AnimParams *animParams) {
  if (animParams->num_inter_frames != 0) {
    if (animParams->num_inter_frames < animParams->inter_frame_cnt) {
      if (animParams->inter_frame_cnt > (animParams->num_inter_frames + animParams->num_images)) {
        animParams->inter_frame_cnt = 0;
        return;
      }

      if (animParams->num_intra_frames != 0) {
        if (animParams->intra_frame_cnt == 0) {
          animParams->intra_frame_cnt = animParams->num_intra_frames;
          animParams->image_cnt = (animParams->image_cnt + 1) % animParams->num_images;
          animParams->inter_frame_cnt++;
          if (animParams->fade_alpha) {
            animParams->alpha_val += animParams->fade_rate;
            if (animParams->alpha_val >= 1.0) {
              animParams->alpha_val = 1.0;
              animParams->fade_rate = (1.0 / (f32) (animParams->num_images / 2)) * -1;
            }
            if (animParams->alpha_val <= 0.0) {
              animParams->alpha_val = 0.0;
              animParams->fade_rate = 1.0 / (f32) (animParams->num_images / 2);
            }
            animParams->alpha = animParams->alpha_val * 255;
          }
        } else {
          animParams->intra_frame_cnt--;
        }
      } else {
        if (animParams->fade_alpha) {
          animParams->alpha_val += animParams->fade_rate;
          if (animParams->alpha_val >= 1.0) {
            animParams->alpha_val = 1.0;
            animParams->fade_rate = (1.0 / (f32) (animParams->num_images / 2)) * -1;
          }
          if (animParams->alpha_val <= 0.0) {
            animParams->alpha_val = 0.0;
            animParams->fade_rate = 1.0 / (f32) (animParams->num_images / 2);
          }
          animParams->alpha = animParams->alpha_val * 255;
        }
        animParams->image_cnt = (animParams->image_cnt + 1) % animParams->num_images;
        animParams->inter_frame_cnt++;
      }

      func_8005BBFC(&g_gdl);
      weird_lots_of_magic_number_setting_66xrefs(&g_gdl, animParams->images[animParams->image_cnt], animParams->palettes[animParams->image_cnt], animParams->x, animParams->y, animParams->red, animParams->green, animParams->blue, animParams->alpha);
      func_8005BE40(&g_gdl);

    } else {
      animParams->inter_frame_cnt++;
    }

  } else {
    if (animParams->num_intra_frames != 0) {
      if (animParams->intra_frame_cnt == 0) {
        animParams->intra_frame_cnt = animParams->num_intra_frames;
        animParams->image_cnt = (animParams->image_cnt + 1) % animParams->num_images;
      } else {
        animParams->intra_frame_cnt--;
      }
    } else {
      animParams->image_cnt = (animParams->image_cnt + 1) % animParams->num_images;
    }

    func_8005BBFC(&g_gdl);
    weird_lots_of_magic_number_setting_66xrefs(&g_gdl, animParams->images[animParams->image_cnt], animParams->palettes[animParams->image_cnt], animParams->x, animParams->y, animParams->red, animParams->green, animParams->blue, animParams->alpha);
    func_8005BE40(&g_gdl);
  }
}

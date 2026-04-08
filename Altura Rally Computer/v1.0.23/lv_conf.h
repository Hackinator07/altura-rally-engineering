/**
 * lv_conf.h – LVGL 9.x config for ESP32 CYD (320x240 landscape, ILI9341, RGB565)
 *
 * Place at: Arduino/libraries/lv_conf.h
 * (one level ABOVE the lvgl folder, NOT inside it)
 *
 * NOTE: Do NOT #include <stdint.h> or anything else here.
 * LVGL v9 has assembly sections that break if stdint.h is included in this file.
 *
 * v1.0.17-NeoGPS: LV_USE_SPAN enabled (1) — TOTAL/TRIP lv_spangroup readouts.
 *   LV_USE_LINE and LV_USE_SCALE remain 0.
 *   lv_scale.c is absent from the PlatformIO LVGL 9.2.2 package.
 *   HDOP zone bar implemented with plain lv_obj rects instead.
 *
 * v1.0.20-NeoGPS: LV_USE_TABLE enabled (1) — GPS diagnostics screen (scr_gps)
 *   refactored from manual lv_label pairs to a single lv_table widget.
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#if 1  /* Set to "1" to enable content */

/*====================
   COLOR SETTINGS
 *====================*/
/* ILI9341 is 16-bit RGB565 */
#define LV_COLOR_DEPTH 16

/* LV_COLOR_16_SWAP was REMOVED in LVGL v9.
 * Byte-swap for SPI hardware is handled at runtime in setup() via:
 *   lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565A8);
 * or by the lv_tft_espi_create() driver which handles this internally. */

/*====================
   MEMORY SETTINGS
 *====================*/
#define LV_MEM_CUSTOM  0
#define LV_MEM_SIZE    (64U * 1024U)   /* 64 kB LVGL heap */
#define LV_MEM_ADR     0               /* 0 = allocate automatically */

/*====================
   HAL / TICK
 *====================*/
/* Tick driven by lv_tick_inc(5) called in loop() — no custom tick needed */
#define LV_TICK_CUSTOM 0

#define LV_DPI_DEF 130

/*====================
   SPRINTF
 *====================*/
#define LV_SPRINTF_USE_FLOAT 1

/*====================
   DRAWING
 *====================*/
#define LV_DRAW_BUF_STRIDE_ALIGN    1
#define LV_DRAW_BUF_ALIGN           4
#define LV_SHADOW_CACHE_SIZE        0
#define LV_CIRCLE_CACHE_SIZE        4

/*====================
   LOGGING
 *====================*/
#define LV_USE_LOG      0
#define LV_LOG_PRINTF   0

/*====================
   ASSERTIONS
 *====================*/
#define LV_USE_ASSERT_NULL          1
#define LV_USE_ASSERT_MALLOC        1
#define LV_USE_ASSERT_STYLE         0
#define LV_USE_ASSERT_MEM_INTEGRITY 0
#define LV_USE_ASSERT_OBJ           0

#define LV_ASSERT_HANDLER while(1);

/*====================
   BUILT-IN FONTS
   Fonts used by rally UI:
     12  — GPS signal status label, HDOP label
     14  — button text, default fallback
     16  — TOTAL/TRIP headers, mph/avg/max unit label
     24  — font picker screen preview row fallback (Montserrat)
     36  — TOTAL/TRIP distance values
     48  — speed number
 *====================*/
#define LV_FONT_MONTSERRAT_8  1   /* splash version string */
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 1
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 1

// Custom converted fonts for numeric readouts (speed, distances).
// B612 — Airbus cockpit readability font (SIL OFL)
// DSEG7 — 7-segment LED Classic (SIL OFL)
// DSEG14 — 14-segment LED Classic (SIL OFL)
// DIN1451 — Alte DIN 1451 Mittelschrift (SIL OFL)
// LCD, Segment7, ShareTechMono — see src/ for .c files
// Corresponding .c files must be present in the sketch/src folder.
// _24 sizes used on scr_font preview rows; _36/_48 used on main screen readouts.
#define LV_FONT_B612_36    1
#define LV_FONT_B612_48    1
#define LV_FONT_DSEG7_36   1
#define LV_FONT_DSEG7_48   1
#define LV_FONT_DSEG14_36  1
#define LV_FONT_DSEG14_48  1
#define LV_FONT_DIN1451_36 1
#define LV_FONT_DIN1451_48 1

#define LV_FONT_DEFAULT &lv_font_montserrat_14

#define LV_FONT_FMT_TXT_LARGE   0
#define LV_USE_FONT_SUBPX       0
#define LV_USE_FONT_PLACEHOLDER 1

/*====================
   TEXT
 *====================*/
#define LV_TXT_ENC                 LV_TXT_ENC_UTF8
#define LV_TXT_BREAK_CHARS         " ,.;:-_"
#define LV_TXT_LINE_BREAK_LONG_LEN 0
#define LV_TXT_COLOR_CMD           "#"
#define LV_USE_BIDI                0
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*====================
   WIDGETS
   Only what the rally UI uses
 *====================*/
#define LV_USE_ARC        0
#define LV_USE_BAR        0
#define LV_USE_BTN        1   /* navigation and action buttons throughout */
#define LV_USE_LED        1   /* HDOP, GPS, and SAT leds on scr_main */
#define LV_USE_BTNMATRIX  0
#define LV_USE_CANVAS     0
#define LV_USE_CHECKBOX   0
#define LV_USE_DROPDOWN   0
#define LV_USE_IMG        1   /* splash screen loon silhouette (lv_img + PROGMEM) */
#define LV_USE_LABEL      1   /* all text labels */
#define LV_USE_LINE       0   /* not used by rally UI */
#define LV_USE_SCALE      0   /* not used — lv_scale.c absent from PlatformIO LVGL 9.2.2 package */
#define LV_USE_ROLLER     0
#define LV_USE_SLIDER     0
#define LV_USE_SWITCH     0
#define LV_USE_TEXTAREA   0
#define LV_USE_TABLE      1   /* GPS diagnostics lv_table on scr_gps (v1.0.20-NeoGPS) */

/*====================
   EXTRA WIDGETS (none used)
 *====================*/
#define LV_USE_ANIMIMG    0
#define LV_USE_CALENDAR   0
#define LV_USE_CHART      0
#define LV_USE_COLORWHEEL 0
#define LV_USE_IMGBTN     0
#define LV_USE_KEYBOARD   0
#define LV_USE_LIST       0
#define LV_USE_MENU       0
#define LV_USE_METER      0
#define LV_USE_MSGBOX     0
#define LV_USE_SPAN       1   /* TOTAL/TRIP lv_spangroup readouts on scr_main (v1.0.17-NeoGPS) */
#define LV_USE_SPINBOX    0
#define LV_USE_SPINNER    0
#define LV_USE_TABVIEW    0
#define LV_USE_TILEVIEW   0
#define LV_USE_WIN        0

/*====================
   THEMES (none used — custom styles applied in code)
 *====================*/
#define LV_USE_THEME_DEFAULT 0
#define LV_USE_THEME_SIMPLE  0
#define LV_USE_THEME_MONO    0

/*====================
   LAYOUTS
 *====================*/
#define LV_USE_FLEX  1   /* speed container row layout, GPS/theme/font scroll containers */
#define LV_USE_GRID  0

/*====================
   DISPLAY DRIVER
 *====================*/
#define LV_USE_TFT_ESPI 1   /* required for lv_tft_espi_create() */

/*====================
   FILE SYSTEM (not used)
 *====================*/
#define LV_USE_FS_STDIO  0
#define LV_USE_FS_POSIX  0
#define LV_USE_FS_WIN32  0
#define LV_USE_FS_FATFS  0

/*====================
   MISC
 *====================*/
#define LV_USE_SNAPSHOT   0
#define LV_USE_MONKEY     0
#define LV_USE_GRIDNAV    0
#define LV_USE_FRAGMENT   0
#define LV_USE_IMGFONT    0
#define LV_USE_MSG        0
#define LV_USE_IME_PINYIN 0

/* CRITICAL: prevents lv_blend_helium.S and example files from compiling */
#define LV_BUILD_EXAMPLES 0

#endif /* if 1 */

#endif /* LV_CONF_H */


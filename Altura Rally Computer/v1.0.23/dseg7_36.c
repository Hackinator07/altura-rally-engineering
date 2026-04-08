/*******************************************************************************
 * Size: 36 px
 * Bpp: 2
 * Opts: --bpp 2 --size 36 --no-compress --stride 1 --align 1 --font DSEG7Classic-Regular.ttf --range 46,48 --format lvgl -o dseg7_36.c
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif



#ifndef DSEG7_36
#define DSEG7_36 1
#endif

#if DSEG7_36

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+002E "." */
    0x5, 0x3, 0xfc, 0x3f, 0xc3, 0xfc, 0x1f, 0x40,

    /* U+0030 "0" */
    0x1, 0x55, 0x55, 0x55, 0x55, 0x0, 0x2f, 0xff,
    0xff, 0xff, 0xff, 0x1, 0x3f, 0xff, 0xff, 0xff,
    0xf5, 0x1f, 0x3f, 0xff, 0xff, 0xff, 0x6e, 0x7f,
    0x0, 0x0, 0x0, 0x1, 0xfd, 0xfc, 0x0, 0x0,
    0x0, 0xb, 0xf7, 0xf0, 0x0, 0x0, 0x0, 0x2f,
    0xdf, 0xc0, 0x0, 0x0, 0x0, 0xbf, 0x7f, 0x0,
    0x0, 0x0, 0x2, 0xfd, 0xfc, 0x0, 0x0, 0x0,
    0xb, 0xf7, 0xf0, 0x0, 0x0, 0x0, 0x2f, 0xdf,
    0xc0, 0x0, 0x0, 0x0, 0xbf, 0x7f, 0x0, 0x0,
    0x0, 0x2, 0xfd, 0xfc, 0x0, 0x0, 0x0, 0xb,
    0xf7, 0xf0, 0x0, 0x0, 0x0, 0x2f, 0xdf, 0xc0,
    0x0, 0x0, 0x0, 0xbf, 0x7d, 0x0, 0x0, 0x0,
    0x0, 0xfd, 0xd0, 0x0, 0x0, 0x0, 0x0, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x58, 0x0, 0x0,
    0x0, 0x0, 0xa, 0x7c, 0x0, 0x0, 0x0, 0x0,
    0xbd, 0xf8, 0x0, 0x0, 0x0, 0x7, 0xf7, 0xf0,
    0x0, 0x0, 0x0, 0x2f, 0xdf, 0xc0, 0x0, 0x0,
    0x0, 0xbf, 0x7f, 0x0, 0x0, 0x0, 0x2, 0xfd,
    0xfc, 0x0, 0x0, 0x0, 0xb, 0xf7, 0xf0, 0x0,
    0x0, 0x0, 0x2f, 0xdf, 0xc0, 0x0, 0x0, 0x0,
    0xbf, 0x7f, 0x0, 0x0, 0x0, 0x2, 0xfd, 0xfc,
    0x0, 0x0, 0x0, 0xb, 0xf7, 0xf0, 0x0, 0x0,
    0x0, 0x2f, 0xdf, 0xc0, 0x0, 0x0, 0x0, 0xbf,
    0x7f, 0x0, 0x0, 0x0, 0x2, 0xfd, 0xf5, 0x55,
    0x55, 0x55, 0x53, 0xf3, 0x9f, 0xff, 0xff, 0xff,
    0xf7, 0x81, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x3,
    0xff, 0xff, 0xff, 0xff, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 0, .box_w = 6, .box_h = 5, .ofs_x = -3, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 470, .box_w = 23, .box_h = 37, .ofs_x = 3, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint8_t glyph_id_ofs_list_0[] = {
    0, 0, 1
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 46, .range_length = 3, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = glyph_id_ofs_list_0, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_FULL
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif

};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t dseg7_36 = {
#else
lv_font_t dseg7_36 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 37,          /*The maximum line height required by the font*/
    .base_line = 0,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -4,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if DSEG7_36*/

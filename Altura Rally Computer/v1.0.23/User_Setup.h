// ============================================================
// User_Setup.h for TFT_eSPI
// Configured for ESP32-2432S028R (Cheap Yellow Display / CYD)
// Source: Random Nerd Tutorials verified working configuration
// https://randomnerdtutorials.com/lvgl-cheap-yellow-display-esp32-2432s028r/
// Place this file in: Arduino/libraries/TFT_eSPI/User_Setup.h
// ============================================================

#define USER_SETUP_INFO "User_Setup"

// Driver - ILI9341_2 variant for CYD
#define ILI9341_2_DRIVER

// Native portrait panel dimensions — rotation to landscape is handled in
// TFT_WIDTH/HEIGHT are portrait native dims. Display is rotated to landscape
// by lv_display_set_rotation(disp, LV_DISPLAY_ROTATION_270) in setup().
// Do NOT add TFT_ROTATION here; it conflicts with LVGL's software rotation.
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// Backlight
#define TFT_BL   21
#define TFT_BACKLIGHT_ON HIGH

// CYD TFT SPI pins (HSPI bus)
#define TFT_MISO 12
#define TFT_MOSI 13
#define TFT_SCLK 14
#define TFT_CS   15
#define TFT_DC    2
#define TFT_RST  -1

// XPT2046 touch chip select (VSPI bus)
#define TOUCH_CS 33

// Use HSPI for TFT — leaves VSPI free for XPT2046
#define USE_HSPI_PORT

// SPI frequencies
#define SPI_FREQUENCY       55000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000

// Fonts
#define LOAD_GLCD
#define LOAD_FONT2
#define LOAD_FONT4
#define LOAD_FONT6
#define LOAD_FONT7
#define LOAD_FONT8
#define LOAD_GFXFF
#define SMOOTH_FONT

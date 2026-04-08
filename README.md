# altura-rally-engineering

<p align="center">
  <img width="400" alt="loonbrophoto" src="https://github.com/user-attachments/assets/4795f775-3684-4309-998c-90018051f487" />
</p>

A codriver first interface tool and rally navigation computer for competitive stage rally use. GPS-derived speed display and odometer accumulation on a 320×240 touchscreen. Built on the CYD (ESP32-2432S028R), NeoGPS, LVGL 9, FreeRTOS, and a u-blox NEO-6M with UBX binary configuration.

**Authors:** Jason Hack, Ciprian Cristea, Eli Goethel

---

## Hardware

| Component | Part |
|---|---|
| MCU / Display | ESP32-2432S028R "Cheap Yellow Display" (CYD) |
| Display driver | ILI9341 (CYD v1/v2) · ST7789 (CYD v3) |
| Touchscreen | XPT2046 resistive |
| GPS module | u-blox NEO-6M (active antenna recommended) |
| GPS UART | HardwareSerial 2 — RX GPIO 22, TX GPIO 27 |

The NEO-6M is configured at boot via UBX binary commands: 57600 baud, 5 Hz update rate, Automotive dynamic model, Static Hold at 40 cm/s, SBAS/WAAS differential corrections enabled, GGA+RMC only (all other sentences disabled). Settings are volatile and re-applied every power cycle.

---

## Software

| Library | Version |
|---|---|
| LVGL | 9.2.2 |
| TFT_eSPI (Bodmer) | 2.5.x |
| NeoGPS (SlashDevin) | 4.x |
| XPT2046_Touchscreen (Stoffregen) | 1.4 |

**Framework:** Arduino via PlatformIO / VS Code  
**RTOS:** FreeRTOS dual-core — GPS pipeline on Core 0, LVGL UI on Core 1  
**Persistence:** ESP32 NVS (odometer, UTC offset, brightness, theme, font)

---

## Features

### Main Screen
- **Speed** — current, average, and max speed (tap the speed container to cycle)
- **TOTAL odometer** — session accumulation in miles, NVS-persisted
- **TRIP odometer** — resettable interval distance
- **GPS / SATS / HDOP status LEDs** — color-coded and blinking indicators for fix state, satellite count (2D/3D), and HDOP band
- **UTC clock** — GPS time with configurable UTC offset (−14 to +14)
- **FRZ button** — freeze the display for note-taking at a waypoint; blinks red while frozen
- **CLR ODO / CLR INT** — long-press to clear total or trip odometer

### GPS Diagnostics Screen
Scrollable table showing: latitude, longitude, altitude, HDOP, fix type, satellite count, rejected step count (REJ STP), sanity rejection count (REJ SAN), and location-false blackout event count (LLF). HDOP, REJ STP, and REJ SAN rows are color-coded amber/red at configurable thresholds.

### Menu
- **Brightness** — 4-step PWM backlight (25 / 50 / 75 / 100%)
- **GPS Diagnostics** — live 9-row diagnostic table: Latitude, Longitude, Altitude (ft), HDOP, Fix Quality (EXCL / GOOD / POOR / NO FIX), Satellites in use, Rejected Steps, Rejected Sanity, and Last Location Failures (LLF).
- **UTC Clock** — pending-value pattern; CONFIRM commits, BACK discards
- **Theme picker** — 17 themes including Night Stage, Day Stage, Stealth, Cobalt, Ember, Racetrack, Enduro, and more
- **Font picker** — 8 selectable numeric fonts: Montserrat, B612, DIN1451, DSEG14, DSEG7, LCD14, Segment7, Share Tech Mono
- **Factory Reset** — confirmed two-tap reset; clears NVS and resets all settings to defaults

---

## GPS Pipeline

NeoGPS is used instead of TinyGPSPlus for one primary reason: **fix coherency**. NeoGPS accumulates an entire RMC+GGA sentence-set into a single `gps_fix` struct before returning it. TinyGPSPlus exposes fields as they arrive — speed from the current RMC can be paired with a location from a stale GGA. In testing that stale-field mixing produced measurable odometer error. NeoGPS eliminates it at the parser level.

Odometer accumulation gates:
- Minimum speed: 1.864 mph (stationary noise rejection)
- Speed sanity: rejects any fix where speed changed more than 124 mph since the last accepted fix
- Step cap: rejects any single haversine increment over 1.0 mile (phantom jump guard)
- HDOP gate: amber ≥ 2.5, red > 3.5 (LED indicators only — not an accumulation gate)

NVS saves every 1 mile of accumulation to limit flash wear (~480 writes/day at 60 mph vs. ~7700 writes/day at the prior 100 m threshold).

---

## NeoGPS Configuration

Two config files must be present alongside the sketch and must be edited inside the PlatformIO libdeps copy (`.pio/libdeps/<env>/NeoGPS/`):

**`GPSfix_cfg.h`** — enables LOCATION, SPEED, TIME, HDOP, SATELLITES only.

**`NMEAGPS_cfg.h`** — critical settings:
- `LAST_SENTENCE_IN_INTERVAL` must be `NMEA_GGA` — the NEO-6M outputs RMC before GGA, so GGA is the sentence that closes each fix set
- `NMEAGPS_ACCUMULATE_FIX` must be enabled
- GSV output must be disabled on the module (handled by UBX init) — trailing GSV sentences disrupt fix coherency

---

## Build

```ini
[env:esp32dev]
platform  = espressif32
board     = esp32dev
framework = arduino
lib_deps  =
  lvgl/lvgl @ ^9.2.2
  bodmer/TFT_eSPI @ ^2.5.43
  paulstoffregen/XPT2046_Touchscreen @ ^1.4
  slashdevin/NeoGPS @ ^4.2.9
build_flags =
  -DUSER_SETUP_LOADED
  -DILI9341_2_DRIVER
  -DTFT_WIDTH=240
  -DTFT_HEIGHT=320
  -DTFT_MISO=12
  -DTFT_MOSI=13
  -DTFT_SCLK=14
  -DTFT_CS=15
  -DTFT_DC=2
  -DTFT_RST=-1
  -DTFT_BL=21
  -DTFT_BACKLIGHT_ON=1
  -DTOUCH_CS=33
  -DUSE_HSPI_PORT
  -DSPI_FREQUENCY=55000000
  -DSPI_READ_FREQUENCY=20000000
  -DSPI_TOUCH_FREQUENCY=2500000
  -DLV_CONF_INCLUDE_SIMPLE
```

For CYD v3 (ST7789), replace `-DILI9341_2_DRIVER` with `-DST7789_DRIVER -DTFT_INVERSION_ON -DTFT_RGB_ORDER=TFT_BGR`.

Custom font C files (`b612_*.c`, `din1451_*.c`, `dseg14_*.c`, etc.) live in `src/` alongside the sketch. Each is generated via `lv_font_conv --bpp 2 --range 0x20-0x7E` at 24, 36, and 48pt. Fonts guarded by `#ifdef` fall back to Montserrat if the C files are absent.

---

## Simulation

The project can simulate in Wokwi (VS Code extension) using `wokwi-ili9341` in `diagram.json`. NVS state persists between simulation runs unless explicitly cleared. There is no `wokwi-st7789` part — the `diagram.json` does not need updating for ST7789 hardware builds.

---

## Firmware Branches

| Branch | GPS Library | Notes |
|---|---|---|
| `main` (v1.0.x-NeoGPS) | NeoGPS | Coherent RMC+GGA fix sets; current active development branch |

---

## License

Hardware designs and firmware are released for personal and educational use. All included fonts are SIL Open Font License.

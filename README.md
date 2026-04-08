# Altura Rally Engineering

<p align="center">
  <img width="400" alt="loonbrophoto" src="https://github.com/user-attachments/assets/4795f775-3684-4309-998c-90018051f487" />
</p>

A codriver first interface tool and rally navigation computer for competitive stage rally use. GPS-derived speed display and odometer accumulation on a 320×240 touchscreen. Built on the CYD (ESP32-2432S028R), NeoGPS, LVGL 9, FreeRTOS, and a u-blox NEO-6M with UBX binary configuration.

**Authors:** Jason Hack, Ciprian Cristea, Eli Goethel

---

### Table of Contents
<p>
  <a href="#hardware">Hardware</a> <br/>
  <a href="#software">Software</a> <br/>
  <a href="#features">Features</a> <br/>
  <a href="#gps-pipeline">GPS Pipeline</a> <br/>
  <a href="#neogps-configuration">NeoGPS Configuration</a> <br/>
  <a href="#build">Build</a> <br/>
  <a href="#simulation">Simulation</a> <br/>
  <a href="#firmware-branches">Firmware Branches</a> <br/>
  <a href="#license-agreement">License Agreement</a> <br/>
  <a href="#9-third-party-software-acknowledgments">Third-Party Software Acknowledgments</a>
</p>
<br/>

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

## License Agreement

---

> **PLEASE READ THIS AGREEMENT CAREFULLY BEFORE DOWNLOADING FIRMWARE OR POWERING ON OR USING THE ALTURA RALLY COMPUTER. BY DOWNLOADING, ACTIVATING, INSTALLING, OR OTHERWISE USING THIS DEVICE, YOU ("USER") AGREE TO BE LEGALLY BOUND BY ALL TERMS BELOW. IF YOU DO NOT AGREE, DO NOT ACCESS FIRMWARE OR POWER ON THE DEVICE AND RETURN IT IMMEDIATELY IN ITS ORIGINAL UNOPENED PACKAGING.**

---

## 1. Purpose and Intended Use

The Altura Rally Computer ("the Device") is a GNSS-based odometer and navigation interface developed specifically for motorsport and competition environments. Hardware designs and firmware are released for personal and educational use. All included fonts are SIL Open Font License.

- **Exclusive Use.** The Device is intended exclusively for organized racing, rallying, and off-road competition. It is not intended as a primary navigational aid on public roads.
- **Regulatory Compliance.** It is the User's sole responsibility to ensure installation and use comply with all applicable local, state, federal, and event-sanctioning-body regulations.
- **Road Use.** The Device is not homologated for road use. If operated on public roads — including liaison sections or recce runs — the User must ensure: (a) full compliance with applicable traffic laws; (b) that installation does not interfere with primary instruments or obstruct driver vision; and (c) compliance with all applicable national and regional legal requirements. Altura accepts no liability for consequences arising from use on public roads.

---

## 2. No Guarantee of Precision — Information Only

- **Informational Use Only.** Output data — including speed, distance, and position — must not be construed as a guarantee of accuracy.
- **No Safety-Critical Reliance.** The Device must not be used as the sole basis for safety-critical navigation, vehicle operation, or stage timing.
- **Environmental Limitations.** Altura is not liable for errors arising from GPS signal loss, satellite geometry degradation, multipath interference, or environmental conditions including dense forest canopy, urban structures, tunnels, or atmospheric interference.

---

## 3. Assumption of Risk & Limitation of Liability

By purchasing or using the Device or its firmware, the User explicitly and voluntarily assumes all risks associated with motorsport competition and GNSS-based instrumentation in high-performance environments.

- **Scope of Disclaimer.** To the fullest extent permitted by applicable law, Altura disclaims all liability for personal injury, death, property damage, financial loss, or competitive disadvantage arising from the use or failure of this Device.
- **Fault Independence.** This limitation applies regardless of legal theory, including product malfunction, hardware failure, firmware error, GPS signal degradation, improper installation, or operator misuse.
- **Installation Responsibility.** Altura is not responsible for damages from improper mounting, wiring, or integration with vehicle electrical systems. Do not mount over airbag deployment zones or in a manner that obstructs driver or co-driver visibility.

> **⚠ Electrical Warning:** Installation may require modifications to your vehicle's electrical system. Incorrect installation may damage both the Device and the vehicle. Installation by a qualified automotive electrician is strongly recommended.

- **Cap on Liability.** In no event shall Altura's total liability to any User exceed the original purchase price paid for the Device.

---

## 4. Firmware & Open-Source License

The firmware is distributed under the **GNU General Public License v3.0 (GPL-3.0)**. Full text: https://www.gnu.org/licenses/gpl-3.0.html

- **Open-Source Distribution.** The complete source code is available through the official Altura firmware repository.
- **Copyleft Requirement.** Any modified version must also be distributed under GPL-3.0 with complete source code.
- **Modification Responsibility.** Any modifying party must: (a) clearly mark changes; (b) preserve all copyright notices; (c) make source code available under GPL-3.0; and (d) ensure full GPL-3.0 compliance.
- **"AS-IS" Provision.** All firmware is provided "AS-IS" without warranty of any kind. Performance characteristics apply only to unmodified firmware on official Altura hardware.
- **Modified Firmware and Warranty.** Hardware warranty is void if the Device runs modified firmware. This does not restrict firmware rights under GPL-3.0.

---

## 5. Hardware Integrity Policy

- **Sealed Unit.** Opening the casing, disassembling the device, or modifying internal hardware immediately and permanently voids all warranty coverage.
- **Third-Party Hardware.** Altura is not responsible for Device behaviour resulting from hardware modifications or integration with non-approved external hardware.

---

## 6. Limited Hardware Warranty

- **Coverage Period.** Altura warrants the hardware against defects in materials and workmanship for **12 months** from original delivery.
- **Conditions.** Non-transferable. Covers manufacturing defects under normal intended use. Does not cover competition impact, improper installation, water ingress, or unauthorized modification.
- **Sole Remedy.** At Altura's sole discretion: repair or replacement of the defective unit.
- **Warranty Voidance.** Void upon: (a) opening or disassembling the unit; (b) operating on modified firmware; (c) damage from improper installation or misuse; or (d) physical modification to the hardware.

---

## 7. Return & Refund Policy

- **Return Window.** Returns accepted within **14 days** of confirmed delivery only.
- **Eligibility.** Unused, in original condition and original packaging. Any unit showing evidence of installation or activation is ineligible.
- **Shipping Costs.** Customer is responsible for return shipping. Costs reimbursed only for verified manufacturing defects.
- **Refund Processing.** Approved refunds issued within 10 business days of confirmed receipt and inspection.

---

## 8. Governing Law & Severability

This Agreement shall be governed by the laws of the State of Wisconsin, without regard to conflict-of-law principles. If any provision is found unenforceable, it shall be modified to the minimum extent necessary, and all remaining provisions remain in full force.

---

## Acceptance of Terms

**Use of the Altura Rally Computer — including powering on the device — constitutes full and binding acceptance of all terms in this Agreement.** The firmware is separately governed by GPL-3.0, independent of and in addition to this Agreement.

---

## 9. Third-Party Software Acknowledgments

| Component | License | Notes |
|---|---|---|
| NeoGPS | GPL-3.0 | GNSS parsing — primary driver of GPL-3.0 license choice |
| TinyGPSPlus | LGPL-2.1 | GNSS parsing (main branch) |
| LVGL | MIT | Embedded graphics library |
| TFT_eSPI | MIT | TFT display driver |
| FreeRTOS | MIT | Real-time operating system |
| Arduino ESP32 Core | LGPL-2.1 | Hardware abstraction layer |
| Adafruit FT6206 | BSD/MIT | Capacitive touch (Wokwi simulation only) |

**GPS Signal Standards:** The Device operates using GPS L1 C/A signals per the U.S. DoD GPS SPS Performance Standard, 5th Edition (April 2020). The U.S. Government does not guarantee GPS availability and reserves the right to modify or discontinue SPS signals.

**Acknowledgments:** Altura gratefully acknowledges foundational contributions from the University of Michigan, Michigan Technological University, the Free Software Foundation, and the U.S. Department of Defense / U.S. Space Force. We thank the open-source community whose freely shared work made this project possible.

---

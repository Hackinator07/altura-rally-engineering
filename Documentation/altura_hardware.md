# Altura Rally Computer
## Hardware Reference — v1.0

**Authors:** Jason Hack · Eli Goethel

---

## 1. Hardware Components

### Microcontroller — ESP32-2432S028R

| Parameter | Value |
|---|---|
| Processor | Dual-core Xtensa LX6 |
| Clock speed | 160 MHz (reduced from 240 MHz for power and thermals) |
| Core 0 role | GPS data processing (background task, priority 2) |
| Core 1 role | Display and touch (foreground, Arduino loop) |
| Wireless | WiFi and Bluetooth disabled at boot — reduces RF noise |
| Inter-core sync | FreeRTOS mutex protecting the shared data structure |

### Display — ILI9341 TFT, 320×240 pixels

| Parameter | Value |
|---|---|
| Interface | SPI at 55 MHz via TFT_eSPI library |
| Orientation | Physical portrait; rotated to landscape in firmware |
| Backlight | GPIO 21, LEDC PWM at 5 kHz / 8-bit — four brightness levels |
| Rendering | Two DMA-capable draw buffers (~30 KB each) — double-buffered |

### Touch — XPT2046 Resistive Touchscreen

| Parameter | Value |
|---|---|
| Bus | VSPI — CLK: 25, MISO: 39, MOSI: 32, CS: 33 |
| Mode | Polled every 5 ms — no interrupt line used |
| Long-press threshold | 2000 ms |
| Calibration | Hardcoded coordinate mapping calibrated to the physical unit |

### GPS Module — u-blox NEO-6M (GY-GPS6MV2 breakout)

| Parameter | Value |
|---|---|
| UART pins | RX: 22, TX: 27 |
| Operating baud rate | 57600 bps (negotiated from 9600 default on every boot) |
| Update rate | 5 Hz — one complete fix every 200 ms |
| Active sentences | GGA and RMC only — all others disabled |
| Antenna | Internal patch with hardwired LDO bias on GY-GPS6MV2 |
| Dynamic model | Automotive |
| Static hold threshold | 40 cm/s |
| SBAS | Enabled (WAAS in North America) |
| Min satellite elevation | 10 degrees |
| Config persistence | Volatile — reapplied from firmware on every boot |

### Storage — ESP32 Internal Flash (NVS)

| Key | Type | Description |
|---|---|---|
| odo | double | Total odometer in miles |
| utc_offset | char | UTC time offset, -14 to +14 hours |
| brightness | uint8 | Backlight PWM level (64 / 128 / 192 / 255) |
| theme | uint8 | Active colour theme index (0–16) |
| font_idx | uint8 | Active numeric font index (0–7) |

All keys reside under the namespace "rally". NVS write-levelling protects against flash corruption. The odometer is saved at 1-mile intervals and immediately on manual or factory reset.

---

## 2. System Architecture

```
                 +------------------------------+
                 |    ESP32-2432S028R (CYD)     |
                 |                              |
 GPS (NEO-6M) -- | UART2  RX:22  TX:27         |
 57600 baud      |  Core 0: GPS task           |---- mutex --+
 5 Hz position   |    Parse RMC + GGA          |             |
                 |    Motion gates             |             v
                 |    Accumulate distance      | +-----------+------+
                 |                              | | RallyData struct  |
                 |  Core 1: Display + Touch    | |  totalTrip        |
                 |    Update screen @ 100 ms   | |  intervalTrip     |
                 |    Read touch @ 5 ms        | |  currentSpeed     |
                 |    Run animations           | |  avgSpeed / max   |
 ILI9341 TFT  -- | SPI  55 MHz  GPIO 13,14,15 | |  hdop / sats      |
 320x240         |  Backlight PWM  GPIO 21     | |  GPS time         |
                 |                              | |  reject counters  |
 XPT2046 Touch-- | VSPI  CLK:25 MISO:39        | +-------------------+
 Resistive       |       MOSI:32 CS:33         |
                 |                              |
 Internal Flash--| NVS  namespace: rally       |
                 +------------------------------+
```

---

## 3. Software Libraries

| Library | Version | License | Role |
|---|---|---|---|
| LVGL | 9.2.2 | MIT | UI framework — screens, widgets, animations |
| TFT_eSPI (Bodmer) | 2.5.x | MIT | ILI9341 display driver with DMA SPI |
| XPT2046_Touchscreen | 1.4 | MIT | Resistive touch controller |
| NeoGPS (SlashDevin) | 4.x | GPL-3.0 | GPS parsing — atomic RMC+GGA pairs |
| Arduino Preferences | built-in | LGPL-2.1 | NVS key-value persistence |
| FreeRTOS | built-in | MIT | Dual-core task management and mutex |
| esp_task_wdt | built-in | Apache-2.0 | Hardware watchdog (5 s timeout, both cores) |

The firmware is open-source and distributed under the GNU General Public License v3.0, inherited from the NeoGPS dependency.

---

*End of Altura Rally Computer Hardware Reference — v1.0*

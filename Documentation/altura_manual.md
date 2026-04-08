# Altura Rally Computer
## User Manual — v1.0

**Authors:** Jason Hack · Eli Goethel

---

## Table of Contents

1. [Introduction](#1-introduction)
2. [System Overview](#2-system-overview)
3. [First Boot & GPS Acquisition](#3-first-boot--gps-acquisition)
4. [Core Concepts](#4-core-concepts)
   - 4.1 [Pending / Confirm Pattern](#41-pending--confirm-pattern)
   - 4.2 [Freeze Display (FRZ)](#42-freeze-display-frz)
   - 4.3 [Odometer System](#43-odometer-system)
   - 4.4 [Speed View Cycling](#44-speed-view-cycling)
   - 4.5 [Auto-Return](#45-auto-return)
5. [Navigation Model](#5-navigation-model)
6. [Screen Guide](#6-screen-guide)
   - 6.1 [Boot Splash Screen](#61-boot-splash-screen)
   - 6.2 [Main Screen](#62-main-screen)
   - 6.3 [Settings Menu](#63-settings-menu)
   - 6.4 [GPS Diagnostics Screen](#64-gps-diagnostics-screen)
   - 6.5 [Clock Screen](#65-clock-screen)
   - 6.6 [Theme Screen](#66-theme-screen)
   - 6.7 [Font Screen](#67-font-screen)
   - 6.8 [Factory Reset Screen](#68-factory-reset-screen)
7. [GPS Signal Indicators](#7-gps-signal-indicators)
8. [GPS Quality & Accuracy](#8-gps-quality--accuracy)
9. [Settings & Saved Data](#9-settings--saved-data)
10. [Troubleshooting](#10-troubleshooting)

---

## 1. Introduction

The **Altura Rally Computer** is a GPS odometer and speedometer built for competitive stage rally use. It measures distance and speed using a u-blox NEO-6M GPS module — no wheel sensor required. The device provides precise distance measurement, live speed readout, GPS-synchronized time display, and detailed signal diagnostics on a compact 320×240 touchscreen.

| Feature | Detail |
|---|---|
| GPS module | u-blox NEO-6M, 5 Hz update rate |
| Distance units | Miles |
| Display | 320×240 touchscreen — fully touch-driven |
| Saved settings | Survive power loss automatically |
| Visual themes | 17 selectable colour schemes |
| Display fonts | 8 selectable numeric fonts |

> **For competitive use:** Keep the device powered continuously during events. Cold GPS starts can take up to three minutes. A warm start locks in under 30 seconds. Avoid power-cycling between recce and stages.

---

## 2. System Overview

The Altura runs two parallel processes that share data through a protected handoff.

| Process | Task | Responsibilities |
|---|---|---|
| GPS | Background | Receives GPS data, applies motion filters, accumulates distance |
| Display | Foreground | Updates screen every 100 ms, handles touch, runs animations |

### Distance Accumulation — Five Protection Layers

A GPS reading only contributes to your distance total if it passes all five checks below.

| Check | Threshold | Protects Against |
|---|---|---|
| Valid location fix | GPS must report a confirmed position | Phantom readings during satellite search |
| Blackout recovery | Previous reading also had a valid fix | Distance jumps when signal returns |
| Minimum speed | Above 1.9 mph (approx. 3 km/h) | Stationary GPS noise accumulation |
| Speed change limit | Under 124 mph change between readings | Sudden GPS speed glitches |
| Per-reading distance cap | Under 1.0 mile per GPS update | Coordinate corruption jumps |

---

## 3. First Boot & GPS Acquisition

On power-up, the Altura shows its boot splash for approximately 3.5 seconds, then transitions to the main screen. Watch the three indicator lights in the top-left.

| Indicator | Colour / Pattern | Meaning |
|---|---|---|
| GPS | Grey, steady | No fix — fewer than 3 satellites |
| GPS | Green, blinking | Acquiring — satellites visible, accuracy improving |
| GPS | Green, steady | Locked — ready to count distance |
| SATS | Grey, steady | Fewer than 3 satellites |
| SATS | Amber, blinking | 2D fix — exactly 3 satellites |
| SATS | Green, steady | 3D fix — 4 or more satellites |
| HDOP | Grey, steady | No fix |
| HDOP | Green, steady | Good signal quality (HDOP under 2.5) |
| HDOP | Amber, blinking | Reduced quality (HDOP 2.5–3.5) |
| HDOP | Red, fast blinking | Poor signal quality (HDOP over 3.5) |

> **Before a stage:** Wait for GPS steady green before the start line.

> **Cold start:** If the device has been off for several hours, acquisition can take 1–3 minutes.

---

## 4. Core Concepts

### 4.1 Pending / Confirm Pattern

The Clock, Theme, and Font screens use a two-step model. Nothing is saved unless you tap CONFIRM.

| Step | Action | What Happens |
|---|---|---|
| 1 | Open screen | Current saved value loaded as starting point |
| 2 | Adjust | Display updates immediately — live preview |
| 3a | Tap CONFIRM | Change saved and applied permanently |
| 3b | Tap BACK | Change discarded, saved value unchanged |

### 4.2 Freeze Display (FRZ)

The FRZ button pauses the readouts. **Distance continues accumulating in the background.**

| Behaviour | Detail |
|---|---|
| Button appearance | Turns red and blinks every half-second when active |
| Button label | Changes from FRZ to RES (resume) while frozen |
| Auto-release | Automatically releases after 60 seconds |
| Background counting | GPS distance accumulation continues normally |
| To un-freeze | Tap the red RES button, or wait 60 seconds |

> **In a stage:** Use FRZ to hold a reference reading while discussing a junction.

### 4.3 Odometer System

| Counter | Label | Saved? | Reset With | Notes |
|---|---|---|---|---|
| Total distance | TOTAL | Yes | Long-press CLR ODO (~1.8 s) | Also resets avg and peak speed |
| Trip distance | TRIP | No | Long-press CLR INT (~1.8 s) | Use for stage-by-stage counting |

Both CLR buttons require a sustained hold of about 1.8 seconds. Releasing early cancels.

### 4.4 Speed View Cycling

Tap the large speed display area to cycle through three views.

| Label | Shows |
|---|---|
| mph | Current GPS speed (default) |
| avg | Average speed since first GPS fix |
| max | Highest speed this session |

### 4.5 Auto-Return

If no touch input is detected for 30 seconds on any settings screen, the device automatically returns to the main screen.

---

## 5. Navigation Model

| From | Action | Direction | To |
|---|---|---|---|
| Main Screen | Tap MENU | Slide left | Settings Menu |
| Settings Menu | Tap BACK | Slide right | Main Screen |
| Settings Menu | Tap GPS tile | Slide left | GPS Diagnostics Screen |
| Settings Menu | Tap CLOCK tile | Slide left | Clock Screen |
| Settings Menu | Tap THEME tile | Slide left | Theme Screen |
| Settings Menu | Tap FONT tile | Slide left | Font Screen |
| Settings Menu | Tap RESET tile | Slide left | Factory Reset Screen |
| Any settings screen | Tap BACK | Slide right | Settings Menu |
| Clock / Theme / Font | Tap CONFIRM | Slide right | Settings Menu (saved) |
| Any screen | 30 s no activity | Fade | Main Screen |

---

## 6. Screen Guide

### 6.1 Boot Splash Screen

Shown for approximately 3.5 seconds on power-up. Displays the Altura logo and firmware version. GPS begins acquiring during this screen. Transitions automatically to the Main Screen.

### 6.2 Main Screen

- **GPS / SATS indicators:** Coloured dots showing fix status
- **Clock:** GPS time adjusted to your UTC offset
- **MENU:** Opens the Settings Menu
- **FRZ:** Freezes the readouts (distance still accumulates)
- **HDOP:** Real-time GPS signal quality indicator
- **Speed (large):** Tap to cycle current / average / max
- **TOTAL and TRIP:** Distance counters in miles
- **CLR ODO / CLR INT:** Hold ~1.8 s to reset each counter

### 6.3 Settings Menu

Six tiles in a 3×2 grid. BRIGHT cycles brightness immediately. GPS, CLOCK, THEME, FONT, and RESET each open their respective screens. The RESET tile is always dark red.

### 6.4 GPS Diagnostics Screen

Live diagnostic table with 9 rows: Latitude, Longitude, Altitude, HDOP, Fix Quality, Satellites, Rejected Steps, Rejected Sanity, and Blackouts. HDOP row highlights based on signal quality. Scroll vertically to view all rows.

### 6.5 Clock Screen

Sets your local UTC offset (-14 to +14 hours). Uses the Pending / Confirm pattern. The clock previews the new time immediately. Factory default: UTC-5 (Eastern Standard Time).

### 6.6 Theme Screen

17 colour themes as a scrollable list. Each row shows five colour swatches. Tap a row to stage it, then tap CONFIRM to apply and save.

### 6.7 Font Screen

8 numeric fonts as a scrollable list. Each row previews that font with sample numbers. Applies to speed, total, trip, and clock readouts only.

### 6.8 Factory Reset Screen

Tap CANCEL to return safely. Tap RESET (dark red) to permanently erase all saved data and return to factory defaults. **This action cannot be undone.**

---

## 7. GPS Signal Indicators

Three round indicator lights appear in the top-left of the main screen.

### GPS Indicator — Overall Fix Quality

| Colour | Pattern | Condition | Meaning |
|---|---|---|---|
| Grey | Steady | Fewer than 3 satellites | No fix |
| Green | Blinking (0.5 s) | 3+ satellites, HDOP above 2.5 | Acquiring |
| Green | Steady | 3+ satellites, HDOP 2.5 or below | Locked |

### SATS Indicator — Fix Type

| Colour | Pattern | Condition | Meaning |
|---|---|---|---|
| Grey | Steady | Fewer than 3 satellites | No fix |
| Amber | Blinking (0.8 s) | Exactly 3 satellites | 2D fix |
| Green | Steady | 4 or more satellites | 3D fix |

### HDOP Indicator — Horizontal Accuracy

| Colour | Pattern | Threshold | Meaning |
|---|---|---|---|
| Grey | Steady | No fix | No fix |
| Green | Steady | HDOP 2.5 or below | Good |
| Amber | Blinking (0.8 s) | HDOP 2.5–3.5 | Reduced |
| Red | Fast blink (0.25 s) | HDOP above 3.5 | Poor |

---

## 8. GPS Quality & Accuracy

### Fix Quality Labels

| Label | HDOP Range | Description |
|---|---|---|
| EXCL | Below 1.5 | Excellent |
| GOOD | 1.5–2.5 | Good — normal operating range |
| POOR | Above 2.5 | Degraded |
| NO FIX | n/a | Fewer than 3 satellites |

### Terrain Accuracy

| Terrain | Typical Accuracy |
|---|---|
| Open stages / highway | ~0.1% error |
| Dense canopy stages | 4–8% undercount possible |

### GPS Module Settings (applied each startup)

| Setting | Value |
|---|---|
| Update rate | 5 Hz |
| Active sentences | Position and speed only |
| Motion model | Automotive |
| Stationary filter | Active |
| SBAS corrections | Enabled (WAAS) |
| Horizon mask | 10 degrees |

---

## 9. Settings & Saved Data

| Setting | Default | Notes |
|---|---|---|
| Total odometer | 0.00 mi | Saved every mile and on every manual reset |
| UTC time offset | UTC-5 | Range: -14 to +14 hours |
| Screen brightness | 100% | 4 levels: 25% / 50% / 75% / 100% |
| Visual theme | Altura | 17 themes available |
| Display font | Montserrat | 8 fonts available |

> **Odometer saves:** Written to storage every mile, and immediately on CLR ODO or factory reset. Up to one mile of total distance could be lost on a sudden power cut. The trip counter is not saved across power cycles.

---

## 10. Troubleshooting

**All GPS indicators are grey after power-up.**
Normal for 30–90 seconds (warm) or up to 3 minutes (cold). Move to clear sky if acquisition exceeds 5 minutes.

**Distance counts while stationary.**
A minimum speed of ~1.9 mph is required. The stationary filter and speed gate together keep this negligible.

**TRIP correct but TOTAL wrong.**
CLR ODO and CLR INT are independent. Both require a ~1.8 s hold.

**Accidentally opened a settings screen mid-stage.**
Tap BACK. Nothing changes unless you tap CONFIRM.

**Speed shows "avg" or "max".**
Tap the speed area again until the label reads "mph".

**Device returned to main screen on its own.**
30-second inactivity auto-return. Intentional.

**FRZ will not turn off.**
Tap the red RES button. Auto-releases after 60 seconds.

**Clock shows the wrong time.**
Open Settings > Clock, adjust UTC offset, tap CONFIRM.

**Odometer shows a value after factory reset.**
Confirm the RESET COMPLETE message appeared. Retry the reset if interrupted.

**Rej. Sanity is climbing on the GPS Diagnostics Screen.**
Speed-change filter triggering — usually heavy canopy or blocked antenna. Odometer is protected.

---

*End of Altura Rally Computer User Manual — v1.0*

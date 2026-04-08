# Altura Rally Computer
## License Agreement — v1.0

**Authors:** Jason Hack · Eli Goethel

---

> **PLEASE READ THIS AGREEMENT CAREFULLY BEFORE POWERING ON OR USING THE ALTURA RALLY COMPUTER. BY ACTIVATING, INSTALLING, OR OTHERWISE USING THIS DEVICE, YOU ("USER") AGREE TO BE LEGALLY BOUND BY ALL TERMS BELOW. IF YOU DO NOT AGREE, DO NOT POWER ON THE DEVICE AND RETURN IT IMMEDIATELY IN ITS ORIGINAL UNOPENED PACKAGING.**

---

## 1. Purpose and Intended Use

The Altura Rally Computer ("the Device") is a GNSS-based odometer and navigation interface developed specifically for motorsport and competition environments.

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

*End of Altura Rally Computer License Agreement — v1.0*

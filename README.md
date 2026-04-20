
**IEEE OPS Capstone Project**  
Two-player wireless racing game using 16x2 LCD, joystick, and nRF24L01 modules.

Players race across scrolling maps while avoiding trees and hitting apples (look like dimonds, which pushes players back). First to complete all levels wins.

## Team Members: Johanna H., Ctaherine K., Diane C.

## Hardware (per player)
- Arduino Nano
- 16x2 LCD (parallel, 16 pins)
- KY-023 Joystick, restart button on pin 6
- nRF24L01+ wireless module


## Pinout (Important)
**LCD:**
- RS → A2
- E → A3
- D4 → 5
- D5 → 4
- D6 → 3
- D7 → 2
- VSS, RW, K → GND
- VDD, A → 5V
- VO → GND (or potentiometer for contrast)

**Joystick:**
- VCC → 5V
- GND → GND
- VRx → A0
- VRy → A1
- SW → (used internally)

**nRF24L01:**
- VCC → 3.3V
- GND → GND
- CE → 7
- CSN → 8
- SCK → 13
- MOSI → 11
- MISO → 12

## How to Use
1. Upload the same `LCDRacer.ino` to both boards.
2. On the **first board**, keep `bool isPlayerOne = true;`
3. On the **second board**, change it to `bool isPlayerOne = false;`
4. Power both boards — they will connect automatically.
5. Use joystick to move (left/right/up/down).
6. Reach the right side to advance levels.
7. Avoid trees (`#`), hitting apples pushes you back.

## Game Features
- 3 levels with increasing difficulty
- Real-time wireless synchronization
- Collision with trees (blocked)
- Apples act as "bumps" (push back)
- Win/Lose screen with restart button (pin 6)

---

Made for IEEE OPS Capstone 2026.

## Software Portion of Project
### Option 1: Arduino IDE (Simplest)
1. Clone or download the repo
2. Open the folder `code/OPSCapstone/`
3. Open `OPSCapstone.ino` in Arduino IDE
4. Install libraries: `Adafruit SSD1306`, `Adafruit GFX`, `RF24`
5. Select Arduino Nano board and upload (same sketch on both boards)

### Option 2: VS Code + PlatformIO (Recommended for teamwork)
1. Install VS Code + **PlatformIO IDE** extension
2. Open the entire repo folder in VS Code
3. PlatformIO will detect the project automatically
4. Click the orange alien icon (PlatformIO) → Build / Upload

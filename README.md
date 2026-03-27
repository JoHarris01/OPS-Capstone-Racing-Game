# OPS-Capstone-Racing-Game
We will create some sort of racing game where players are racing each other until the end. A player can pick up certain items that can negatively effect the opponent and power-ups to boost themselves. First player to cross the finish line on Level 2 wins. Both screens show “WINNER!” or "LOSER!" with victory chiptune + flashing animation.


# OPS Capstone Racing Game

Wireless head-to-head racing game for IEEE OPS capstone.  
Two Arduino Nanos with SSD1306 OLEDs, joysticks, and NRF24L01 modules.  
Players race on synced boards & maps and can sabotage each other (screen flash + pushback).

## Features
- Real-time wireless position syncing
- 2 levels with different track maps
- Power-ups/sabotage system
- Retro-style graphics and sounds (via piezo buzzer)

## Hardware (per player)
- Arduino Nano
- 0.96" SSD1306 OLED (I2C)
- KY-023 Joystick
- NRF24L01+ wireless module
- Passive piezo buzzer (optional extra button)

## Software portion of the project
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

## Folder Structure
- `code/OPSCapstone/` → Main Arduino sketch (works with both IDEs-- might break up parts)
- `hardware/` → Wiring diagrams and pinouts
- `images/` → Screenshots of gameplay
- `docs/` → Reports or presentation slides (if any-- optional)


## Team Responsibilities (UNOFFICIAL)
- OLED rendering & graphics + communication: [Johanna H.]
- Game logic & maps: [Catherine K.]
- Hardware assembly & testing: [Diane C.]

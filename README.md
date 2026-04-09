# OPS-Capstone-Racing-Game
We will create some sort of racing game where players are racing each other until the end. A player can pick up certain items that can negatively effect the opponent and power-ups to boost themselves. First player to cross the finish line on Level 2 wins. Both screens show “WINNER!” or "LOSER!" with victory chiptune + flashing animation.

#Cardboard/Decor might be used to cover extraneous wires, might need to use male/female jumpers cables to allow them to stick out of the cardboard

# OPS Capstone Racing Game
Wireless head-to-head racing game for IEEE OPS capstone.  
Two Arduino Nanos with SSD1306 OLEDs, joysticks, and NRF24L01 modules.  
Players race on synced boards & maps and can sabotage each other (screen flash + pushback).

## Features
- Real-time wireless board syncing
- 1 level with different track maps
- Power-ups/sabotage system
- Retro-style graphics and sounds (via piezo buzzer-- Johanna can help with this as well)

## Hardware (per player)
- Arduino Nano
- LCD Display 
- KY-023 Joystick
- NRF24L01+ wireless module
- Passive piezo buzzer (optional extra button)

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

## Folder Structure (UNOFFICIAL)
- `code/OPSCapstone/` → Main Arduino sketch (works with both IDEs-- might break up parts)
- `hardware/` → Wiring diagrams and pinouts
- `images/` → Screenshots of gameplay
- `docs/` → Reports or presentation slides (if any-- optional)


## Team Responsibilities (UNOFFICIAL)
- OLED rendering & graphics + communication: [Johanna H.]
- Game logic & maps: [Catherine K.]
- Hardware assembly & testing: [Diane C.]

#The LCD Pinout on circuit: 
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * A connected to power
 * K connected to ground 

// Pin definitions and shared constants forthe game
#pragma once

// ============== OLED ==============
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64

// ============== Joystick ==============
#define JOY_X     A0
#define JOY_Y     A1
#define FIRE_BTN  2     // Joystick button or extra button

// ============== NRF24L01 ==============
#define CE_PIN    7
#define CSN_PIN   8

// ============== Game Settings ==============
#define MAX_PROGRESS      100     // Track length (0 to 100)
#define SABOTAGE_DURATION 2000    // milliseconds (2 seconds)
#define NUM_LANES         4

// ============== Packet Structure (for wireless) ==============
struct GamePacket {
  int progress;           // Current position (0-100)
  int lane;               // Current lane (0-3)
  bool sabotageFired;     // Did this player just fire sabotage?
  int level;              // Current level (1 or 2)
  bool isValid;           // Simple checksum flag
};

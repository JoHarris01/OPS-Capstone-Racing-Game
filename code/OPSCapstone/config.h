// config.h
#pragma once

//LCD
#define LCD_ADDRESS   0x27        // Change to 0x3F if needed
#define LCD_COLUMNS   16
#define LCD_ROWS      2

//Joystick
#define JOY_X     A0
#define JOY_Y     A1
#define FIRE_BTN  2

//nRF24L01
#define CE_PIN    7
#define CSN_PIN   8

//Game Settings
#define MAX_PROGRESS   100
#define SABOTAGE_DURATION 1800
#define NUM_LANES      3

struct GamePacket {
  int progress;
  int lane;
  bool sabotageFired;
  int level;
  bool isValid;
};

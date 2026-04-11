// LCDRacer.ino
// Vertical LCD Racing Game with Sabotage - IEEE OPS Capstone

// LCDRacer.ino - Main File

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RF24.h>
#include "config.h"
#include "sprites.h"
#include "comms.h"
#include "game_logic.h"
#include "mechanics.h"
#include "maps.h"         

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
RF24 radio(CE_PIN, CSN_PIN);

GamePacket txPacket;
GamePacket rxPacket;

// Globals
int playerProgress = 0;
int playerLane = 1;
int currentLevel = 1;
bool gameRunning = false;
bool sabotaged = false;
unsigned long sabotageEndTime = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, carTop);
  lcd.createChar(1, carBottom);

  lcd.setCursor(2, 0);
  lcd.print("PACKET DASH");
  lcd.setCursor(4, 1);
  lcd.print("DUEL");
  delay(2000);
  lcd.clear();

  initRadio();
  initGameLogic();
  initMechanics();

  pinMode(FIRE_BTN, INPUT_PULLUP);

  selectedMap = 0;           
  offset = 0;
  loadSelectedMap();         
  gameRunning = true;
}

void loop() {
  if (!gameRunning) {
    showWinnerScreen();
    return;
  }

  updateSabotage();
  updateMovement();
  updateMechanics();

  if (checkForIncomingData()) {
    if (rxPacket.sabotageFired) triggerSabotage();
  }

  drawGameScreen();   // Now uses her maps

  if (digitalRead(FIRE_BTN) == LOW) {
    sendSabotage();
    delay(250);
  }

  if (checkFinishLine()) {
    nextRound();
  }

  offset++;   // Scroll the map
  delay(100);
}

// 
void drawGameScreen() {
  lcd.clear();

  // Top row = scrolling map (her map data)
  lcd.setCursor(0, 0);
  for (int i = 0; i < 16; i++) {
    int idx = (offset + i) % 16;
    lcd.print(getMapTile(0, idx));
  }

  // Bottom row = player info + car
  lcd.setCursor(0, 1);
  lcd.print("Lane:");
  lcd.print(playerLane);

  lcd.setCursor(8, 1);
  lcd.write(byte(0));
  lcd.write(byte(1));

  if (sabotaged) {
    lcd.setCursor(11, 1);
    lcd.print("SAB!");
  }
}

void showWinnerScreen() {
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print(playerProgress >= MAX_PROGRESS ? " YOU WIN! " : " YOU LOSE ");
  lcd.setCursor(2, 1);
  lcd.print("Game Over");
  delay(4000);
}

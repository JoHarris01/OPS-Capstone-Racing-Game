// Main file for Packet Dash Duel - Wireless OLED Racing Game
// LCDRacer.ino
// Vertical LCD Racing Game with Sabotage - IEEE OPS Capstone

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RF24.h>
#include "config.h"
#include "sprites.h"
#include "comms.h"
#include "game_logic.h"
#include "mechanics.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
RF24 radio(CE_PIN, CSN_PIN);

GamePacket txPacket;
GamePacket rxPacket;

void setup() {
  Serial.begin(9600);
  Serial.println("=== LCD Packet Dash Duel Starting ===");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("PACKET DASH");
  lcd.setCursor(2, 1);
  lcd.print("DUEL STARTING");
  delay(2500);
  lcd.clear();

  initRadio();
  initGameLogic();
  initMechanics();

  pinMode(FIRE_BTN, INPUT_PULLUP);

  Serial.println("Setup complete!");
}

void loop() {
  if (!gameRunning) {
    showWinnerScreen();
    return;
  }

  updateSabotage();
  updateMovement();           // Teammate A
  updateMechanics();          // Teammate B

  // Wireless communication
  if (checkForIncomingData()) {
    if (rxPacket.sabotageFired) triggerSabotage();
  }

  drawGameScreen();           // Your responsibility - LCD drawing

  // Fire sabotage
  if (digitalRead(FIRE_BTN) == LOW) {
    sendSabotage();
    delay(300);
  }

  // Check if round is finished
  if (checkFinishLine()) {
    nextRound();
  }

  delay(80);
}

// ==================== YOUR PART: LCD DISPLAY ====================
void drawGameScreen() {
  lcd.clear();

  // Top row - Progress & Level
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(currentLevel);
  lcd.print(" P:");
  lcd.print(playerProgress);

  // Bottom row - Lane + Status
  lcd.setCursor(0, 1);
  lcd.print("Lane:");
  lcd.print(playerLane);

  if (sabotaged) {
    lcd.print(" SABOTAGED!");
  } else {
    lcd.print(" OK");
  }
}

// Show winner / loser at the end of the game
void showWinnerScreen() {
  lcd.clear();
  lcd.setCursor(1, 0);
  if (playerProgress >= MAX_PROGRESS) {
    lcd.print("YOU WIN!");
  } else {
    lcd.print("YOU LOSE");
  }
  lcd.setCursor(0, 1);
  lcd.print("Round over");
  delay(4000);
}

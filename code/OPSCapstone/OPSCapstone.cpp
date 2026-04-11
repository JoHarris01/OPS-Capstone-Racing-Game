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

// Global variables (used by all files)
int playerProgress = 0;
int playerLane = 1;
int currentLevel = 1;
int roundNumber = 1;
bool gameRunning = false;
int score = 0;
bool sabotaged = false;
unsigned long sabotageEndTime = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== LCD Packet Dash Duel Starting ===");

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Create custom characters
  lcd.createChar(0, carTop);
  lcd.createChar(1, carBottom);
  lcd.createChar(2, orb);

  lcd.setCursor(3, 0);
  lcd.print("PACKET DASH");
  lcd.setCursor(4, 1);
  lcd.print("DUEL");
  delay(2500);
  lcd.clear();

  initRadio();
  initGameLogic();
  initMechanics();

  pinMode(FIRE_BTN, INPUT_PULLUP);

  gameRunning = true;
  Serial.println("Setup complete - Game Ready!");
}

void loop() {
  if (!gameRunning) {
    showWinnerScreen();
    return;
  }

  updateSabotage();
  updateMovement();        
  updateMechanics();       

  // Wireless
  if (checkForIncomingData()) {
    if (rxPacket.sabotageFired) triggerSabotage();
  }

  drawGameScreen();        
  // Fire sabotage with joystick button
  if (digitalRead(FIRE_BTN) == LOW) {
    sendSabotage();
    delay(250);
  }

  // Check if round is finished
  if (checkFinishLine()) {
    nextRound();
  }

  delay(90);
}

//YOUR PART: LCD DISPLAY
void drawGameScreen() {
  lcd.clear();

  // Top row: Level and Progress
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(currentLevel);
  lcd.print(" P:");
  lcd.print(playerProgress);

  // Bottom row: Lane + Car + Status
  lcd.setCursor(0, 1);
  lcd.print("Lane:");
  lcd.print(playerLane);

  // Show car using custom characters
  lcd.setCursor(9, 1);
  lcd.write(byte(0));   // top half of sprite
  lcd.write(byte(1));   // bottom half of sprite

  if (sabotaged) {
    lcd.setCursor(12, 1);
    lcd.print("SAB!");
  } else {
    lcd.setCursor(12, 1);
    lcd.print(" OK");
  }
}

// Show winner or loser at the end of the game
void showWinnerScreen() {
  lcd.clear();
  lcd.setCursor(2, 0);
  if (playerProgress >= MAX_PROGRESS) {
    lcd.print("YOU WIN!");
  } else {
    lcd.print("YOU LOSE");
  }
  lcd.setCursor(0, 1);
  lcd.print("Game Over");
  delay(5000);
  lcd.clear();
}

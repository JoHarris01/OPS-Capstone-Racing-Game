// LCDRacer.ino - Complete Main File with Point System
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RF24.h>
#include "config.h"
#include "sprites.h"
#include "comms.h"
#include "game_logic.h"
#include "mechanics.h"
#include "maps.h"

bool isPlayerA = true; 

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);
RF24 radio(CE_PIN, CSN_PIN);

GamePacket txPacket;
GamePacket rxPacket;

// Globals
int playerProgress = 0;
int playerLane = 1;
int currentLevel = 1;
int roundNumber = 1;
bool gameRunning = false;
bool sabotaged = false;
unsigned long sabotageEndTime = 0;

// Point System
int playerScore = 0;
int opponentScore = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.createChar(0, carTop);
  lcd.createChar(1, carBottom);
  lcd.createChar(2, orb);

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
  playerScore = 0;
  opponentScore = 0;

  if (IS_PLAYER_A) {
  radio.openWritingPipe(address1);
  radio.openReadingPipe(1, address2);
} else {
  radio.openWritingPipe(address2);
  radio.openReadingPipe(1, address1);
}
}

void loop() {
  if (!gameRunning) {
    showWinnerScreen();
    return;
  }

  updateSabotage();
  updateMovement();        // From game_logic.h
  updateMechanics();       // From mechanics.h

  // Wireless
  if (checkForIncomingData()) {
    if (rxPacket.sabotageFired) {
      triggerSabotage();
      opponentScore += 10;     // Opponent gains points for sabotaging you
    }
  }

  drawGameScreen();         // Your LCD + map display

  // Fire sabotage
  if (digitalRead(FIRE_BTN) == LOW) {
    sendSabotage();
    playerScore += 15;       // Bonus for successful sabotage
    delay(250);
  }

  // Progress points
  if (playerProgress % 8 == 0 && playerProgress > 0) {
    playerScore += 1;
  }

  if (checkFinishLine()) {
    playerScore += 50;       // Big bonus for finishing round
    nextRound();
  }

  offset++;
  delay(100);
}

// LCD Display with Score and Map
void drawGameScreen() {
  lcd.clear();

  // Top row: Level + Score
  lcd.setCursor(0, 0);
  lcd.print("L");
  lcd.print(currentLevel);
  lcd.print(" S:");
  lcd.print(playerScore);

  // Bottom row: Lane + Car + Status + Map tile
  lcd.setCursor(0, 1);
  lcd.print("Lane:");
  lcd.print(playerLane);

  lcd.setCursor(8, 1);
  lcd.write(byte(0));
  lcd.write(byte(1));

  if (sabotaged) {
    lcd.setCursor(11, 1);
    lcd.print(" SAB!");
  }
}

// Final Winner Screen
void showWinnerScreen() {
  lcd.clear();
  lcd.setCursor(1, 0);
  
  if (playerScore > opponentScore) {
    lcd.print(" YOU WIN!");
  } else if (opponentScore > playerScore) {
    lcd.print(" YOU LOSE ");
  } else {
    lcd.print("   TIE   ");
  }

  lcd.setCursor(0, 1);
  lcd.print("You:");
  lcd.print(playerScore);
  lcd.print(" Opp:");
  lcd.print(opponentScore);

  delay(5000);
}

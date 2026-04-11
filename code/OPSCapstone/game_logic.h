// Core game logic: movement, progress, levels, finish conditions

#pragma once
#include "config.h"

extern int playerProgress;
extern int playerLane;
extern int currentLevel;
extern bool gameRunning;
extern int roundNumber;

void initGameLogic() {
  playerProgress = 0;
  playerLane = 1;        // Start in middle lane (0-2)
  currentLevel = 1;
  roundNumber = 1;
  gameRunning = true;
}

// Read joystick and update player position
void updateMovement() {
  int x = analogRead(JOY_X);
  int y = analogRead(JOY_Y);

  // Horizontal movement (lanes)
  if (x < 300 && playerLane > 0) playerLane--;
  if (x > 700 && playerLane < NUM_LANES-1) playerLane++;

  // Vertical movement (progress - accelerate)
  if (y < 300) {
    playerProgress += 2;     // Moving forward
  } else if (y > 700) {
    playerProgress -= 1;     // Slow down / reverse a bit
  }

  // Keep in bounds
  if (playerProgress < 0) playerProgress = 0;
  if (playerProgress > MAX_PROGRESS) playerProgress = MAX_PROGRESS;
}

// Check if current round is finished
bool checkFinishLine() {
  return playerProgress >= MAX_PROGRESS;
}

// Move to next round or end game
void nextRound() {
  roundNumber++;
  if (roundNumber > 2) {
    gameRunning = false;     // Game over after 2 rounds
    Serial.println("Game Over - Showing winner screen");
  } else {
    currentLevel = roundNumber;
    playerProgress = 0;
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("ROUND");
    lcd.print(roundNumber);
    lcd.setCursor(4, 1);
    lcd.print("START!");
    delay(2000);
  }
}

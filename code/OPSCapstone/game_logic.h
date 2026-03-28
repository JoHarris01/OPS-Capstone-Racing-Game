// Core game logic - car movement, progress, levels

#pragma once
#include "config.h"

extern int playerProgress;
extern int playerLane;
extern int currentLevel;
extern bool gameRunning;

// Update player movement based on joystick
void updateMovement() {
  // TODO: Read joystick and update playerLane and playerProgress
  // This will be filled by someone
}

// Check if player reached the finish line
bool checkFinishLine() {
  return playerProgress >= MAX_PROGRESS;
}

// Switch to next level
void nextLevel() {
  currentLevel++;
  playerProgress = 0;        // Reset progress for new level
  Serial.print("Starting Level ");
  Serial.println(currentLevel);
}

// Initialize game variables
void initGameLogic() {
  playerProgress = 0;
  playerLane = 1;            // Start in middle lane
  currentLevel = 1;
  gameRunning = true;
}

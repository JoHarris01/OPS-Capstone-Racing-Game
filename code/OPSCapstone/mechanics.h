// mechanics.h
// Power-ups, sabotage, scoring, and point system

#pragma once
#include "config.h"

extern int playerScore;
extern int opponentScore;
extern bool sabotaged;
extern unsigned long sabotageEndTime;

void initMechanics() {
  playerScore = 0;
  opponentScore = 0;
  sabotaged = false;
}

// Add points for different actions
void addPoints(int points) {
  playerScore += points;
  Serial.print("Points added: +");
  Serial.println(points);
}

// Check and collect power-up
bool checkPowerUpCollection(int playerLane) {
  // This will be expanded with actual power-up position later
  if (random(0, 100) < 6) {        // Chance to collect
    addPoints(25);
    return true;
  }
  return false;
}

// When you successfully sabotage the opponent
void onSuccessfulSabotage() {
  addPoints(15);
}

// When you get sabotaged (penalty)
void triggerSabotage() {
  sabotaged = true;
  sabotageEndTime = millis() + SABOTAGE_DURATION;
  playerScore = max(0, playerScore - 10);   // Small penalty
  playerProgress = max(0, playerProgress - 15);
}

// Update sabotage timer
void updateSabotage() {
  if (sabotaged && millis() > sabotageEndTime) {
    sabotaged = false;
  }
}

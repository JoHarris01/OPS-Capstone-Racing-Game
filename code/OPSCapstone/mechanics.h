// mechanics.h
// Power-ups, sabotage, scoring, and game mechanics

#pragma once
#include "config.h"

extern int score;
extern bool sabotaged;
extern unsigned long sabotageEndTime;

void initMechanics() {
  score = 0;
  sabotaged = false;
}

void updateMechanics() {
  updateSabotage();
}

// Handle when player gets sabotaged
void triggerSabotage() {
  sabotaged = true;
  sabotageEndTime = millis() + SABOTAGE_DURATION;
  playerProgress = max(0, playerProgress - 15);   // Push back 15 units
  Serial.println("Sabotage received - pushed back!");
}

// Update sabotage timer
void updateSabotage() {
  if (sabotaged && millis() > sabotageEndTime) {
    sabotaged = false;
    Serial.println("Sabotage effect ended");
  }
}

// Simple power-up collection (to be expanded by teammate)
bool checkPowerUpCollection() {
  // Random chance for now - teammate can improve this
  if (random(0, 100) < 5) {   // 5% chance per loop
    score += 10;
    Serial.println("Power-up collected!");
    return true;
  }
  return false;
}

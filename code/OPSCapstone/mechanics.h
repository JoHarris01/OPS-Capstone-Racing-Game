// Power-ups, obstacles, sounds, and game mechanics

#pragma once
#include "config.h"

extern int score;
extern bool sabotaged;
extern unsigned long sabotageEndTime;

// Initialize mechanics
void initMechanics() {
  score = 0;
  sabotaged = false;
}

// Spawn glitch orb (power-up) at random position
void spawnOrb() {
  // TODO: Teammate B will implement random orb spawning
  Serial.println("Glitch Orb spawned!");
}

// Check if player collected an orb
bool checkOrbCollection(int playerX, int playerY) {
  // TODO: Collision detection with orb
  return false;
}

// Handle sabotage effect (called when opponent fires at you)
void triggerSabotage() {
  sabotaged = true;
  sabotageEndTime = millis() + SABOTAGE_DURATION;
  Serial.println("SABOTAGE HIT! Screen will flash...");
}

// Update sabotage timer
void updateSabotage() {
  if (sabotaged && millis() > sabotageEndTime) {
    sabotaged = false;
    Serial.println("Sabotage effect ended");
  }
}

// Play simple sound effects
void playSound(int type) {
  // type 0 = orb collected, 1 = sabotage, 2 = finish
  if (type == 0) {
    tone(8, 1200, 100);   // High beep for orb
  } else if (type == 1) {
    tone(8, 400, 300);    // Low nasty beep for sabotage
  } else if (type == 2) {
    tone(8, 1500, 200);
    delay(100);
    tone(8, 2000, 300);   // Victory sound
  }
}

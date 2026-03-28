// Main file for Packet Dash Duel - Wireless OLED Racing Game

#include <SPI.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "config.h"
#include "sprites.h"
#include "comms.h"
#include "game_logic.h"
#include "mechanics.h"

// Global objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
RF24 radio(CE_PIN, CSN_PIN);

GamePacket txPacket;
GamePacket rxPacket;

// Global variables
int playerProgress = 0;
int playerLane = 1;
int currentLevel = 1;
bool gameRunning = false;
int score = 0;
bool sabotaged = false;
unsigned long sabotageEndTime = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== Packet Dash Duel Starting ===");

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed to initialize!");
    while (1);
  }
  display.clearDisplay();
  display.display();

  // Initialize other systems
  initRadio();
  initGameLogic();
  initMechanics();

  pinMode(FIRE_BTN, INPUT_PULLUP);

  gameRunning = true;
  Serial.println("Setup complete - Ready to race!");
}

void loop() {
  if (!gameRunning) return;

  // Update sabotage effect
  updateSabotage();

  // Update player movement (Teammate A)
  updateMovement();

  // Check for incoming wireless data
  if (checkForIncomingData()) {
    // Update opponent position and check for sabotage
    if (rxPacket.sabotageFired) {
      triggerSabotage();
    }
  }

  // Draw everything on OLED (your part)
  drawGameScreen();

  // Fire sabotage when button pressed
  if (digitalRead(FIRE_BTN) == LOW) {
    sendSabotage();
    delay(300); // simple debounce
  }

  delay(50); // Small delay for stability
}

// ==================== OLED DRAWING ====================
// (This is your main area - you can expand this)
void drawGameScreen() {
  display.clearDisplay();

  // Draw basic track
  display.drawRect(20, 0, 88, 64, WHITE);        // Road border
  display.drawRect(35, 0, 58, 64, WHITE);        // Inner road

  // Draw player car at bottom
  display.drawBitmap(50 + (playerLane * 12), 48, carSprite, 8, 8, WHITE);

  // Draw sabotage effect
  if (sabotaged) {
    display.invertDisplay(true);
  } else {
    display.invertDisplay(false);
  }

  display.display();
}

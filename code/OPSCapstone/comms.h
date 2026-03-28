// Wireless communication using NRF24L01

#pragma once
#include <RF24.h>
#include "config.h"

extern RF24 radio;                    // Defined in main .ino
extern GamePacket txPacket;           // Transmit packet
extern GamePacket rxPacket;           // Receive packet

// Initialize wireless
void initRadio() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);      // Low power for breadboard
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(0xF0F0F0F0E1LL);    // Address for Player 1
  radio.openReadingPipe(1, 0xF0F0F0F0E2LL); // Address for Player 2
  radio.startListening();
  Serial.println("Radio initialized");
}

// Send current game state to the other player
void sendGameState(int progress, int lane, bool sabotageFired, int level) {
  txPacket.progress = progress;
  txPacket.lane = lane;
  txPacket.sabotageFired = sabotageFired;
  txPacket.level = level;
  txPacket.isValid = true;

  radio.stopListening();
  radio.write(&txPacket, sizeof(txPacket));
  radio.startListening();
}

// Check if we received data from the other player
bool checkForIncomingData() {
  if (radio.available()) {
    radio.read(&rxPacket, sizeof(rxPacket));
    return true;
  }
  return false;
}

// Trigger sabotage effect on the other player's screen
void sendSabotage() {
  txPacket.sabotageFired = true;
  radio.stopListening();
  radio.write(&txPacket, sizeof(txPacket));
  radio.startListening();
  Serial.println("Sabotage sent to opponent!");
}

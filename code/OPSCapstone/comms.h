
// Wireless communication using nRF24L01

#pragma once
#include <RF24.h>
#include "config.h"

extern RF24 radio;
extern GamePacket txPacket;
extern GamePacket rxPacket;

void initRadio() {
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_250KBPS);

  if (isPlayerA) {
    radio.openWritingPipe(0xF0F0F0F0E1LL);    // Player A writes to this address
    radio.openReadingPipe(1, 0xF0F0F0F0E2LL); // Player A listens to Player B
    Serial.println("I am Player A");
  } else {
    radio.openWritingPipe(0xF0F0F0F0E2LL);    // Player B writes to this address
    radio.openReadingPipe(1, 0xF0F0F0F0E1LL); // Player B listens to Player A
    Serial.println("I am Player B");
  }

  radio.startListening();
}

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

bool checkForIncomingData() {
  if (radio.available()) {
    radio.read(&rxPacket, sizeof(rxPacket));
    return true;
  }
  return false;
}

void sendSabotage() {
  txPacket.sabotageFired = true;
  radio.stopListening();
  radio.write(&txPacket, sizeof(txPacket));
  radio.startListening();
  Serial.println("Sabotage sent!");
}

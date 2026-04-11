
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
  radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.openReadingPipe(1, 0xF0F0F0F0E2LL);
  radio.startListening();
  Serial.println("Wireless ready");
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

// Bitmap sprites for OLED display (8x8 and 16x8)
#pragma once

// Player Car (8x8) - looks like a little racing packet
const unsigned char carSprite[] PROGMEM = {
  0b00011000,
  0b00111100,
  0b01111110,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00100100,
  0b01000010
};

// Opponent Ghost Car (smaller/faded look)
const unsigned char ghostCar[] PROGMEM = {
  0b00011000,
  0b00111100,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000,
  0b00000000,
  0b00000000
};

// Glitch Orb / Power-up (6x6 diamond)
const unsigned char orbSprite[] PROGMEM = {
  0b00011000,
  0b00111100,
  0b01111110,
  0b00111100,
  0b00011000,
  0b00000000
};

// Finish Line
const unsigned char finishLine[] PROGMEM = {
  0b11111111,
  0b00000000,
  0b11111111,
  0b00000000,
  0b11111111,
  0b00000000,
  0b11111111,
  0b00000000
};

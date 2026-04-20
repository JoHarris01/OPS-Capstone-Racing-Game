#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(A2, A3, 5, 4, 3, 2);
RF24 radio(7, 8);
//#define JOY_BTN   6

bool isPlayerOne = false; // SET TO false ON SECOND BOARD
const byte addrs[][6] = {"1Node", "2Node"};


struct Pack { int x; int y; int lvl; bool won; bool ready; };
Pack me = {0, 1, 1, false, false}, peer = {0, 1, 1, false, false};


int gameSpeed = 130;
bool gameOver = false;


byte p1Char[] = {0x4,0xE,0x4,0xE,0x4,0xA,0xA,0x0}, p2Char[] = {0x4,0xA,0x4,0xA,0x4,0xA,0xA,0x0};
byte tree[]   = {0x1F,0x15,0x1F,0x15,0x1F,0x15,0x1F,0x1F}, bump[] = {0x4,0xE,0x1F,0x1F,0x1F,0xE,0x4,0x0};


void setup() {
  pinMode(6, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.createChar(0, tree); lcd.createChar(1, bump);
  lcd.createChar(2, p1Char); lcd.createChar(3, p2Char);
 
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(2, 2);
 
  if(isPlayerOne) {
    radio.openWritingPipe(addrs[0]);
    radio.openReadingPipe(1, addrs[1]);
  } else {
    radio.openWritingPipe(addrs[1]);
    radio.openReadingPipe(1, addrs[0]);
  }
  radio.startListening();


  lcd.clear();
  lcd.print("CONNECTING...");
  me.ready = true;


  while (!peer.ready) {
    sendStatus();
    if (radio.available()) radio.read(&peer, sizeof(Pack));
    lcd.setCursor(0, 1);
    lcd.print("WAITING FOR P"); lcd.print(isPlayerOne ? "2" : "1");
    delay(200);
  }
 
  lcd.clear(); lcd.print("CONNECTED!"); delay(1000);
  showStart();
}


void loop() {
  // --- 1. GAME OVER STATE ---
  if (gameOver) {
    if (digitalRead(4) == LOW) {
      resetGame();
    }
    // If I'm NOT the winner, I keep listening to see if the other guy reset
    if (!me.won && radio.available()) {
      radio.read(&peer, sizeof(Pack));
      if (!peer.won && peer.lvl == 1) resetGame();
    }
    return;
  }


  // --- 2. RECEIVE DATA ---
  if (radio.available()) {
    radio.read(&peer, sizeof(Pack));
    if (peer.won && !me.won) { // Only trigger loss if I haven't won already
      gameOver = true;
      drawEnd(false);
      return;
    }
  }


  // --- 3. MOVEMENT & COLLISION ---
  int oldX = me.x, oldY = me.y;
  if(analogRead(A0)<300 && me.x>0) me.x--;
  if(analogRead(A0)>700 && me.x<15) me.x++;
  if(analogRead(A1)<300) me.y = 0;
  if(analogRead(A1)>700) me.y = 1;


  int hit = getMapObject(me.x, me.y, me.lvl);
  if(hit == 0) { me.x = oldX; me.y = oldY; }
  else if(hit == 1) { me.x = max(0, me.x-4); }


  // --- 4. WIN CHECK ---
  if(me.x >= 15) {
    if(me.lvl < 3) {
      me.lvl++; me.x = 0; gameSpeed -= 30; showStart();
    } else {
      me.won = true;
      gameOver = true;
      // Spam the win signal so peer catches it
      for(int i=0; i<15; i++) { sendStatus(); delay(5); }
      drawEnd(true);
      return;
    }
  }


  sendStatus();
  drawScene();
  delay(gameSpeed);
}


void drawEnd(bool win) {
  lcd.clear();
  if(win) {
    lcd.setCursor(4, 0); lcd.print("WINNER!");
    lcd.setCursor(0, 1); lcd.print("Click to Restart");
  } else {
    lcd.setCursor(5, 0); lcd.print("LOSER!");
    lcd.setCursor(0, 1); lcd.print("Click to Restart");
  }


  // --- BLOCKING LOOP: Waits for button click ---
  // Wait until button is pressed (LOW)
  while(digitalRead(6) == HIGH) {
    // If I won, keep telling the other person so they see LOSER screen
    if(win) { sendStatus(); delay(50); }
  }
  // Optional: Wait for button release
  while(digitalRead(6) == LOW);
  delay(100);
}


void sendStatus() {
  radio.stopListening();
  radio.write(&me, sizeof(Pack));
  radio.startListening();
}


void resetGame() {
  me.x = 0; me.y = 1; me.lvl = 1; me.won = false; me.ready = true;
  peer.x = 0; peer.y = 1; peer.lvl = 1; peer.won = false;
  gameSpeed = 130;
  gameOver = false;
  showStart();
}


// ... (getMapObject and drawScene remain exactly as you had them)


void drawScene() {
  lcd.clear();
  for(int c=0; c<16; c++) for(int r=0; r<2; r++) {
    int o = getMapObject(c, r, me.lvl);
    if(o != -1) { lcd.setCursor(c, r); lcd.write(byte(o)); }
  }
  lcd.setCursor(me.x, me.y); lcd.write(byte(2));
  if(peer.lvl == me.lvl) {
    lcd.setCursor(peer.x, peer.y); lcd.write(byte(3));
  }
}


int getMapObject(int x, int r, int l) {
  if (x <= 1 || x >= 15) return -1;
  int spc = (l == 1) ? 4 : (l == 2) ? 3 : 2;
  if (x % spc == 0) {
    int oR = ((x / spc) + l) % 2;
    if (r == oR) return (l == 3 || x % 2 != 0) ? 1 : 0;
  }
  return -1;
}


void showStart() {
  lcd.clear();
  lcd.setCursor(4,0); lcd.print("P"); lcd.print(isPlayerOne ? "1":"2");
  lcd.print(" LVL "); lcd.print(me.lvl);
  lcd.setCursor(0, 1); lcd.print("READY? RACE!"); delay(1500);
}

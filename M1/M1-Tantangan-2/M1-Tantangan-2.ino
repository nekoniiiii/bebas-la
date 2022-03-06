//I Made Wiratathya Putramas - 13320012

#define BAUD 500000

// Pin Standar kit ESCOPE 2020 ESP32
#define DO0 13
#define DO1 12
#define DO2 14
#define DO3 27
#define DO4 33

#define DI0 32
#define DI1 35
#define DI2 34
#define DI3 39
#define DI4 36

#define LED0 5
#define BT0 4
#define BT1 16
#define BT2 17

#define N_LED 3
bool d0, d2, b_pressed;

// definisi pin, taruh di array
int p_btn[N_LED] = {BT0, BT1, BT2};
int p_led[N_LED] = {DO0, DO1, DO2};

// state, pakai enum untuk memperjelas 
enum {DELAY, JALAN, SIAP_HENTI, HENTI, SIAP_JALAN};
int state = DELAY;

void stateDelay() {
  digitalWrite(DO0, HIGH);
  delay(120000);
  b_pressed = 0;
  state = JALAN;
}

void jalan() {
  digitalWrite(DO0, HIGH);
  if (b_pressed) {
    digitalWrite(DO0, LOW);
    state = SIAP_HENTI;
  }
}

void siapHenti(){
  for (int i=0; i<10; i++) {
    digitalWrite(DO1, HIGH);
    delay(500);
    digitalWrite(DO1, LOW);
    delay(500);
  }
  state = HENTI;
}

void berhenti() {
  digitalWrite(DO2, HIGH);
  delay(30000);
  digitalWrite(DO2, LOW);
  state = SIAP_JALAN;
}

void siapJalan() {
  for (int i =0; i<10; i++) {
    digitalWrite(DO2,HIGH);
    delay(500);
    digitalWrite(DO2,LOW);
    delay(500);
  }
  state = DELAY;
}

void setup() {
  Serial.begin(BAUD);
  // Siapkan mode I/O
  for (int i=0; i<N_LED; i++) {
    pinMode(p_led[i], OUTPUT);
    pinMode(p_btn[i], INPUT_PULLUP);
  }
}

void loop() {
  // baca semua input
  // tombol tengah tidak berfungsi
  d0 = !digitalRead(BT0);
  d2 = !digitalRead(BT2);
  b_pressed = d0 || d2;

  // Aksi berdasarkan state
  switch(state) {
    case DELAY : stateDelay(); break;
    case JALAN : jalan(); break;
    case SIAP_HENTI : siapHenti(); break;
    case HENTI : berhenti(); break;
    case SIAP_JALAN : siapJalan(); break;     
  }
}

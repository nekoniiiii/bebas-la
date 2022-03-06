/* Program : Running LED
 * Contoh running LED memakai FSA
 * Tombol Kiri: run ke kiri
 * Tombol Tengah: stop
 * Tombol Kanan: run ke kanan
 * (c) Eko M. Budi, 2022
 */

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

// data
// menggunakan array untuk permudah I/O
#define N_LED 3
byte d_in;
byte d_out=1;

// definisi pin, taruh di array
int p_btn[N_LED] = {BT0, BT1, BT2};
int p_led[N_LED] = {DO0, DO1, DO2};

// state, pakai enum untuk memperjelas 
enum {HENTI, KANAN, KIRI};
int state = HENTI;

// Fungsi untuk plot data ke serial plotter
void plotData() {
  Serial.print((d_in & 1));
  Serial.print(' ');
  Serial.print((d_in>>1 & 1) + 2);
  Serial.print(' ');
  Serial.print((d_in>>2 & 1) + 4);
  Serial.print(' ');
  Serial.print((d_out & 1) + 6);
  Serial.print(' ');
  Serial.print((d_out>>1 & 1) + 8);
  Serial.print(' ');
  Serial.print((d_out>>2 & 1) + 10);
  Serial.println();
  // plot state, d_in dan d_out
  // lengkapi !
}

// putar bit ke kanan
void rotateRight() {
  bool temp=d_out & 1;
  d_out = d_out >> 1;
  d_out = d_out | (temp << N_LED-1);
}

// putar bit ke kiri
void rotateLeft() {
  bool temp=d_out&(1<<N_LED-1);
  d_out=d_out<<1;
  d_out=d_out|(temp);
}

// state Henti
void stateHenti() {
  // periksa event
  switch (d_in) {
    case 0B001 : state = KANAN; return;
    case 0B100 : state = KIRI; return;    
  }
}

void stateKanan() {
  switch (d_in) {
    case 0B010 : state = HENTI; return;
    case 0B100 : state = KIRI; return;
  }
  rotateRight();
}

void stateKiri() {
  switch (d_in) {
    case 0B010 : state = HENTI; return;
    case 0B001 : state = KANAN; return;
  }
  rotateLeft();  
}


// UTAMA
void setup() {
  Serial.begin(BAUD);
  Serial.println("\nBasic DIO");
  
  // Siapkan mode I/O
  for (int i=0; i<N_LED; i++) {
    pinMode(p_led[i], OUTPUT);
    pinMode(p_btn[i], INPUT_PULLUP);
  }

  // Header Plot
  Serial.println("d0 d1 d2");
}


void loop() {
  // baca semua input
  for(int i=0; i<N_LED; i++) {
    byte d=!digitalRead(p_btn[i]);
    d_in = d_in & ~(1<<i) | (d<<i);
  }

  // pemilihan state
  switch(state) {
    case HENTI : stateHenti(); break;
    case KIRI : stateKiri(); break;
    case KANAN : stateKanan(); break;    
  }
    
  // tulis semua output
  for(int i=0; i<N_LED; i++) {
    digitalWrite(p_led[i], (d_out>>i) & 1);
  }

  plotData();
  delay(200);
}

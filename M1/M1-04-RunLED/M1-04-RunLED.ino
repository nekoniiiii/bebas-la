/* Program : Running LED
 * Contoh running LED memakai data bool
 * dan penggunaan array untuk permudah akses
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
bool d_in[N_LED];
bool d_out[N_LED]={1,0,0};

// definisi pin, taruh di array
int p_btn[N_LED] = {BT0, BT1, BT2};
int p_led[N_LED] = {DO0, DO1, DO2};

// Fungsi untuk plot data ke serial plotter
void plotData() {
  for (int i=0; i<N_LED; i++) {
    Serial.print(d_in[i]+2*i);
    Serial.print(' ');
  }
  for (int i=0; i<N_LED; i++) {
    Serial.print(d_out[i]+6+2*i);
    Serial.print(' ');
  }  
  Serial.println();
}

// putar bit ke kiri
void rotateLeft() {
  bool temp=d_out[0];
  for(int i=1; i<N_LED; i++) {
    d_out[i-1] = d_out[i];
  }
  d_out[N_LED-1] = temp;
}

// putar bit ke kanan
void rotateRight() {
  bool temp = d_out[N_LED-1];
  for(int i=N_LED-1; i>0; i--){
    d_out[i] = d_out[i-1];
  }
  d_out[0]=temp;
}

// Mempersiapkan I/O
void setup() {
  Serial.begin(BAUD);
  Serial.println("\nBasic DIO");
  
  // Siapkan mode I/O
  // pakai array lebih ringkas
  for (int i=0; i<N_LED; i++) {
    pinMode(p_led[i], OUTPUT);
    pinMode(p_btn[i], INPUT_PULLUP);
  }

  // Header Plot
  Serial.println("d0 d1 d2");
}

// loop dengan algoritma multi-loop
void loop() {
  // baca semua input
  // dan langsung balik logic krn pull-up
  for(int i=0; i<N_LED; i++) {
    d_in[i]=!digitalRead(p_btn[i]);
  }

  // prosess data sesuai event input
  if (d_in[0]) {
    rotateLeft();
  }
  else if (d_in[2]) {
    rotateRight();    
  }
  
  // tulis semua output
  for(int i=0; i<N_LED; i++) {
    digitalWrite(p_led[i], d_out[i]);
  }

  plotData();
  delay(200);
}

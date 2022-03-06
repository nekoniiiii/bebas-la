/* Program : BASIC digital I/O
 * Contoh digital I/O, data bool dan operatornya
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

#define AO0 26
#define AO1 25

#define LED0 5
#define BT0 4
#define BT1 16
#define BT2 17

// data
// menggunakan tipe bool untuk proses logika
bool d0, d1, d2;
bool dled0, dled1, dbuzzer;

// Fungsi untuk plot data ke serial plotter
void plotData() {
  char buff[40];
  sprintf(buff, "%3d %3d %3d %3d %3d", d0+8, d1+6, d2+4, dled0+2, dbuzzer); 
  Serial.println(buff);  
}


// Definisi pin rangkaian 4 LED
void setup() {
  Serial.begin(BAUD);
  Serial.println("\nBasic DIO");
  
  // Siapkan Output
  pinMode(DO0, OUTPUT);
  pinMode(DO1, OUTPUT);
  pinMode(DO2, OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(AO1, OUTPUT);

  // Siapkan Input
  pinMode(BT0, INPUT);    
  pinMode(BT1, INPUT_PULLUP);    
  pinMode(BT2, INPUT_PULLUP);   

  // Header Plot
  Serial.println("d0  d1  d2  dLED dBuzzer");
}


void loop() {
  // baca semua input, balik jika pullup
  d0 = !digitalRead(BT0);
  d1 = !digitalRead(BT1);
  d2 = !digitalRead(BT2);

  // prosess data
  // LED ON jika salah satu tombol ditekan
  dled0 = d0 || d1 || d2;
  
  // Alarm menyala jika ada 2 atau lebih tombol ditekan
  dled1 = d0&&d1 || d1&&d2 || d0&&d2;
  dbuzzer = !dled1;
  
  // tulis semua output
  digitalWrite(DO0, d0);
  digitalWrite(DO1, d1);
  digitalWrite(DO2, d2);
  digitalWrite(LED0, dled0);
  digitalWrite(AO1, dbuzzer);

  plotData();
  delay(50); // delay 20fps
}

/* Program : DA dan INA
 * Contoh mengeluarkan tegangan dengan DA
 * dan membaca tegangan & arus dengan INA
 * diatur dengan button dan tampil di Serial Monitor / Tracer
 * (c) Eko M. Budi, 2022
 */

// pustaka
#include <Wire.h>
#include <Adafruit_INA219.h>

// pustaka OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BAUD 500000

// Pin Standar kit ESCOPE 2020
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

// pesan obyek INA219
Adafruit_INA219 ina219;

// pesan obyek display
#define D_WIDTH   128 
#define D_HEIGHT  32 
#define D_RESET   4
#define D_ADDR    0x3C
Adafruit_SSD1306 oled(D_WIDTH, D_HEIGHT, &Wire, D_RESET);

// data
bool d_bt0, d_bt2;
byte da_out = 0;

float shunt_mv = 0;
float bus_v = 0;
float current_ma = 0;
float power_mw = 0;

// Menampilkan data
void printData() {
  char buff[50];
  sprintf(buff, "%3d %6.2f %6.2f %6.2f %6.2f",
    da_out, bus_v, shunt_mv, current_ma, power_mw);  
  Serial.println(buff);
}

void printOled() {
  oled.clearDisplay();

  // print desimal
  oled.setTextSize(1);
  oled.setCursor(0, 0);  // Start at top-left corner
  oled.print("V(V) o I(mA) o P(mW)");

  // print binary
  oled.setTextSize(1);
  oled.setCursor(0, 12);
  oled.printf("%4.2f o %5.2f o %4.2f",
    bus_v, current_ma, power_mw);

  // keluarkan
  oled.display();
}

void setup() {
  // Siapkan Serial
  Serial.begin(BAUD);
  Serial.println("\nDA-INA219 Test");
  Serial.println("DA  VI-(V)  Vsh(mV)  I(mA)  P(mW)");
  

  // siapkan INA219
  if (!ina219.begin()) {
    while (1) { delay(100); }
  }

  // siapkan button
  pinMode(BT0, INPUT_PULLUP);
  pinMode(BT2, INPUT_PULLUP);
  
  // siapkan OLED
  if (!oled.begin(SSD1306_SWITCHCAPVCC, D_ADDR)) {
    Serial.println("OLED allocation failed");
    for (;;); // Don't proceed, loop forever
  }
  oled.setFont();
  oled.setTextColor(WHITE);
}

void loop() {
  // baca input
  d_bt0 = !digitalRead(BT0);
  d_bt2 = !digitalRead(BT2);    

  shunt_mv = ina219.getShuntVoltage_mV();
  bus_v = ina219.getBusVoltage_V();
  current_ma = ina219.getCurrent_mA();
  power_mw = ina219.getPower_mW();

  printOled();
  
  // proses input button
  if (d_bt0) {
    da_out--;
    delay(50);
  }
  else if (d_bt2) {
    da_out++;
    delay(50);
  }
  else {
    // keluarkan output
    dacWrite(AO0, da_out);
    delay(1000);
  }
  printData();  
}

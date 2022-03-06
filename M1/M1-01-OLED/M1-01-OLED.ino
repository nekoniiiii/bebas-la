/* Program : Tampilan OLED
 * Contoh memrogram OLED
 * (c) Eko M. Budi, 2022
 */

// pustaka I2C
// menyediakan obyek Wire 
#include <Wire.h>

// pustaka OLED
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// pesan obyek display
#define D_WIDTH   128 
#define D_HEIGHT  32 
#define D_RESET   4
#define D_ADDR    0x3C
Adafruit_SSD1306 oled(D_WIDTH, D_HEIGHT, &Wire, D_RESET);

// data
char counter=0;

void printCount() {
  oled.clearDisplay();

  // print desimal
  oled.setTextSize(1);
  oled.setCursor(0, 0);  // Start at top-left corner
  oled.print(counter);

  // print binary
  oled.setTextSize(2);
  oled.setCursor(0, 12);
  oled.print(counter, BIN);

  // keluarkan
  oled.display();
}

void setup(void)
{
  Serial.begin(9600);
  Serial.println("\nOLED Test");

  // siapkan OLED
  if (!oled.begin(SSD1306_SWITCHCAPVCC, D_ADDR)) {
    Serial.println("OLED allocation failed");
    for (;;); // Don't proceed, loop forever
  }
  oled.setFont();
  oled.setTextColor(WHITE);
}

void loop(void)
{
  // proses
  counter++;
  
  printCount();
  delay(200);
}

/* Program : Tampilan Serial Plotter
 * Contoh memrogram Serial Plotter
 * Dan operasi bitwise logic
 * (c) Eko M. Budi, 2022
 */

#define BAUD 500000

// data
byte counter=0;

// Plot counter bit per bit
void plotCount() {
  byte d = counter;
  Serial.print((d>>7 & 1));
  Serial.print(' ');
  Serial.print((d>>6 & 1) + 2);
  Serial.print(' ');
  Serial.print((d>>5 & 1) + 4);
  Serial.print(' ');
  Serial.print((d>>4 & 1) + 6);
  Serial.print(' ');
  Serial.print((d>>3 & 1) + 8);
  Serial.print(' ');
  Serial.print((d>>2 & 1) + 10);
  Serial.print(' ');
  Serial.print((d>>1 & 1) + 12);
  Serial.print(' ');
  Serial.println((d & 1) + 14);
}

void setup(void)
{
  Serial.begin(BAUD);
  Serial.println("\nSerial Plot Test");
  // Header untuk plot bit per bit
  Serial.println("d7 d6 d5 d4 d3 d2 d1 d0");
}

void loop(void)
{
  // proses
  counter++;
  
  plotCount();
  delay(50);
}

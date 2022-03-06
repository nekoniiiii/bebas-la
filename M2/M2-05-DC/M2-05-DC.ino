
/* Program : DC SWEEP
 * Pengukuran DC Sweep
 * 
 * Dibagi menjadi multifile
 * - sketch pertama : library & konstanta
 * - 10_escope : fungsi dasar escope
 * - 60_serial : fungsi dasar serial
 * - 70_data : deklarasi data global
 * - 72_dc : fungsi untuk operasi DC Sweep
 * - 99_main : fungsi utama setup() dan loop()
 * 
 * (c) Eko M. Budi, 2022
 */

// pustaka
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BAUD 500000
#define PROG_NAME "Pengukuran DC Sweep"

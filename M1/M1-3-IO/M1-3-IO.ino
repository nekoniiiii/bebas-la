/* Program : Pengolahan data mahasiswa
 * Contoh I/O Serial 
 * 13320012 - I Made Wiratathya Putramas
 */

// Konstanta, pakai model lama
#define BOBOT_UTS 0.4
#define BOBOT_UAS 0.6

// konstanta, gaya baru
const float bA = 85.0;
const float bB = 75.0;
const float bC = 60.0;
const float bD = 40.0;

// Data mahasiswa
long nim;
String nama;
int uts;
int uas;
float nilai_angka;
char nilai_huruf;

/* menampilkan prompt dan tunggu jawaban */
void tanya(char s[]) {
  // habiskan data sebelumnya
  while (Serial.available()) 
    Serial.read();
    
  // cetak prompt
  Serial.print(s);
  Serial.print(": ");

  // tunggu sampai ada data
  while (!Serial.available()) {} 
}

/* input data */
void inputData() {
  Serial.println("Masukkan data");
  tanya("NIM");
  nim = Serial.parseInt();
  Serial.println(nim);
  
  tanya("Nama");
  nama = Serial.readStringUntil('\n');
  Serial.println(nama);

  tanya("UTS");
  uts = Serial.parseFloat();
  Serial.println(uts);
  
  tanya("UAS");
  uas = Serial.parseFloat();
  Serial.println(uas);  
}

/* cetak data */
void cetakData() {
  char buffer[60];  // variabel lokal
  
  sprintf(buffer, "%8u %-15s %6.2f %c",
    nim, nama.c_str(), nilai_angka, nilai_huruf);

  Serial.println(buffer);
  Serial.println("----------");
}

/* hitung nilai angka dari nilai uts dan uas */
float nilaiAngka(int uts, int uas) {
  return (BOBOT_UTS*uts)+(BOBOT_UAS*uas);
}

/* hitung nilai huruf berdasar batas bA, bB, bC, bD */
char nilaiHuruf(float nilai_angka) {
 // … gunakan pencabangan untuk menentukan nilai huruf
 if (nilai_angka>=bA){
  return 'A';
 }
 else if (nilai_angka>=bB){
  return 'B';
 }
 else if (nilai_angka>=bC){
  return 'C';
 }
 else if (nilai_angka>=bD){
  return 'D';
 }
 else{
  return 'E';
 }
}

// inisialisasi
void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println("Pengolahan Nilai");
}

// loop utama
void loop() {  
  inputData();  
  nilai_angka = nilaiAngka(uts, uas);
  nilai_huruf = nilaiHuruf(nilai_angka);
  cetakData();    
}

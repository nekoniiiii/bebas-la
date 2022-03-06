// UTAMA
void setup() {
  // Siapkan serial, tunggu sampai terkoneksi
  Serial.begin(BAUD);
  while (!Serial);
  Serial.println();
  Serial.println(PROG_NAME);

  // siapkan board ESCOPE
  escopeSetup();  
}

// loop tunggu user input, lalu proses
void loop() {
  // minta masukan dari user
  serialPrompt("Pengukuran Sinyal");

  // tunggu sampai memang ada kiriman
  while(!Serial.available()) {
    oledPrint(0,0,"DC");
    delay(500);    
    oled.clearDisplay();
    delay(500);    
  }
  
  int mv0 = Serial.parseInt();
  int mv1 = Serial.parseInt();
  mv0 = constrain(mv0,100,3100);
  mv1 = constrain(mv1,100,3100);
  Serial.printf("%d %d\n",mv0,mv1);

  // lakukan aksi DC
  dcAction(mv0, mv1);  
}

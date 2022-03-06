/*
 * Pengukuran AC
 */
#define N_SWEEP 9
// data spektrum

int spectrum[N_SWEEP][2] = {
  {1,0},
  {2,0},
  {4,0},
  {8,0},
  {10,0},
  {20,0},
  {40,0},
  {80,0},
  {100,0}
};

void acPrintSpectrum() {
  for (int i=0; i<N_SWEEP; i++){
    char buff[40];
  sprintf(buff, "%4d %4d", spectrum[i][0], spectrum[i][1]);
  Serial.println(buff);
  }
}

void acPrintHeader() {
  char buff[60]; 
  sprintf(buff, "F(Hz) \tGain(%%)");
  Serial.println(buff);
}

// fungsi pengukuran AC
void acMeasure() {
  signal_type = ST_SINUS;
  for (int i=0; i<N_SWEEP; i++) {
    
    // hitung periode dari frekuensi di tabel
    int frek = spectrum[i][0]; // ambil frekuensi di tabel
    periode_signal = (float)1000/frek  ; // hitung periode dr frekuensi
    
    trMeasure(); // panggil pengukuran transien
    
    // hasil pengukuran transien ada di buffer
    
    int a0 = (float)(lbuffer.max(1)-lbuffer.min(1))/2 +0.5; // hitung amplitudo sinyal V0
    int a1 = (float)(lbuffer.max(2)-lbuffer.min(2))/2 +0.5; // hitung amplitude sinyal V1
    
    spectrum[i][1] = 100 * a1 / a0; // simpan gain dalam persen
 }
}

// fungsi pengukuran AC
void acAction() {
  acPrintHeader();
  acMeasure();
  acPrintSpectrum();
}

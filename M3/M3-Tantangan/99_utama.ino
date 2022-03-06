/*
 * Program utama 
 * - menerima masukan dari serial dengan format
 *   [perintah] [periode_ms]
 * - lalu menjalankan pengukuran transien atau AC
 *   
 * Coba jalankan dan amati luaran dengan Serial Plotter,
 * beri masukan, misalnya:
 *   TS 1000
 *   AC 
 */ 

// Rentang periode (dalam ms)
#define PERIODE_MIN 10
#define PERIODE_MAX 10000


void parseAC() {
  // tak ada parameter lain, langsung 
  acAction();  
}

void parseTX(int st) {
  // baca parameter frekuensi
  float frek = Serial.parseFloat();
  int prd = (float)1000/frek +0.5;
  if ((prd >= PERIODE_MIN) && (prd <= PERIODE_MAX)) {
      // kalau memenuhi lakukan aksi
      periode_signal = prd;  // set periode
      signal_type = st;  // set bentuk gelombang      
      trAction();
  }  
}

void parseCommand() {
    // baca perintah 
    String cmd = Serial.readStringUntil(' ');
    cmd.trim();
    cmd.toUpperCase();
    
    if (cmd == "TS") {
      int mv0 = Serial.parseInt();
      int mv1 = Serial.parseInt();
      mv0 = constrain(mv0,100,3100);
      mv1 = constrain(mv1,100,3100);
      setRange(mv0, mv1);
      parseTX(ST_SINUS);
    }
    else if (cmd == "TR") {
      int mv0 = Serial.parseInt();
      int mv1 = Serial.parseInt();
      mv0 = constrain(mv0,100,3100);
      mv1 = constrain(mv1,100,3100);
      setRange(mv0, mv1);
      parseTX(ST_RECTANGLE);
    }
    else if (cmd == "TT") {
      int mv0 = Serial.parseInt();
      int mv1 = Serial.parseInt();
      mv0 = constrain(mv0,100,3100);
      mv1 = constrain(mv1,100,3100);
      setRange(mv0, mv1);
      parseTX(ST_TRIANGLE);
    }
    else if (cmd == "TW") {
      int mv0 = Serial.parseInt();
      int mv1 = Serial.parseInt();
      mv0 = constrain(mv0,100,3100);
      mv1 = constrain(mv1,100,3100);
      setRange(mv0, mv1);
      parseTX(ST_SAWTOOTH);
    }
    else if (cmd == "AC") {
      Serial.println("AC SWEEP");
      parseAC();
    }
    else if (cmd == "OP") {
      int mv0 = Serial.parseInt();
      mv0 = constrain(mv0,100,3100);
      Serial.println("Operating Point");
      Serial.println(mv0);
      opAction(mv0);
    }
    else if (cmd == "DC") {
      int mv0 = Serial.parseInt();
      int mv1 = Serial.parseInt();
      mv0 = constrain(mv0,100,3100);
      mv1 = constrain(mv1,100,3100);
      Serial.printf("DC SWEEP %d %d\n",mv0,mv1);
      dcAction(mv0, mv1);
    }
    // habiskan semua sisa di serial
    while(Serial.available()) Serial.read();
}

// Utama, algoritma multi-loop periodik
void setup() {
  Serial.begin(500000);    
  delay(3000);
  Serial.println();
  Serial.println(PROG_NAME);
}

void loop() {
  if (Serial.available()) {
    parseCommand();
  }
}

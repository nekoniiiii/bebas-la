/*
 * Pengukuran transien
 */

#define N_WARMUP 5

// generate signal
void generateSignal() {
  int tp = p1.elapsed() % periode_signal;
  da_mv = fSignal(tp, periode_signal);
  dacWrite(p_da, mvToDa(da_mv));
}

// trace signal, masuk buffer
void traceSignal() {
  int item_mv[N_SIGNAL+1];
  item_mv[0]=da_mv;  // sinyal output 
  for(int i=0; i<N_SIGNAL; i++) {
     int ad = analogRead(p_ad[i]);
     item_mv[1+i] = adToMv(ad);
  }
  lbuffer.put(item_mv); // masuk buffer
}

void trPlotSignal() {
  char buff[40];
  int item_mv[N_SIGNAL+1];
  while (!lbuffer.isEmpty()) {
    lbuffer.take(item_mv);  
    sprintf(buff, "%4d %4d %4d",
      item_mv[0], item_mv[1], item_mv[2]);
    Serial.println(buff);
  }
}

void trPlotHeader() {
  char buff[60]; 
  sprintf(buff, "Vout V0   V1  %s Frekuensi=%.2f", 
    signal_strs[signal_type], 1000/(float)periode_signal);
  Serial.println(buff);
}


// fungsi pengukuran transien
void trMeasure() {
  ts_signal = periode_signal / N_DATA;
  if (ts_signal < 1)
    ts_signal = 1;  
  p1.reset(ts_signal);
  lbuffer.reset();

  // pemanasan
  for (int i=0; i<N_DATA*N_WARMUP; i++) {
    p1.wait();
    generateSignal();
  }

  // pengukuran transien
  for (int i=0; i<N_DATA; i++) {
    p1.wait();
    generateSignal();
    traceSignal();
  }
}

// fungsi pengukuran transien
void trAction() {
  trPlotHeader();
  trMeasure();
  trPlotSignal();
}

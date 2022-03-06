/*
 * Fungsi-fungsi untuk penghasil sinyal
 */

// enumerasi bentuk sinyal
enum {ST_SINUS, ST_RECTANGLE, ST_TRIANGLE, ST_SAWTOOTH, ST_MAX};

// rentang signal (dalam mv)
int signal_min = 500;
int signal_max = 2500;
int signal_span = signal_max - signal_min;

void setRange(int min, int max) {
  signal_min = min;
  signal_max = max;
  signal_span = signal_max - signal_min;
}

// fungsi menghasilkan sinyal sinus
// amplitudo signal_min - signal_max
int fSin(unsigned long t, unsigned long periode) {
  float s = sin(2*M_PI*t/periode);
  return ((s + 1)/2*signal_span)+signal_min;
}

// fungsi menghasilkan sinyal kotak
// rentang signal_min - signal_max
int fRectangle(unsigned long t, unsigned long periode) {
  if (t<periode/2){
    return signal_max;
  }
  return signal_min;
}

// fungsi menghasilkan sinyal segitiga
// rentang signal_min - signal_max
int fTriangle(unsigned long t, unsigned long periode) {
  if (t>3*periode/4){
    return (signal_span/(0.5*periode))*(t-(3*periode/4)) + signal_min;
  }
  else if (t>periode/4){
    return (-signal_span/(0.5*periode))*(t-(periode/4)) + signal_max ;
  }
  else {
    return (signal_span/(0.5*periode))*t + ((signal_max+signal_min)/2);
  }
}

// fungsi menghasilkan gigi gergaji
// rentang signal_min - signal_max
int fSawTooth(unsigned long t, unsigned long periode) {
  if (t>3*periode/4){
    return (t-3*periode/4)*signal_span/periode + signal_min;
  }
  else{
    return t*signal_span/periode + (signal_span/4 + signal_min);
  }
}

// fungsi menghasilkan noise
// rentang signal_min - signal_max
int fNoise() {
  return random(signal_min, signal_max+1);
}

// fungsi menghasilkan sinyal dengan type tertentu
int fSignal(int stype, unsigned long t, unsigned long periode) {
  switch(stype) {
    case ST_SINUS: return fSin(t, periode); 
    case ST_RECTANGLE: return fRectangle(t, periode);
    case ST_TRIANGLE: return fTriangle(t, periode);
    case ST_SAWTOOTH: return fSawTooth(t, periode);
  }
  return fNoise();
}

// fungsi untuk gain (dalam persen) dan offset
int fAdjust(int s, int gain, int offset) {
  int s1 = s - offset;
  return (s1 * gain / 100) + offset;
}

// fungsi menaruh sinyal ke tengah dan diberi gain
int fCenter(int s, int gain) {
  int offset = signal_min + (signal_span/2);
  return fAdjust(s,gain,offset);
}

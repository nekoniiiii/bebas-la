/*
 * Action Operating Condition
 */

void opPrintHeader() {
  Serial.println("VDA     V0      V1");
}

void opPlot() {
  char buff[40];
  sprintf(buff, "%4d   %4d    %4d", 
    da_mv, ad_mv[0], ad_mv[1]);
  Serial.println(buff);  
}

// Melaksanakan prosedur OP
// Kirim output tertentu ke DA
// lalu ukur dan print ke Serial sebanyak ndata
// lalu hitung rata-rata
void opAction(int op_mv) {
  int ndata = 20;

  opPrintHeader();

  da_mv = op_mv;   // simpan op ke data global

  // output 
  dacWriteMv(p_da, da_mv);
  delay(100); // tunggu tunak

  for (int i=0; i<ndata; i++) {
    
    //menyimpan data ke array
    for(int j=0; j<N_AD; j++) {
      ad_mv[j] = analogReadMv(p_ad[j]);
    }
    
    // tulis baris
    opPlot();
  }  
  Serial.println("==========================================");
}

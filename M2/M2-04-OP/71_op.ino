/*
 * Action Operating Condition
 */

void opPrintHeader() {
  Serial.println("VDA     Vi+     V0      V1      V2");
}

void opPlot() {
  char buff[40];
  sprintf(buff, "%4d    %4d    %4d    %4d    %4d", 
    da_mv, ina_mv, ad_mv[0], ad_mv[1], ad_mv[2]);
  Serial.println(buff);  
}

// Melaksanakan prosedur OP
// Kirim output tertentu ke DA
// lalu ukur dan print ke Serial sebanyak ndata
// lalu hitung rata-rata
void opAction(int op_mv) {

  opPrintHeader();

  da_mv = op_mv;   // simpan op ke data global

  // inisialisasi variabel 
  float rerata[N_DA+1] = {0,0,0};
  float stdev[N_DA+1] = {0,0,0};

  // output 
  dacWriteMv(p_da, da_mv);
  delay(100); // tunggu tunak

  for (int i=0; i<ndata; i++) {
    // baca
    ina_mv = inaReadLoadMv();
    
    //menyimpan data ke array
    temp[0][i] = ina_mv;
    for(int j=0; j<N_DA; j++) {
      ad_mv[j] = analogReadMv(p_ad[j]);
      temp[j+1][i] = ad_mv[j];
    }
    
    // tulis baris
    opPlot();
  }  

  //menghitung jumlah data untuk rerata
  for (int i=0; i<(N_DA+1); i++) {
    for (int j=0; j<ndata; j++) {
      rerata[i] = rerata[i] + temp[i][j];
    }
  }
  
  for (int i=0; i<(N_DA+1); i++) {
    rerata[i] = rerata[i]/ndata; //menghitung rerata
    //menghitung sum off error squared
    for (int j=0; j<ndata; j++) {
      stdev[i] = stdev[i] + pow(temp[i][j]-rerata[i], 2);
    }
    stdev[i] = sqrt(stdev[i]/(ndata-1)); //menghitung stdev
  }
  Serial.println("==========================================");
  Serial.printf("AVG     %.2f %.2f %.2f %.2f \n", rerata[0], rerata[1], rerata[2], rerata[3]);
  Serial.printf("STDEV   %.2f    %.2f    %.2f    %.2f \n", stdev[0], stdev[1], stdev[2], stdev[3]);
}

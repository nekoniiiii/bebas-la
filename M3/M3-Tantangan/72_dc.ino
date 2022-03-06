/*
 * Action DC Sweep Condition
 */

void dcPrintHeader() {
  Serial.println("VDA  V0   V1");
}

void dcPlot() {
  char buff[40];
  sprintf(buff, "%4d %4d %4d", 
    da_mv, ad_mv[0], ad_mv[1]);
  Serial.println(buff);  
}

void dcAction(int v_min, int v_max) {

  dcPrintHeader();
  
  for (int i = v_min; i<= v_max; i+=100) {
     da_mv = i;
     
     
     dacWriteMv(p_da, da_mv);
     delay(100);
     
     for(int j=0; j<N_AD; j++) {
       ad_mv[j] = analogReadMv(p_ad[j]);
     }
     dcPlot();
  }
  Serial.println("--------------------------------------------------");
}

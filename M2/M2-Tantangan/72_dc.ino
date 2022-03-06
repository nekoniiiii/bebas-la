/*
 * Action DC Sweep Condition
 */

void dcPrintHeader() {
  Serial.println("VDA  Vi+  V0   V1   V2");
}

void dcPlot() {
  char buff[40];
  sprintf(buff, "%4d %4d %4d %4d %4d", 
    da_mv, ina_mv, ad_mv[0], ad_mv[1], ad_mv[2]);
  Serial.println(buff);  
}

void dcAction(int v_min, int v_max) {

  dcPrintHeader();
  
  // inisialisasi variabel-variabel untuk perhitungan a, b, dan r2
  float sum_da = 0; //jumlah seluruh da_mv (x)
  float sum_da2 = 0; //jumlah seluruh da_mv^2 (x^2)
  float sum_vi = 0; //jumlah seluruh ina_mv (y)
  float sum_vi2 = 0; //jumlah seluruh ina_mv^2 (y^2)
  float sum_davi = 0; //jumlah seluruh (da_mv*vi_mv) (xy)
  float sum_ad[N_DA]= {0,0,0}; //jumlah seluruh ad_mv (y)
  float sum_ad2[N_DA]= {0,0,0}; //jumlah seluruh (ad_mv^2) (y^2)
  float sum_daad[N_DA]= {0,0,0}; //jumlah seluruh (da_mv*ad_mv) (xy)
  
  for (int i = v_min; i<= v_max; i+=100) {
     da_mv = i;
     
     sum_da = sum_da + da_mv;
     sum_da2 = sum_da2 + pow(da_mv, 2);
     
     dacWriteMv(p_da, da_mv);
     delay(100);
     ina_mv = inaReadLoadMv();
     
     sum_vi = sum_vi + ina_mv;
     sum_vi2 = sum_vi2 + pow(ina_mv, 2);
     sum_davi = sum_davi + (da_mv*ina_mv);
     
     for(int j=0; j<N_DA; j++) {
       ad_mv[j] = analogReadMv(p_ad[j]);
       
       sum_ad[j] = sum_ad[j] + ad_mv[j];
       sum_ad2[j] = sum_ad2[j] + pow(ad_mv[j],2);
       sum_daad[j] = sum_daad[j] + (da_mv*ad_mv[j]);
     }
     dcPlot();
  }
  // perhitungan a, b, dan r2 dengan rumus regresi linear serta rumus R Squared, antara da_mv dan ina_mv
  a = ((sum_vi*sum_da2)-(sum_da*sum_davi))/((((v_max-v_min)/100+1)*sum_da2)-pow(sum_da,2));
  b = ((((v_max-v_min)/100+1)*sum_davi)-(sum_da*sum_vi))/((((v_max-v_min)/100+1)*sum_da2)-pow(sum_da, 2));
  r2 = pow(((((v_max-v_min)/100+1)*sum_davi)-(sum_da*sum_vi)),2)/(((((v_max-v_min)/100+1)*sum_da2)-pow(sum_da,2))*((((v_max-v_min)/100+1)*sum_vi2)-pow(sum_vi, 2)));
  Serial.println("--------------------------------------------------");
  Serial.printf("Persamaan Regresi antara DA dan VI+: y = %.3fx + %.3f\n", b, a);
  Serial.printf("R squared %.5f\n", r2);

  // perhitungan a, b, dan r2 dengan rumus regresi linear serta rumus R Squared, antara da_mv dan ad_mv
  for (int j = 0; j<N_DA; j++) {
     a = ((sum_ad[j]*sum_da2)-(sum_da*sum_daad[j]))/((((v_max-v_min)/100+1)*sum_da2)-pow(sum_da,2));
     b = ((((v_max-v_min)/100+1)*sum_daad[j])-(sum_da*sum_ad[j]))/((((v_max-v_min)/100+1)*sum_da2)-pow(sum_da, 2));
     r2 = (pow(((((v_max-v_min)/100+1)*sum_daad[j])-(sum_da*sum_ad[j])),2))/(((((v_max-v_min)/100+1)*sum_da2)-pow(sum_da,2))*((((v_max-v_min)/100+1)*sum_ad2[j])-pow(sum_ad[j], 2)));
     Serial.printf("Persamaan Regresi antara DA dan V%d: y = %.3fx + %.3f\n",j, b, a);
     Serial.printf("R squared %.5f\n", r2);
  }
}

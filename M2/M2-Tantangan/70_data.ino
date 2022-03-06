/* 
 * Data global untuk operasi 
 */ 

// banyak pin DA 
#define N_DA 3

// Pin I/O
int p_ad[N_DA] = {DI0, DI1, DI2};
int p_da = AO0;

// data pengukuran
int ad_mv[N_DA];  
int da_mv;
int ina_mv;
float a; //hasil regresi: y = bx + a
float b;
float r2; // R squared

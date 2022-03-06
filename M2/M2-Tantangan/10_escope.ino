/*
 * Konstanta dan fungsi dasar escope
 */

// Pin Standar kit ESCOPE 2020 ESP32
#define DO0 13
#define DO1 12
#define DO2 14
#define DO3 27
#define DO4 33

#define DI0 32
#define DI1 35
#define DI2 34
#define DI3 39
#define DI4 36

#define AO0 26
#define AO1 25

#define LED0 5
#define BT0 4
#define BT1 16
#define BT2 17

#define DA_MAX 255
#define AD_MAX 4095

// KONVERSI dgn Kalibrasi
// index kolom array kalibrasi
enum {I_AD, I_MV, I_DA, N_COL};
#define N_ROW 256

// isi tabel ini dari hasil program sebelumnya
int tabel[N_ROW][N_COL] = {
{   0,   32,    0},
{   1,   48,    1},
{   2,   56,    2},
{   4,   68,    3},
{   6,   80,    4},
{   9,   88,    5},
{  28,  104,    6},
{  38,  116,    7},
{  45,  124,    8},
{  67,  140,    9},
{  81,  152,   10},
{  92,  164,   11},
{ 103,  176,   12},
{ 126,  188,   13},
{ 144,  200,   14},
{ 144,  216,   15},
{ 167,  224,   16},
{ 186,  236,   17},
{ 191,  248,   18},
{ 207,  260,   19},
{ 222,  272,   20},
{ 240,  284,   21},
{ 253,  300,   22},
{ 270,  308,   23},
{ 281,  320,   24},
{ 288,  332,   25},
{ 309,  344,   26},
{ 320,  356,   27},
{ 338,  368,   28},
{ 355,  380,   29},
{ 369,  392,   30},
{ 375,  408,   31},
{ 389,  416,   32},
{ 400,  428,   33},
{ 425,  440,   34},
{ 443,  456,   35},
{ 455,  468,   36},
{ 470,  476,   37},
{ 490,  488,   38},
{ 499,  504,   39},
{ 500,  512,   40},
{ 502,  524,   41},
{ 539,  540,   42},
{ 558,  548,   43},
{ 571,  564,   44},
{ 587,  572,   45},
{ 597,  588,   46},
{ 612,  600,   47},
{ 624,  608,   48},
{ 646,  624,   49},
{ 679,  636,   50},
{ 673,  648,   51},
{ 688,  660,   52},
{ 702,  672,   53},
{ 717,  688,   54},
{ 723,  696,   55},
{ 746,  704,   56},
{ 766,  720,   57},
{ 770,  732,   58},
{ 784,  740,   59},
{ 783,  756,   60},
{ 814,  768,   61},
{ 832,  784,   62},
{ 848,  796,   63},
{ 861,  804,   64},
{ 880,  816,   65},
{ 896,  832,   66},
{ 910,  844,   67},
{ 913,  856,   68},
{ 943,  868,   69},
{ 958,  880,   70},
{ 962,  892,   71},
{ 979,  900,   72},
{1001,  916,   73},
{1008,  928,   74},
{1028,  940,   75},
{1031,  952,   76},
{1059,  964,   77},
{1079,  976,   78},
{1088,  988,   79},
{1104, 1000,   80},
{1118, 1012,   81},
{1131, 1028,   82},
{1141, 1036,   83},
{1157, 1048,   84},
{1175, 1060,   85},
{1190, 1072,   86},
{1200, 1084,   87},
{1216, 1096,   88},
{1233, 1108,   89},
{1248, 1120,   90},
{1264, 1136,   91},
{1280, 1144,   92},
{1287, 1156,   93},
{1307, 1168,   94},
{1319, 1184,   95},
{1339, 1192,   96},
{1364, 1204,   97},
{1360, 1216,   98},
{1382, 1232,   99},
{1362, 1240,  100},
{1413, 1252,  101},
{1423, 1264,  102},
{1442, 1276,  103},
{1453, 1292,  104},
{1465, 1300,  105},
{1469, 1316,  106},
{1499, 1324,  107},
{1510, 1336,  108},
{1530, 1352,  109},
{1552, 1364,  110},
{1566, 1376,  111},
{1575, 1388,  112},
{1585, 1396,  113},
{1609, 1412,  114},
{1617, 1424,  115},
{1632, 1436,  116},
{1647, 1448,  117},
{1663, 1460,  118},
{1680, 1472,  119},
{1687, 1484,  120},
{1711, 1492,  121},
{1719, 1508,  122},
{1709, 1520,  123},
{1755, 1532,  124},
{1767, 1544,  125},
{1778, 1560,  126},
{1795, 1568,  127},
{1809, 1584,  128},
{1828, 1596,  129},
{1845, 1608,  130},
{1856, 1620,  131},
{1872, 1632,  132},
{1887, 1644,  133},
{1897, 1656,  134},
{1915, 1672,  135},
{1925, 1680,  136},
{1937, 1692,  137},
{1959, 1700,  138},
{1977, 1716,  139},
{1984, 1728,  140},
{2000, 1740,  141},
{2018, 1752,  142},
{2034, 1768,  143},
{2045, 1776,  144},
{2065, 1792,  145},
{2078, 1800,  146},
{2094, 1816,  147},
{2107, 1824,  148},
{2119, 1840,  149},
{2134, 1848,  150},
{2139, 1864,  151},
{2167, 1872,  152},
{2177, 1888,  153},
{2196, 1900,  154},
{2206, 1912,  155},
{2227, 1924,  156},
{2239, 1932,  157},
{2256, 1948,  158},
{2269, 1956,  159},
{2275, 1968,  160},
{2297, 1984,  161},
{2320, 1992,  162},
{2323, 2008,  163},
{2339, 2016,  164},
{2355, 2032,  165},
{2368, 2044,  166},
{2385, 2056,  167},
{2394, 2068,  168},
{2413, 2080,  169},
{2425, 2088,  170},
{2445, 2104,  171},
{2451, 2116,  172},
{2473, 2128,  173},
{2483, 2140,  174},
{2501, 2152,  175},
{2512, 2164,  176},
{2530, 2176,  177},
{2545, 2192,  178},
{2559, 2200,  179},
{2590, 2212,  180},
{2589, 2224,  181},
{2615, 2232,  182},
{2624, 2252,  183},
{2639, 2260,  184},
{2651, 2272,  185},
{2671, 2284,  186},
{2679, 2296,  187},
{2698, 2308,  188},
{2710, 2320,  189},
{2725, 2336,  190},
{2736, 2344,  191},
{2757, 2356,  192},
{2768, 2368,  193},
{2790, 2380,  194},
{2811, 2396,  195},
{2841, 2408,  196},
{2837, 2416,  197},
{2854, 2432,  198},
{2874, 2444,  199},
{2883, 2452,  200},
{2898, 2464,  201},
{2915, 2476,  202},
{2928, 2492,  203},
{2943, 2504,  204},
{2963, 2516,  205},
{2974, 2528,  206},
{2995, 2540,  207},
{3011, 2552,  208},
{3028, 2564,  209},
{3047, 2576,  210},
{3061, 2588,  211},
{3083, 2600,  212},
{3107, 2616,  213},
{3125, 2628,  214},
{3136, 2636,  215},
{3151, 2644,  216},
{3191, 2660,  217},
{3196, 2676,  218},
{3213, 2688,  219},
{3237, 2696,  220},
{3249, 2708,  221},
{3275, 2720,  222},
{3288, 2736,  223},
{3312, 2744,  224},
{3329, 2760,  225},
{3355, 2772,  226},
{3375, 2780,  227},
{3391, 2792,  228},
{3418, 2804,  229},
{3437, 2820,  230},
{3455, 2828,  231},
{3483, 2840,  232},
{3502, 2852,  233},
{3521, 2864,  234},
{3550, 2880,  235},
{3571, 2888,  236},
{3600, 2904,  237},
{3630, 2916,  238},
{3648, 2924,  239},
{3669, 2936,  240},
{3702, 2952,  241},
{3722, 2960,  242},
{3750, 2976,  243},
{3772, 2988,  244},
{3803, 3000,  245},
{3831, 3012,  246},
{3858, 3024,  247},
{3885, 3036,  248},
{3905, 3048,  249},
{3932, 3060,  250},
{3967, 3072,  251},
{3991, 3084,  252},
{4023, 3096,  253},
{4055, 3108,  254},
{4083, 3120,  255},
};


// Fungsi konversi
int mvToDa(int mv) {
  // konversi linier
  int ofs_mv = tabel[0][I_MV];
  float delta_mv = (float)tabel[N_ROW-1][I_MV]-ofs_mv;
  float delta_da = (float)tabel[N_ROW-1][I_DA];

  // kalkulasi pakai float, potong jadi int lagi
  int da = (int)((mv - ofs_mv) * delta_da / delta_mv);

  return constrain(da,0,DA_MAX);
}

// cari row yang isi AD nya sudah > ad
// return index antara 1 - (N_ROW-1)
int findIdx(int ad) {
  int i;
  for (i=1; i<N_ROW-1; i++) {
    if (tabel[i][I_AD] >= ad) break;    
  }
  return i;
}

// Fungsi konversi
int adToMv(int ad) {
  int idx = findIdx(ad);

  // konversi look-up table
  // interpolasi linier
  int ofs_ad = tabel[idx-1][I_AD];
  int ofs_mv = tabel[idx-1][I_MV];
  float delta_mv = (float)tabel[idx][I_MV]-ofs_mv;
  float delta_ad = (float)tabel[idx][I_AD]-ofs_ad;

  int mv = (int)((ad-ofs_ad) * delta_mv / delta_ad + 0.5) + ofs_mv;  

  return mv;
}

// DigitalToAnalog
void dacWriteMv(int pin, int mv) {
  dacWrite(pin, mvToDa(mv));
}

// DigitalToAnalog
int analogReadMv(int pin) {
  return adToMv(analogRead(pin));
}

// INA219
Adafruit_INA219 ina219;

int inaReadLoadMv() {
  float shunt_mv = ina219.getShuntVoltage_mV();
  float bus_v = ina219.getBusVoltage_V();    
  return (int) (shunt_mv + bus_v * 1000 + 0.5);      
}

int inaReadBusMv() {
  float bus_v = ina219.getBusVoltage_V();    
  return (int) (bus_v * 1000 + 0.5);      
}

// OLED
// pesan obyek display
#define D_WIDTH   128 
#define D_HEIGHT  32 
#define D_RESET   4
#define D_ADDR    0x3C
Adafruit_SSD1306 oled(D_WIDTH, D_HEIGHT, &Wire, D_RESET);

void oledPrint(int x, int y, char *str) {
  oled.setCursor(x,y);
  oled.print(str);
  oled.display();  
}

void oledBlink(int x, int y, char *str) {
  static bool dblink=true;
  if (dblink) {
    oled.setCursor(x,y);
    oled.print(str);
  }
  else {
    oled.clearDisplay();    
  }
  oled.display();
  dblink != dblink;
  delay(500);
}

// LED
void ledBlink() {
  static bool dled=true;
  digitalWrite(LED0, dled);
  dled=!dled;
}

void escopeSetup() {
  // siapkan OLED
  if(!oled.begin(SSD1306_SWITCHCAPVCC, D_ADDR)) {
    for(;;); 
  }
  oled.setTextColor(WHITE);
  oled.clearDisplay();
  oled.display();
  
  // siapkan INA219
  if (!ina219.begin()) {
    while (1) { delay(100); }
  }   

  // siapkan button
  pinMode(BT0, INPUT_PULLUP);
  pinMode(BT1, INPUT_PULLUP);
  pinMode(BT2, INPUT_PULLUP);

  // siapkan LED
  pinMode(LED0, OUTPUT);
  digitalWrite(LED0, LOW);
}

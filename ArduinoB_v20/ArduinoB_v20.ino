#include <XBee.h>

#define DEBUG 0   // 0 to disable, 1 to enable printing debug messages
#if DEBUG
  #define DPRINT(...)    Serial.print(__VA_ARGS__)
  #define DPRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define DPRINT(...)    (void)0
  #define DPRINTLN(...)  (void)0
#endif

#define DELTA_THRESHOLD 7         // Threshold for reporting a change
#define PUBLISH_DELTA 10
#define NUM_SENSORS 9            // 5 XBEE under COORDINATOR B and 6 XBEE under COORDINATOR D

// Two coordinators: one on Serial2, one on Serial3
XBee                 xbee1, xbee2;
ZBRxIoSampleResponse sample1, sample2;

// Keep track of last readings for each channel & port
uint16_t    ad1_1;
uint16_t    ad1_2;
uint16_t    ad2_1;
uint16_t    ad2_2;
uint16_t    lastAd1_1 = 0, lastAd2_1 = 0;
uint16_t    lastAd1_2 = 0, lastAd2_2 = 0;
uint8_t    SL3_1;
uint8_t    SL4_1;
uint8_t    SL3_2;
uint8_t    SL4_2;

unsigned long ad1;
unsigned long ad2;
unsigned long noses[NUM_SENSORS];  // array to hold values for nose information
unsigned long store_noses[NUM_SENSORS];
int calib_noses[NUM_SENSORS];
int calib_nose_times[NUM_SENSORS];
int nose_switches[NUM_SENSORS];

int switchOff1 = 0;
int switchOff2 = 0;

unsigned long mouths[NUM_SENSORS];  // array to hold values for mouth information
unsigned long store_mouths[NUM_SENSORS];
//unsigned long calib_mouths[13];
int calib_mouths[NUM_SENSORS];
int calib_mouth_times[NUM_SENSORS];
int mouth_switches[NUM_SENSORS];

// previous values, initialized so first real reading always shows up
unsigned long prevNoses[NUM_SENSORS]  = { 0 };
unsigned long prevMouths[NUM_SENSORS] = { 0 };

// AANPASSEN TONEN PER MEGA !!!! - array controlA + array list _ 4 tonen per xbee: mond IN mond UIT neus IN neus UIT
//int controlA[5][4] = { {24, 25, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 18, 19}, {20, 21, 22, 23} };
//int controlA[4][NUM_SENSORS] = { {62,64,65,66},{67,69,71,72},{77,74,79,81}};
int controlA[NUM_SENSORS][4] = {
  {42, 41, 45, 40},   // sensor 0
  {46, 39, 52, 38},   // sensor 1
  {37, 53, 36, 54},   // sensor 2
  {35, 34, 50, 33},   // sensor 3
  {49, 32, 31, 48},   // sensor 4
  {30, 47, 29, 28},   // sensor 5
  {55, 27, 56, 26},   // sensor 6
  {25, 24, 44, 23},   // sensor 7
  {43, 22, 21, 127}   // sensor 8
  //{77, 78, 79, 80},   // sensor 9
  //{81, 82, 83, 84}    // sensor 10
};
//int list[] = { 24, 25, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 18, 19, 20, 21, 22, 23 };
// nieuwe miditonenlijst
int list[] = {41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84 };
const size_t n = sizeof(list) / sizeof(list[0]);

//int controlB[5][4] = { {24,25,26,27},{28,29,30,31},{32,33,34,35},{36,37,38,39},{40,41,42,43} };
long lastDebounceTime = 0;

long maxi = 525;
long mini = 475;

unsigned long publishTime = 0;

/*for the MIDI stuff */
 int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 int noteON = 144; //144 = 10010000 in binary, note on command
 int noteOFF = 128; //128 = 10000000 in binary, note off command

void setup() {
  Serial.begin(31250);
  Serial2.begin(9600);    // XBee Coordinator#1 on Mega’s Serial2 (pins 16=RX2,17=TX2)
  Serial3.begin(9600);    // XBee Coordinator#2 on Mega’s Serial3 (pins 14=RX3,15=TX3)

  xbee1.setSerial(Serial2);
  xbee2.setSerial(Serial3);

  DPRINTLN("Waiting for XBee I/O Sample (0x92) frames on Serial2 & Serial3...");
}

void loop() {
  // ————— Coordinator B (Serial2) —————
  xbee1.readPacket();
  if ( xbee1.getResponse().isAvailable()
    && xbee1.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE ) {

    xbee1.getResponse().getZBRxIoSampleResponse(sample1);

    // extract SL3 & SL4
    XBeeAddress64 addr1 = sample1.getRemoteAddress64();
    uint32_t   lsb1     = addr1.getLsb();
    SL3_1    = (lsb1 >> 8) & 0xFF;
    SL4_1    =  lsb1        & 0xFF;

    // AD1 with delta
    if ( sample1.isAnalogEnabled(1) ) {
      ad1_1 = sample1.getAnalog(1);
      if ( abs((int)ad1_1 - (int)lastAd1_1) > DELTA_THRESHOLD ) {
        DPRINT("Coord1  "); DPRINT(SL3_1, HEX); DPRINT(SL4_1, HEX);
        DPRINT("  AD1 = ");  DPRINTLN(ad1_1);
      }
      lastAd1_1 = ad1_1;
    }

    // AD2 with delta
    if ( sample1.isAnalogEnabled(2) ) {
      ad2_1 = sample1.getAnalog(2);
      if ( abs((int)ad2_1 - (int)lastAd2_1) > DELTA_THRESHOLD ) {
        DPRINT("Coord1  "); DPRINT(SL3_1, HEX); DPRINT(SL4_1, HEX);
        DPRINT("  AD2 = "); DPRINTLN(ad2_1);
      }
      lastAd2_1 = ad2_1;
    }
    // now that we’ve got fresh SL3_1, SL4_1, ad1_1, ad2_1:
    int idx_B = addr_to_index_1(SL3_1, SL4_1);
    if (idx_B >= 0) {
      noses[idx_B] = ad1_1;
      mouths[idx_B] = ad2_1;
    }
  }
  else if ( xbee1.getResponse().isError() ) {
    Serial.print("Coord1 read error: 0x"); Serial.print(SL3_1, HEX); Serial.print(SL4_1, HEX);
    Serial.println(xbee1.getResponse().getErrorCode(), HEX);
  }

// ————— Coordinator D (Serial3) —————
xbee2.readPacket();
if ( xbee2.getResponse().isAvailable()
  && xbee2.getResponse().getApiId() == ZB_IO_SAMPLE_RESPONSE ) {

  xbee2.getResponse().getZBRxIoSampleResponse(sample2);

  // extract SL3_2 & SL4_2
  XBeeAddress64 addr2 = sample2.getRemoteAddress64();
  uint32_t   lsb2     = addr2.getLsb();
  SL3_2 = (lsb2 >> 8) & 0xFF;
  SL4_2 =  lsb2       & 0xFF;

  // AD1 with delta (now using sample2)
  if ( sample2.isAnalogEnabled(1) ) {
    ad1_2 = sample2.getAnalog(1);
    if ( abs((int)ad1_2 - (int)lastAd1_2) > DELTA_THRESHOLD ) {
      DPRINT("Coord2  ");
      DPRINT(SL3_2, HEX); DPRINT(SL4_2, HEX);
      DPRINT("  AD1 = ");  DPRINTLN(ad1_2);
    }
    lastAd1_2 = ad1_2;
  }

  // AD2 with delta
  if ( sample2.isAnalogEnabled(2) ) {
    ad2_2 = sample2.getAnalog(2);
    if ( abs((int)ad2_2 - (int)lastAd2_2) > DELTA_THRESHOLD ) {
      DPRINT("Coord2  ");
      DPRINT(SL3_2, HEX); DPRINT(SL4_2, HEX);
      DPRINT("  AD2 = ");  DPRINTLN(ad2_2);
    }
    lastAd2_2 = ad2_2;
  }

  // now that we’ve got fresh SL3_2, SL4_2, ad1_2, ad2_2:
  int idx_D = addr_to_index_2(SL3_2, SL4_2);
  if (idx_D >= 0) {
    noses[idx_D] = ad1_2;
    mouths[idx_D] = ad2_2;
  }
}
else if (xbee2.getResponse().isError()) {
  Serial.print("Coord2 read error: 0x"); Serial.print(SL3_2, HEX); Serial.print(SL4_2, HEX);
  Serial.println(xbee2.getResponse().getErrorCode(), HEX);
}
  
// Only print & copy if something changed
  if ( arrayChanged(noses, prevNoses, NUM_SENSORS) ) {
    DPRINT("noses ");
    printArray(noses, NUM_SENSORS);
    copyArray(noses, prevNoses, NUM_SENSORS);
  }

  if ( arrayChanged(mouths, prevMouths, NUM_SENSORS) ) {
    DPRINT("mouths ");
    printArray(mouths, NUM_SENSORS);
    copyArray(mouths, prevMouths, NUM_SENSORS);
  }

  delay(10);
  
  actionA();
}

int addr_to_index_1(uint8_t SL3_1, uint8_t SL4_1) {
  // return sensor index for xbees on coordinator B, or -1 if unknown, based on SL3_1/SL4_1 pair
  if (SL3_1 == 0x6B && SL4_1 == 0xFB) return  0;  // 0x422C6BFB // #11
  if (SL3_1 == 0x6D && SL4_1 == 0x6A) return  1;  // 0x422C6D6A // #12
  if (SL3_1 == 0x6D && SL4_1 == 0x1C) return  2;  // 0x422C6D1C // #13
  if (SL3_1 == 0x6D && SL4_1 == 0x53) return  3;  // 0x422C6D53 // #14
  if (SL3_1 == 0x69 && SL4_1 == 0xEF) return  4;  // 0x422C69EF // #15
  return -1;
}

int addr_to_index_2(uint8_t SL3_2, uint8_t SL4_2) {
  // return sensor index for xbees on coordinator D, or -1 if unknown, based on SL3_2/SL4_2 pair
  if (SL3_2 == 0x69 && SL4_2 == 0x2C) return  5;  // 0x422C692C // #16
  if (SL3_2 == 0x69 && SL4_2 == 0x12) return  6;  // 0x422C6912 // #17
  if (SL3_2 == 0x6C && SL4_2 == 0x08) return  7;  // 0x422C6C08 // #18
  if (SL3_2 == 0x6C && SL4_2 == 0xF2) return  8;  // 0x422C6CF2 // #19
  if (SL3_2 == 0x69 && SL4_2 == 0x1A) return  9;  // 0x422C691A // #20
  if (SL3_2 == 0xB9 && SL4_2 == 0x33) return 10;  // 0x4086B933 // #21
  return -1;
}

void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

// -- helper functions -----------------------------------

// returns true if any element differs
template<typename T>
bool arrayChanged(const T arr[], const T prev[], size_t len) {
  for (size_t i = 0; i < len; i++) {
    if (arr[i] != prev[i]) return true;
  }
  return false;
}

// simple element-wise copy
template<typename T>
void copyArray(const T src[], T dest[], size_t len) {
  for (size_t i = 0; i < len; i++) {
    dest[i] = src[i];
  }
}

// prints [v0, v1, …] exactly as before
template<typename T>
void printArray(const T arr[], size_t len) {
  DPRINT("[");
  for (size_t i = 0; i < len; i++) {
    DPRINT(arr[i]);
    if (i < len - 1) DPRINT(", ");
  }
  DPRINTLN("]");
}
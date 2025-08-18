/* SWITCH OFF SERIAL PRINTS FOR CORRECT MIDI COMMUNICATION !!! 
36 MIDI NOTES - from 21 to 56 
we skip 51, because it's not working
*/
#define PUBLISH_DELTA 10
//variables

bool isCapturingA = false;
bool isCapturingB = false;

byte indexB = 0;
uint8_t indexA = 0;

// array to hold xbee frame 0x92 excluding header byte
char inDataA[22];
char inDataB[22];
unsigned long AD1; 
unsigned long AD2;
unsigned long noses[4];  // array to hold 13 values for nose information
unsigned long store_noses[4];
int calib_noses[4];
int calib_nose_times[4];
int nose_switches[4];

int switchOff1 = 0;
int switchOff2 = 0;


unsigned long mouths[4];  // array to hold 13 values for mouth information
unsigned long store_mouths[4];
//unsigned long calib_mouths[13]; 
int calib_mouths[4];
int calib_mouth_times[4];
int mouth_switches[4];

//int controlA[5][4] = { {24, 25, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 18, 19}, {20, 21, 22, 23} };
int controlA[4][4] = { {61,62,63,64},{65,66,67,68},{69,70,71,72},{73,74,75,76} };


int scramble_check[4][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

//int list[] = { 24, 25, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 18, 19, 20, 21, 22, 23 };
// nieuwe miditonenlijst
int list[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20, 21, 22, 23, 24,25,26,27,28,29,30,31,32,33,34,35,36,37};
//62,64,65,67,69,
//70,72,74,75,76
//79,81
//48,50,52,53,54,55
//

const size_t n = sizeof(list) / sizeof(list[0]);


//int controlB[5][4] = { {24,25,26,27},{28,29,30,31},{32,33,34,35},{36,37,38,39},{40,41,42,43} };
long lastDebounceTime = 0;
long timeline = 0;
long timestructure = 4;
int timeswitch = 0;

long maxi = 525;
long mini = 475;

unsigned long publishTime = 0;

/*for the MIDI stuff */
 int velocity = 100;//velocity of MIDI notes, must be between 0 and 127
 int noteON = 144; //144 = 10010000 in binary, note on command
 int noteOFF = 128; //128 = 10000000 in binary, note off command



void setup() {
  // start serial
  Serial2.begin(9600);
  Serial.begin(31250);
  //Serial1.begin;
  //Serial2.begin;

  Serial3.begin(9600);


    for (int i = 21; i < 57; i++)
  {
    MIDImessage(noteOFF, i, velocity);
  }
  //publishTime = millis() + PUBLISH_DELTA;
}
//51,52
void loop() {
  //unsigned long delta = millis();
  // publish values after PUBLISH_DELTA ms have passed

  for (int i = 21; i < 56; i++)
  {
    
    if (i == 51) { // Check if 'x' is within the range to skip
      //Serial.println("skip 51");
      continue;             // Skip the rest of the current iteration
    }
    
    MIDImessage(noteON, i, velocity);
    //MIDImessage(noteON, i, velocity);
    //Serial.println(i);
    //Serial.println(list[i]);
    delay(500);
    MIDImessage(noteOFF, i, velocity);
    //MIDImessage(noteOFF, i, velocity);
    delay(500);
  }

}

void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

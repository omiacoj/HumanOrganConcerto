//#define DEBUG
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
unsigned long noses[5];  // array to hold 13 values for nose information
unsigned long store_noses[5];
int calib_noses[5];
int calib_nose_times[5];
int nose_switches[5];

int switchOff1 = 0;
int switchOff2 = 0;


unsigned long mouths[5];  // array to hold 13 values for mouth information
unsigned long store_mouths[5];
//unsigned long calib_mouths[13];
int calib_mouths[5];
int calib_mouth_times[5];
int mouth_switches[5];

//int controlA[5][4] = { {24, 25, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}, {12, 13, 18, 19}, {20, 21, 22, 23} };
int controlA[5][4] = { {41, 42, 43, 44}, {45, 46, 47, 48}, {49, 50, 51, 52}, {53, 54, 55, 56}, {57, 58, 59, 60} };

//int list[] = { 24, 25, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 18, 19, 20, 21, 22, 23 };
int list[] = { 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60 };
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
  // start serial
  Serial2.begin(9600);
  Serial.begin(31250);

  Serial3.begin(9600);

}

void loop() {
  
  //COORDINATOR A
  while (Serial3.available() > 0 )
  {
    //Serial.print("Serial 3 available");
    char inCharA = Serial3.read();
    //Serial.print(indexA);
    // scan for begin of command character
    // start capturing, we only capture 2 following bytes (id, val)
    if ( (uint8_t)inCharA == 0x7E && indexA == 0) {
      //Serial.print("start");
      //Serial.print(" ");
      //Serial.print("0x7E");
      //Serial.print(" ");
      isCapturingA = true; continue;
    }
    // als we aan het capturen zijn
    if (isCapturingA)
    {
      switch ( (uint8_t)inCharA )
      {
        // received start code in middle of message
        // discard what we've captured so far
        case 0x7E:
          {
            //Serial.print("escape 0x7E");
            //Serial.print(" ");
            isCapturingA = false;
            indexA = 0;
            continue;

            //empty incoming serial buffers
            while (Serial3.available() > 0) {
              char t = Serial3.read();
            }

            while (Serial.available() > 0) {
              char t = Serial.read();
            }
            delay(100);
          }
        // received a valid character
        default:
          {
            //Serial.print(inCharA, HEX);
            //Serial.print(" ");
            if ( (uint8_t)inCharA != 0x7E ) {
              inDataA[indexA] = inCharA; // Store it
            }
            else {
              //Serial.print("end");
              //Serial.print(" ");
              isCapturingA = false;
              // reset for next command
              indexA = 0;
              // parse command
              //parseSerialA();
              while (Serial3.available() > 0) {
                char t = Serial3.read();
              }

              while (Serial.available() > 0) {
                char t = Serial.read();
              }
            }
            indexA++;

            // check if we're at end of command
            if (indexA > 22) {

              //Serial.print("end");
              // Serial.print(" ");
              isCapturingA = false;
              // reset for next command
              indexA = 0;
              // parse command
              parseSerialA();

              while (Serial3.available() > 0) {
                char t = Serial3.read();
              }

              while (Serial.available() > 0) {
                char t = Serial.read();
              }
            }
          }
      }
    }
  } // end serial whilex


  //CONTROLLER C
  while (Serial2.available() > 0 )
  {
    //Serial.print("Serial 2 available");
    char inCharB = Serial2.read();
    //Serial.print(inCharB, HEX);
    //Serial.print("   ");
    //Serial.print(indexB);
    // scan for begin of command character
    // start capturing, we only capture 2 following bytes (id, val)
    if ( (uint8_t)inCharB == 0x7E && indexB == 0) {
      //Serial.print("start B");
      //Serial.print(" ");
      //Serial.print("0x7E");
      //Serial.print(" ");
      isCapturingB = true; continue;
    }

    // als we aan het capturen zijn
    if (isCapturingB)
    {
      //Serial.print("capturing");

      switch ( (uint8_t)inCharB )
      {
        // received start code in middle of message
        // discard what we've captured so far
        case 0x7E:
          {

            //Serial.print("escape 0x7E -- B");
            //Serial.print(" ");
            isCapturingB = false;
            indexB = 0;
            continue;

            //empty incoming serial buffers
            while (Serial2.available() > 0) {
              char t = Serial2.read();
            }

            while (Serial.available() > 0) {
              char t = Serial.read();
            }
            delay(100);
          }
        // received a valid character
        default:
          {

            //Serial.print(inCharA, HEX);
            //Serial.print(" ");

            if ( (uint8_t)inCharB != 0x7E ) {
              inDataB[indexB] = inCharB; // Store it
            }
            else {
              /*
              Serial.print("end");
              Serial.print(" "); */
              isCapturingB = false;
              // reset for next command
              indexB = 0;
              // parse command
              //parseSerialA();


              while (Serial2.available() > 0) {
                char t = Serial2.read();
              }

              while (Serial.available() > 0) {
                char t = Serial.read();
              }
            }

            indexB++;
            //Serial.print(indexB);
            //Serial.print(" ");
            // check if we're at end of command
            if (indexB > 22) {
              //indexB = 0;

              //Serial.print("end");
              //Serial.print(" ");

              isCapturingB = false;
              // reset for next command
              indexB = 0;
              // parse command
              parseSerialC();


              while (Serial2.available() > 0) {
                char t = Serial2.read();
              }

              while (Serial.available() > 0) {
                char t = Serial.read();
              }

            }



          }
      }
    }
  }

  actionA();



}

void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data
}

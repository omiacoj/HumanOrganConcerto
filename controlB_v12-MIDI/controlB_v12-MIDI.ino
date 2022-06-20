;//#define DEBUG
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

int controlA[4][4] = { {61,62,63,64},{65,66,67,68},{69,70,71,72},{73,74,75,76} };

int scramble_check[4][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

int list[] = { 61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76 };

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
 int velocity = 100;
 int noteON = 144; //144 = 10010000 in binary, note on command
 int noteOFF = 128; //128 = 10000000 in binary, note off command



//int controlB[5];
void setup() {
    // start serial 
  Serial2.begin(9600);
  Serial.begin(31250);
  //Serial1.begin;
  //Serial2.begin;
  
  Serial3.begin(9600);
 
}

void loop() {
 //unsigned long delta = millis();
  // publish values after PUBLISH_DELTA ms have passed

/*
     while(Serial2.available() > 0 ) 
  {
     Serial.print("Serial 2 available");
    //char inCharA = Serial3.read();
  }
*/

//FIRST CONTROLLER
      while(Serial3.available() > 0 ) 
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
      isCapturingA = true; continue; }

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
  while(Serial3.available() > 0) {
    char t = Serial3.read();
  }
  
  while(Serial.available() > 0) {
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


  while(Serial3.available() > 0) {
    char t = Serial3.read();
  }
  
  while(Serial.available() > 0) {
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


  while(Serial3.available() > 0) {
    char t = Serial3.read();
  }
  
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
             
            }


            
        }
      }
    }
  } // end serial whilex


//SECOND CONTROLLER
while(Serial2.available() > 0 ) 
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
      isCapturingB = true; continue; }

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
  while(Serial2.available() > 0) {
    char t = Serial2.read();
  }
  
  while(Serial.available() > 0) {
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


  while(Serial2.available() > 0) {
    char t = Serial2.read();
  }
  
  while(Serial.available() > 0) {
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
              parseSerialB();


  while(Serial2.available() > 0) {
    char t = Serial2.read();
  }
  
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
             
            }


            
        }
      }
    }  
  } 
 
actionA();


//SCRAMBLE TIJD in MILLISECONDEN:
timeline = millis() % 55400;
if ( timeline == 0 ) 
{ 

//Serial.print("BANG");
//Serial.println(millis());

timeswitch = 1;

if ( timestructure == 4 )
    { 
      timestructure = 0;
    }
else {
  timestructure = timestructure + 1; 
}

//Serial.print(" timestructure : ");
//Serial.println(timestructure);

if ( timeswitch == 1 ) {


//switch off notes of previous configuration
 for (int x = 0; x < 4; x++ ) {
      for (int y = 0; y < 4; y++ ) {
        if ( scramble_check[x][y] == 1 ) {
          MIDImessage(noteOFF, controlA[x][y], velocity);
          //digitalWrite(controlA[x][y],HIGH);
          scramble_check[x][y] = 0;
          //Serial.print("switched off  :  ");
          //Serial.println(x); Serial.print("    "); Serial.println(y); Serial.print("    ");
        }
      }
  }
      
if ( timestructure == 0 ) 
    {
      
   
    int list[] = { 2,3,4,5,6,7,8,9,10,11,12,13,18,19,24,25 };
    Serial.print("CHROMATIC");
    timeswitch = 0;
    }
    else 
    { 
    Serial.print("SCRAMBLE");

    for (size_t i = 0; i < n - 1; i++)
{
    size_t j = random(0, n - i);

    int t = list[i];
    list[i] = list[j];
    list[j] = t;
}
      timeswitch = 0;
    }

  //check what relays are on and switch them off

  controlA[0][0] = list[0];
  controlA[0][1] = list[1];
  controlA[0][2] = list[2];
  controlA[0][3] = list[3];

  controlA[1][0] = list[4];
  controlA[1][1] = list[5];
  controlA[1][2] = list[6];
  controlA[1][3] = list[7];

  
  controlA[2][0] = list[8];
  controlA[2][1] = list[9];
  controlA[2][2] = list[10];
  controlA[2][3] = list[11];

  controlA[3][0] = list[12];
  controlA[3][1] = list[13];
  controlA[3][2] = list[14];
  controlA[3][3] = list[15];

  delay(1);

}


}

}

void MIDImessage(int command, int MIDInote, int MIDIvelocity) {
  Serial.write(command);//send note on or note off command 
  Serial.write(MIDInote);//send pitch data
  Serial.write(MIDIvelocity);//send velocity data

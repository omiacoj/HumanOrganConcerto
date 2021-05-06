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

int randpin1 = 0;
int randpin2 = 0;
int randpin3 = 0;
int randpin4 = 0;
int randpin5 = 0;


int controlA[4][4] = { {2,3,24,25},{4,5,6,7},{8,9,10,11},{12,13,18,19} };


int scramble_check[4][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };

int list[] = { 2,3,4,5,6,7,8,9,10,11,12,13,18,19,24,25 };

const size_t n = sizeof(list) / sizeof(list[0]);


//int controlB[5][4] = { {24,25,26,27},{28,29,30,31},{32,33,34,35},{36,37,38,39},{40,41,42,43} };
long lastDebounceTime = 0;
long timeline = 0;
long timestructure = 4;
int timeswitch = 0;

long maxi = 525;
long mini = 475;

unsigned long publishTime = 0;


//int controlB[5];
void setup() {
    // start serial 
  //Serial2.begin(9600);
  //Serial.begin(9600);
  //Serial1.begin;
  //Serial2.begin;
  
  //Serial3.begin(9600);
 
    // set digital outputs
  for (int i = 0; i < 26; i++)
  {
    if ( i > 1 ) {
    if ( i < 14 || i > 17 ) {
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
    }
    }
  }
  //publishTime = millis() + PUBLISH_DELTA;
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

while ( true )
  {
   randpin1 = random(0,3);
  randpin2 = random(4,7);
  randpin3 = random(8,11);
  randpin4 = random(12,15);
 
  
  
  digitalWrite(list[randpin1], LOW);
  digitalWrite(list[randpin3], LOW);
  delay(random(2000,6000));
  digitalWrite(list[randpin3], LOW);
  delay(random(1000,3000));
  digitalWrite(list[randpin2], LOW);
  digitalWrite(list[randpin4], LOW);
  delay(random(175,250));
  digitalWrite(list[randpin4], HIGH);
  delay(random(175,250));
  randpin4 = random(12,15);
  digitalWrite(list[randpin4], LOW);
  delay(random(175,250));
  digitalWrite(list[randpin4], HIGH);
  delay(random(175,250));
  randpin4 = random(12,15);
  digitalWrite(list[randpin4], LOW);
  delay(random(175,350));
  digitalWrite(list[randpin4], HIGH);
  delay(random(175,250));
  randpin4 = random(12,15);
  digitalWrite(list[randpin4], LOW);
  delay(random(175,300));
  digitalWrite(list[randpin4], HIGH);
  delay(random(175,250));
  randpin4 = random(12,15);
  digitalWrite(list[randpin4], LOW);
  delay(random(175,350));
  digitalWrite(list[randpin4], HIGH);
  delay(random(175,250));
  randpin4 = random(12,15);
  digitalWrite(list[randpin4], LOW);
  delay(random(175,250));
  digitalWrite(list[randpin4], HIGH);
  delay(random(175,250));

  delay(random(175,1250));
  digitalWrite(list[randpin2], HIGH);
  
  digitalWrite(list[randpin3], HIGH);
  digitalWrite(list[randpin1], HIGH);

  };



}

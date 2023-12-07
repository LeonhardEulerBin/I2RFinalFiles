#include <Adafruit_LIS2MDL.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_LIS2MDL lis2mdl = Adafruit_LIS2MDL(12345);
#define multiplexAdrS0 10
#define multiplexAdrS1 11
#define multiplexAdrS2 12
#define multiplexAdrS3 13

//chips 0-(numChips-1)
int numChips=3;
int chipSelected = 0;
int chipStates[4];
int i = 0;



void initializeChips(Adafruit_LIS2MDL lis2mdl, int numChips);
void select2States(int chipSelected, int numChips);

void setup(void) {
  pinMode(multiplexAdrS0,OUTPUT);
  pinMode(multiplexAdrS1,OUTPUT);
  pinMode(multiplexAdrS2,OUTPUT);
  pinMode(multiplexAdrS3,OUTPUT);

  digitalWrite(multiplexAdrS0,LOW);
  digitalWrite(multiplexAdrS1,LOW);
  digitalWrite(multiplexAdrS2,LOW);
  digitalWrite(multiplexAdrS3,LOW);

  Serial.begin(115200);
  
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  
  initializeChips();
}
  
  


void loop(void) {
  //Serial.println("loop start");
  String dataString = "";
  for (i = 0; i <= (numChips-1); i++) {
  /* Get a new sensor event */
  sensors_event_t event;
  lis2mdl.getEvent(&event);
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) */
  dataString = dataString + event.magnetic.x;
  dataString = dataString + "  ";
  dataString = dataString + event.magnetic.y;
  dataString = dataString + "  ";
  dataString = dataString + ((-1)*event.magnetic.z);
  dataString = dataString + "  ";
  
  select2States();
  //Serial.println(chipStates[0]);
  //Serial.print(chipSelected);
  /* Delay before the next sample */
  }
  Serial.println(dataString);
  //Serial.println("loop end");
}

void initializeChips(){
  //Serial.println("initialize start");
  for (i = 0; i <= (numChips-1); i++) {
    /* Enable auto-gain */
    lis2mdl.enableAutoRange(true);
    //Serial.println("Setup Start");
    while (!lis2mdl.begin()) {}
    
    select2States();
  }
  //Serial.println("initialize end");
}


void select2States(){
  //Serial.println("Select start");
  ++chipSelected;
  chipSelected = chipSelected % numChips;

  chipStates[0] = chipSelected & 1;
  chipStates[1] = (chipSelected & 2) >> 1;
  chipStates[2] = (chipSelected & 4) >> 2;
  chipStates[3] = (chipSelected & 8) >> 3;


  digitalWrite(multiplexAdrS0,chipStates[0]);
  digitalWrite(multiplexAdrS1,chipStates[1]);
  digitalWrite(multiplexAdrS2,chipStates[2]);
  digitalWrite(multiplexAdrS3,chipStates[3]);

  
  delay(50);
  
  //Serial.println("Select end");
}

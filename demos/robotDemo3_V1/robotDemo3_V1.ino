// Intro to Robotics Demo 2
// Author: Ryan Lewis

// initialize libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define NUM_POTENTIOMETERS 4

// initialize motors and shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);



int potPin1 = A8; // Analog input for potentiometer 1
int potPin2 = A9; // Analog input for potentiometer 2
int potPin3 = A10; // Analog input for potentiometer 3
int potPin4 = A11; // Analog input for potentiometer 4

#define NUM_POTENTIOMETERS 4
float pi = 3.14159265;
float potReadings[NUM_POTENTIOMETERS] = {300, 250, 550, 300};
float potRanges[2][NUM_POTENTIOMETERS] = {{0, 514}, {191, 578}, {123, 581}, {269, 420}};
float angleRanges[2][NUM_POTENTIOMETERS] = {{-7*pi/6, 3*pi/4}, {-2*pi/6, 1*pi/2}, {-1*pi/2, 1*pi/2}, {0, 255}};
float angleSets[8][NUM_POTENTIOMETERS] = {{0, 0, pi/2, 0}, {0, pi/4, pi/4, 0}, {0, pi/4, pi/4, 255}, {0, 0, pi/2, 255}, {pi/4, 0, pi/2, 255}, {pi/4, pi/4, pi/4, 255}, {pi/4, pi/4, pi/4, 0}, {pi/4, 0, pi/2, 0}}; // Two sets of desired angles

float potDifferences[NUM_POTENTIOMETERS];
int stateSatisfied = 0;




// Function to calculate the differences between desired and current potentiometer values
void calculatePotDifferences(float potReadings[NUM_POTENTIOMETERS], float potRanges[2][NUM_POTENTIOMETERS],
                             float angleRanges[2][NUM_POTENTIOMETERS], float angleSets[2][NUM_POTENTIOMETERS],
                             int chosenSet, float potDifferences[NUM_POTENTIOMETERS]) {

  for (int i = 0; i < NUM_POTENTIOMETERS; i++) {
    // Extract relevant parameters for the i-th potentiometer
    float minPotRange = potRanges[0][i];
    float maxPotRange = potRanges[1][i];
    float minAngleRange = angleRanges[0][i];
    float maxAngleRange = angleRanges[1][i];
    float desiredAngle = angleSets[chosenSet][i];

    // Map the desired angle to a potentiometer reading within the specified range
    float desiredPotValue = map(desiredAngle, minAngleRange, maxAngleRange, minPotRange, maxPotRange);

    // Calculate the difference between the desired and current potentiometer reading
    potDifferences[i] = desiredPotValue - potReadings[i];
  }
}

// Function to read the pot Values
void potRead() {
  potReadings[1] = analogRead(A8);
  potReadings[2] = analogRead(A9);
  potReadings[3] = analogRead(A10);
  potReadings[4] = analogRead(A11);
}


// Function to set the motor speeds
void motorDrive(int potDifferences[NUM_POTENTIOMETERS]) {
  if (abs(potDifferences[1]) > 0) {
    motor1->setSpeed(potDifferences[1]);
    motor1->run(FORWARD);
  }
  else if (abs(potDifferences[1]) < 0) {
    motor1->setSpeed(potDifferences[1]);
    motor1->run(BACKWARD);
  }

  if (abs(potDifferences[2]) > 0) {
    motor2->setSpeed(potDifferences[2]);
    motor2->run(FORWARD);
  }
  else if (abs(potDifferences[2]) < 0) {
    motor2->setSpeed(potDifferences[2]);
    motor2->run(BACKWARD);
  }

  if (abs(potDifferences[3]) > 0) {
    motor3->setSpeed(potDifferences[3]);
    motor3->run(FORWARD);
  }
  else if (abs(potDifferences[2]) < 0) {
    motor4->setSpeed(potDifferences[4]);
    motor4->run(BACKWARD);
  }

  if (abs(potDifferences[1]) > 0) {
    motor1->setSpeed(potDifferences[1]);
    motor1->run(FORWARD);
  }
  else if (abs(potDifferences[2]) < 0) {
    motor1->setSpeed(potDifferences[1]);
    motor1->run(BACKWARD);
  }
}

// Function to release the motors
void potCheck(int potDifferences[NUM_POTENTIOMETERS]) {
  if (abs(potDifferences[1]) < 5) {
    motor1->run(RELEASE);
  }
  else if (abs(potDifferences[2]) < 5) {
    motor2->run(RELEASE);
  }
  else if (abs(potDifferences[3]) < 5) {
    motor3->run(RELEASE);
  }
  else if (abs(potDifferences[4]) < 5) {
    motor4->run(RELEASE);
  }
  else if (abs(potDifferences[1]) < 5 && abs(potDifferences[2]) < 5 && abs(potDifferences[3]) < 5 && abs(potDifferences[4]) < 5) {
    motor1->run(RELEASE);
    motor2->run(RELEASE);
    motor3->run(RELEASE);
    motor4->run(RELEASE);
    stateSatisfied = 1;
  }

}


void setup() {
  AFMS.begin();  // Initialize with the default frequency 1.6KHz
  // Initialize your arrays with your data
  int potReadings[NUM_POTENTIOMETERS];
  int potRanges[2][NUM_POTENTIOMETERS];
  int angleRanges[2][NUM_POTENTIOMETERS];
  int angleSets[2][NUM_POTENTIOMETERS];
  int chosenSet = 1; // Choose the desired set of angles

  // Call the function to calculate the differences
  int potDifferences[NUM_POTENTIOMETERS];
  


  Serial.begin(9600);
  for (int chosenSet = 0; chosenSet < 8; chosenSet++) {
    while (stateSatisfied = 0) {
      potRead();
      calculatePotDifferences(potReadings, potRanges, angleRanges, angleSets, chosenSet, potDifferences);
      motorDrive(potDifferences[NUM_POTENTIOMETERS]);
      potCheck(potDifferences[NUM_POTENTIOMETERS]);
    }
    stateSatisfied = 0;
  }

}


void loop() {
  
}

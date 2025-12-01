#include <Wire.h>
#include <Adafruit_MotorShield.h>

#define NUM_POTENTIOMETERS 4

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

int potPin1 = A8; // Analog input for potentiometer 1
int potPin2 = A9; // Analog input for potentiometer 2
int potPin3 = A10; // Analog input for potentiometer 3
int potPin4 = A11; // Analog input for potentiometer 4

float pi = 3.14159265;
float potReadings[NUM_POTENTIOMETERS] = {300, 250, 550, 300};
float potRanges[2][NUM_POTENTIOMETERS] = {{218, 191, 123, 269}, {603, 578, 581, 420}};
float angleRanges[2][NUM_POTENTIOMETERS] = {{-pi/2, -2*pi/6, -pi/2, 0}, {pi/2, pi/2, pi/2, 255}};
float angleSets[8][NUM_POTENTIOMETERS] = {
    {0, 0, pi / 2, 0}, {0, pi / 4, pi / 4, 0}, {0, pi / 4, pi / 4, 255}, {0, 0, pi / 2, 255},
    {pi / 4, 0, pi / 2, 255}, {pi / 4, pi / 4, pi / 4, 255}, {pi / 4, pi / 4, pi / 4, 0}, {pi / 4, 0, pi / 2, 0}};
int motorSpeeds = 100;


float potDifferences[NUM_POTENTIOMETERS];
int stateSatisfied = 0;
float threshold = 10;
int chosenSet = 0;

void calculatePotDifferences(float potReadings[NUM_POTENTIOMETERS], float potRanges[2][NUM_POTENTIOMETERS],
                             float angleRanges[2][NUM_POTENTIOMETERS], float angleSets[8][NUM_POTENTIOMETERS],
                             int chosenSet, float potDifferences[NUM_POTENTIOMETERS]) {
  for (int i = 0; i < NUM_POTENTIOMETERS; i++) {
    float minPotRange = potRanges[0][i];
    float maxPotRange = potRanges[1][i];
    float minAngleRange = angleRanges[0][i];
    float maxAngleRange = angleRanges[1][i];
    float desiredAngle = angleSets[chosenSet][i];
    float desiredPotValue = map(desiredAngle, minAngleRange, maxAngleRange, minPotRange, maxPotRange);
    potDifferences[i] = desiredPotValue - potReadings[i];
  }


}

void potRead() {
  potReadings[0] = analogRead(potPin1);
  potReadings[1] = analogRead(potPin2);
  potReadings[2] = analogRead(potPin3);
  potReadings[3] = analogRead(potPin4);

  Serial.print("Pot1 Diff: ");
  Serial.print(potDifferences[0]);
  Serial.print("   ");
  Serial.print("Pot2 Diff: ");
  Serial.print(potDifferences[1]);
  Serial.print("   ");
  Serial.print("Pot3 Diff: ");
  Serial.print(potDifferences[2]);
  Serial.print("   ");
  Serial.print("Pot4 Diff: ");
  Serial.print(potDifferences[3]);
  Serial.print("   ");
  Serial.println(chosenSet);
}

void motorDrive(float potDifferences[NUM_POTENTIOMETERS]) {
  if (abs(potDifferences[0]) > threshold) {
    motor1->setSpeed(motorSpeeds);
    if (potDifferences[0] < 0) {
      motor1->run(FORWARD);
    }
    else {
      motor1->run(BACKWARD);
    }
  } else if (abs(potDifferences[1]) > threshold) {
    motor2->setSpeed(motorSpeeds);
    motor2->run(potDifferences[1] > 0 ? FORWARD : BACKWARD);
  } else if (abs(potDifferences[2]) > threshold) {
    motor3->setSpeed(motorSpeeds);
    motor3->run(potDifferences[2] > 0 ? FORWARD : BACKWARD);
  } else if (abs(potDifferences[3]) > threshold) {
    motor4->setSpeed(motorSpeeds);
    motor4->run(potDifferences[3] > 0 ? FORWARD : BACKWARD);
  } else {
    motor4->run(RELEASE);
  }
}

void potCheck(float potDifferences[NUM_POTENTIOMETERS]) {
  if (abs(potDifferences[0]) < threshold && abs(potDifferences[1]) < threshold && abs(potDifferences[2]) < threshold && abs(potDifferences[3]) < threshold) {
    motor1->run(RELEASE);
    motor2->run(RELEASE);
    motor3->run(RELEASE);
    motor4->run(RELEASE);
    stateSatisfied = 1;
    Serial.println("State Satisfied");
  }
}

void setup() {
  AFMS.begin();
  Serial.begin(9600);

  for (chosenSet = 0; chosenSet < 8; chosenSet++) {
    motor1->run(RELEASE);
    motor2->run(RELEASE);
    motor3->run(RELEASE);
    motor4->run(RELEASE);
    while (stateSatisfied == 0) {
      potRead();
      calculatePotDifferences(potReadings, potRanges, angleRanges, angleSets, chosenSet, potDifferences);
      motorDrive(potDifferences);
      potCheck(potDifferences);
      delay(100);
    }
    stateSatisfied = 0; // Reset stateSatisfied for the next iteration
  }
}

void loop() {
  // Your main loop code here
}

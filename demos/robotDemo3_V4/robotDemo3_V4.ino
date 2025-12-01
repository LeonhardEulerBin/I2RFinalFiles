// Intro to Robotics Demo 2
// Author: Ryan Lewis

// initialize libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>

// initialize motors and shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);
Adafruit_DCMotor *motor2 = AFMS.getMotor(2);
Adafruit_DCMotor *motor3 = AFMS.getMotor(3);
Adafruit_DCMotor *motor4 = AFMS.getMotor(4);

int potPin1 = A8;   // Analog input for potentiometer 1
int potPin2 = A9;   // Analog input for potentiometer 2
int potPin3 = A10;  // Analog input for potentiometer 3
int potPin4 = A11;  // Analog input for potentiometer 4

// adjust run parameters

int globalSpeed = 255;  //0-255
int globalDelay = 0;    //1000=1[sec]
float potReadings[4] = { 100, 100, 100, 100 };


//pickup-dropoff timings (forward and backward timings are the same)



float m1P1 = analogRead(potPin1);
float m1P2 = 420 - 520;
float m2P1 = analogRead(potPin2);
float m2P2 = 560 - 354;
float m3P1 = analogRead(potPin3);
float m3P2 = 530 - 561;
float m4P1 = analogRead(potPin4);
float m4P2 = 425 - 300;
float threshold = 5;

int methodRun = 1;

void dispPots() {
  potReadings[0] = analogRead(potPin1) - m1P1;
  potReadings[1] = analogRead(potPin2) - m2P1;
  potReadings[2] = analogRead(potPin3) - m3P1;
  potReadings[3] = analogRead(potPin4) - m4P1;
  // Print the potentiometer value to the serial monitor
  Serial.print("PV1: ");
  Serial.print(potReadings[0]);
  Serial.print("   ");
  Serial.print("PV2: ");
  Serial.print(potReadings[1]);
  Serial.print("   ");

  Serial.print("PV3: ");
  Serial.print(potReadings[2]);
  Serial.print("   ");

  Serial.print("PV4: ");
  Serial.print(potReadings[3]);
  Serial.println("   ");
}


void move4321to1() {
  methodRun = 1;
  potReadings[0] = analogRead(potPin1) - m1P1;
  potReadings[1] = analogRead(potPin2) - m2P1;
  potReadings[2] = analogRead(potPin3) - m3P1;
  potReadings[3] = analogRead(potPin4) - m4P1;
  dispPots();
  while (methodRun = 1) {
    while (abs(potReadings[3] - m4P1) > threshold) {
      potReadings[3] = analogRead(potPin4);
      motor4->setSpeed(globalSpeed);
      if ((potReadings[3] - m4P1) < 0) {
        motor4->run(FORWARD);
      } else {
        motor4->run(BACKWARD);
      }
    }
    motor4->run(RELEASE);

    while (abs(potReadings[2] - m3P1) > threshold) {
      potReadings[2] = analogRead(potPin3);
      motor3->setSpeed(globalSpeed);
      if ((potReadings[2] - m3P1) < 0) {
        motor3->run(FORWARD);
      } else {
        motor3->run(BACKWARD);
      }
    }
    motor3->run(RELEASE);

    while (abs(potReadings[1] - m2P1) > threshold) {
      potReadings[1] = analogRead(potPin2);
      motor2->setSpeed(globalSpeed);
      if ((potReadings[1] - m2P1) < 0) {
        motor2->run(FORWARD);
      } else {
        motor2->run(BACKWARD);
      }
    }
    motor2->run(RELEASE);

    while (abs(potReadings[0] - m1P1) > threshold) {
      potReadings[0] = analogRead(potPin1);
      motor1->setSpeed(globalSpeed);
      if ((potReadings[0] - m1P1) > 0) {
        motor1->run(FORWARD);
      } else {
        motor1->run(BACKWARD);
      }
    }
    motor1->run(RELEASE);
    methodRun = 0;
    Serial.println("Method move4321to1 Complete");
    dispPots();
    break;
  }
}


void move32to2() {
  methodRun = 1;
  potReadings[0] = analogRead(potPin1) - m1P1;
  potReadings[1] = analogRead(potPin2) - m2P1;
  potReadings[2] = analogRead(potPin3) - m3P1;
  potReadings[3] = analogRead(potPin4) - m4P1;
  while (methodRun = 1) {

    while (abs(potReadings[2] - m3P2) > threshold) {
      potReadings[2] = analogRead(potPin3);
      motor3->setSpeed(globalSpeed);
      if ((potReadings[2] - m3P2) < 0) {
        motor3->run(FORWARD);
      } else {
        motor3->run(BACKWARD);
      }
    }
    motor3->run(RELEASE);

    while (abs(potReadings[1] - m2P2) > threshold) {
      potReadings[1] = analogRead(potPin2);
      motor2->setSpeed(globalSpeed);
      if ((potReadings[1] - m2P2) < 0) {
        motor2->run(FORWARD);
      } else {
        motor2->run(BACKWARD);
      }
    }
    motor2->run(RELEASE);

    methodRun = 0;
    Serial.println("Method move32to2 Complete");
    dispPots();
    break;
  }
}


void move4to2() {
  methodRun = 1;
  potReadings[0] = analogRead(potPin1) - m1P1;
  potReadings[1] = analogRead(potPin2) - m2P1;
  potReadings[2] = analogRead(potPin3) - m3P1;
  potReadings[3] = analogRead(potPin4) - m4P1;
  while (methodRun = 1) {
    while (abs(potReadings[3] - m4P2) > threshold) {
      potReadings[3] = analogRead(potPin4);
      motor4->setSpeed(globalSpeed);
      if ((potReadings[3] - m4P2) < 0) {
        motor4->run(FORWARD);
      } else {
        motor4->run(BACKWARD);
      }
    }
    motor4->run(RELEASE);

    methodRun = 0;
    Serial.println("Method move4to2 Complete");
    dispPots();
    break;
  }
}

void move23to1() {
  methodRun = 1;
  potReadings[0] = analogRead(potPin1) - m1P1;
  potReadings[1] = analogRead(potPin2) - m2P1;
  potReadings[2] = analogRead(potPin3) - m3P1;
  potReadings[3] = analogRead(potPin4) - m4P1;
  while (methodRun = 1) {
    while (abs(potReadings[1] - m2P1) > threshold) {
      potReadings[1] = analogRead(potPin2);
      motor2->setSpeed(globalSpeed);
      if ((potReadings[1] - m2P1) < 0) {
        motor2->run(FORWARD);
      } else {
        motor2->run(BACKWARD);
      }
    }
    motor2->run(RELEASE);

    while (abs(potReadings[2] - m3P1) > threshold) {
      potReadings[2] = analogRead(potPin3);
      motor3->setSpeed(globalSpeed);
      if ((potReadings[2] - m3P1) < 0) {
        motor3->run(FORWARD);
      } else {
        motor3->run(BACKWARD);
      }
    }
    motor3->run(RELEASE);
    methodRun = 0;
    Serial.println("Method move23to1 Complete");
    dispPots();
    break;
  }
}

void move1to2() {
  methodRun = 1;
  potReadings[0] = analogRead(potPin1) - m1P1;
  potReadings[1] = analogRead(potPin2) - m2P1;
  potReadings[2] = analogRead(potPin3) - m3P1;
  potReadings[3] = analogRead(potPin4) - m4P1;
  while (methodRun = 1) {
    while (abs(potReadings[0] - m1P2) > threshold) {
      potReadings[0] = analogRead(potPin1);
      motor1->setSpeed(globalSpeed);
      if ((potReadings[0] - m1P2) > 0) {
        motor1->run(FORWARD);
      } else {
        motor1->run(BACKWARD);
      }
    }
    motor1->run(RELEASE);
    methodRun = 0;
    Serial.println("Method move1to2 Complete");
    dispPots();
    break;
  }
}


void setup() {
  AFMS.begin();  // Initialize with the default frequency 1.6KHz
  Serial.begin(9600);

  move4321to1();
  delay(500);
  move32to2();
  delay(500);
  move4to2();
  delay(500);
  move23to1();
  delay(500);
  move1to2();
  delay(500);
  move32to2();
  delay(500);
  move4321to1();
  delay(500);
}

void loop() {
}

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

// adjust run parameters
int doDemo = 1; //1=true 0=false
int globalSpeed = 255; //0-255
int globalDelay = 0; //1000=1[sec]

//return to zero position timings
int fixM1ForwardTime = 0; //motor1
int fixM2ForwardTime = 0000; //motor2
int fixM3ForwardTime = 0; //motor3
int fixM4ForwardTime = 300; //motor4
int fixM1BackwardTime = 0; //motor1
int fixM2BackwardTime = 1000; //motor2
int fixM3BackwardTime = 000; //motor3
int fixM4BackwardTime = 000; //motor4

//pickup-dropoff timings (forward and backward timings are the same)
int baseRotateTime = 1500; //motor1
int shoulderRotateTime = 1000; //motor2
int wristRotateTime = 1200; //motor3
int gripClampTime = 1000; //motor4

void setup() {
  AFMS.begin();  // Initialize with the default frequency 1.6KHz
  Serial.begin(9600);

  //run return to zero timings
  if (doDemo == 0) {
    motor1->setSpeed(globalSpeed);
    motor1->run(FORWARD);
    delay(fixM1ForwardTime);
    motor1->run(RELEASE);

    motor2->setSpeed(globalSpeed);
    motor2->run(FORWARD);
    delay(fixM2ForwardTime);
    motor2->run(RELEASE);
    
    motor3->setSpeed(globalSpeed);
    motor3->run(FORWARD);
    delay(fixM3ForwardTime);
    motor3->run(RELEASE);

    motor4->setSpeed(globalSpeed);
    motor4->run(FORWARD);
    delay(fixM4ForwardTime);
    motor4->run(RELEASE);

    motor1->setSpeed(globalSpeed);
    motor1->run(BACKWARD);
    delay(fixM1BackwardTime);
    motor1->run(RELEASE);

    motor2->setSpeed(globalSpeed);
    motor2->run(BACKWARD);
    delay(fixM2BackwardTime);
    motor2->run(RELEASE);
    
    motor3->setSpeed(globalSpeed);
    motor3->run(BACKWARD);
    delay(fixM3BackwardTime);
    motor3->run(RELEASE);

    motor4->setSpeed(globalSpeed);
    motor4->run(BACKWARD);
    delay(fixM4BackwardTime);
    motor4->run(RELEASE);
  }

  // run pickup-dropoff sequence
  else {
    // Forward sequence
    // Pickup
    motor2->setSpeed(globalSpeed);
    motor2->run(FORWARD);
    delay(shoulderRotateTime + globalDelay);
    motor2->run(RELEASE);
    
    motor3->setSpeed(globalSpeed);
    motor3->run(FORWARD);
    delay(wristRotateTime + globalDelay);
    motor3->run(RELEASE);

    motor4->setSpeed(globalSpeed);
    motor4->run(FORWARD);
    delay(gripClampTime + globalDelay);
    motor4->run(RELEASE);

    motor3->setSpeed(globalSpeed);
    motor3->run(BACKWARD);
    delay(wristRotateTime + globalDelay);
    motor3->run(RELEASE);
    
    motor2->setSpeed(globalSpeed);
    motor2->run(BACKWARD);
    delay(shoulderRotateTime + globalDelay);
    motor2->run(RELEASE);

    // Move Forward
    motor1->setSpeed(globalSpeed);
    motor1->run(FORWARD);
    delay(baseRotateTime + globalDelay);
    motor1->run(RELEASE);

    // Place
    motor2->setSpeed(globalSpeed);
    motor2->run(FORWARD);
    delay(shoulderRotateTime + globalDelay);
    motor2->run(RELEASE);
    
    motor3->setSpeed(globalSpeed);
    motor3->run(FORWARD);
    delay(wristRotateTime + globalDelay);
    motor3->run(RELEASE);

    motor4->setSpeed(globalSpeed);
    motor4->run(BACKWARD);
    delay(gripClampTime + globalDelay);
    motor4->run(RELEASE);

    motor3->setSpeed(globalSpeed);
    motor3->run(BACKWARD);
    delay(wristRotateTime + globalDelay);
    motor3->run(RELEASE);
    
    motor2->setSpeed(globalSpeed);
    motor2->run(BACKWARD);
    delay(shoulderRotateTime + globalDelay);
    motor2->run(RELEASE);

    // Return To Zero
    motor1->setSpeed(globalSpeed);
    motor1->run(BACKWARD);
    delay(baseRotateTime + globalDelay);
    motor1->run(RELEASE);

  }
}

void loop() {
  
}

#include <Arduino.h>
#include <PathPoints.h>
#include <VarSpeedServo.h>

// Servo instanciation
VarSpeedServo axis[4];

// Base speed
int speed = 75;

// Interval between motors (in ms)
int interval = 500;

void setup() {
  // put your setup code here, to run once:
  // Serial initialization
  Serial.begin(9600);
  while (!Serial) { };

  // Attach servos
  axis[ACTUATOR].attach(9);
  axis[ROTATION].attach(10);
  axis[ELEVATION].attach(11);
  axis[EXTENSION].attach(12);

  // Zero the motors
  axis[ACTUATOR].write(0, speed, true);
  axis[ROTATION].write(90, speed, true);
  axis[ELEVATION].write(30, speed, true);
  axis[EXTENSION].write(120, speed, true);
}

void loop() {
  // put your main code here, to run repeatedly:
}
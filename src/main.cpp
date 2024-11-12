#include <Arduino.h>
#include <PathPoints.hpp>
#include <VarSpeedServo.h>

// Servo instanciation
VarSpeedServo motorX;
VarSpeedServo motorY;
VarSpeedServo motorZ;
VarSpeedServo motorA;

// Initial motor angles
int angleX = 120; 
int angleY = 90; 
int angleZ = 30;
int angleA = 0;

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
  motorX.attach(9);
  motorY.attach(10);
  motorZ.attach(11);
  motorA.attach(12);

  // Zero the motors
  motorX.write(angleX, speed, true);
  motorY.write(angleY, speed, true);
  motorZ.write(angleZ, speed, true);
  motorA.write(angleA, speed, true);
}

void loop() {
  // put your main code here, to run repeatedly:
  int points;
  std::vector<std::vector<int>> angles = setPoints(points);

  for (int point = 0; point < points; point++) {
    Serial.print("Point #");
    Serial.print(point + 1);
    Serial.print(" Angles: X=");
    Serial.print(angles[point][ANGLE_X]);
    Serial.print(", Y=");
    Serial.print(angles[point][ANGLE_Y]);
    Serial.print(", Z=");
    Serial.print(angles[point][ANGLE_Z]);
    Serial.print(", Claw=");
    Serial.println(angles[point][ANGLE_A]);

    motorX.write(angles[point][ANGLE_X], speed, true);
    motorY.write(angles[point][ANGLE_Y], speed, true);
    motorZ.write(angles[point][ANGLE_Z], speed, true);
    motorA.write(angles[point][ANGLE_A], speed, true);
  }

  delay(2000);
}
#include <Arduino.h>
#include <Servo.h>
#include <PathPoints.hpp>

// Servo instanciation
Servo motorX;
Servo motorY;
Servo motorZ;
Servo motorA;

// Initial motor angles
int angleX, angleY = 90; 
int angleZ, angleA = 0;

// Interval between motors (in ms)
int interval = 1000;

// Function declarations
void motorRamp(int& currentAngle, int targetAngle, int motorPin);

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
  motorX.write(angleX);
  motorY.write(angleY);
  motorZ.write(angleZ);
  motorA.write(angleA);
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

    motorRamp(angleX, angles[point][ANGLE_X], 9);
    motorRamp(angleY, angles[point][ANGLE_Y], 10);
    motorRamp(angleZ, angles[point][ANGLE_Z], 11);
    motorRamp(angleA, angles[point][ANGLE_A], 12);
  }

  delay(2000);
}

void motorRamp(int& currentAngle, int targetAngle, int motorPin) {
  int count = 0;

  while (currentAngle != targetAngle) {
    if (currentAngle > targetAngle) currentAngle--;
    else currentAngle++;

    if (count >= 5 || abs(currentAngle - targetAngle) < 5) {
      switch (motorPin) {
        case 9:
          motorX.write(currentAngle);
          break;
        case 10:
          motorY.write(currentAngle);
          break;
        case 11:
          motorZ.write(currentAngle);
          break;
        case 12:
          motorA.write(currentAngle);
          break;
      }

      count = 0;
    }
    delay(30);
  }
}
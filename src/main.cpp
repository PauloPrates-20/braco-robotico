#include <Arduino.h>
#include <Servo.h>
#include <PathPoints.hpp>

// Servo instanciation
Servo motorX;
Servo motorY;
Servo motorZ;
Servo motorA;

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

    motorX.write(angles[point][ANGLE_X]);
    delay(250);
    motorY.write(angles[point][ANGLE_Y]);
    delay(250);
    motorZ.write(angles[point][ANGLE_Z]);
    delay(250);
    motorA.write(angles[point][ANGLE_A]);
    delay(1250);
  }

  delay(5000);
}
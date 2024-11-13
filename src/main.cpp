#include <Arduino.h>
#include <PathPoints.h>
#include <VarSpeedServo.h>

// Servo instanciation
VarSpeedServo axis[4];

// Path instanciation
PathPoints track;

// Base speed
int speed = 75;

// Interval between motors (in ms)
int interval = 500;

// Function declarations
void run(uint8_t repetitions = 1);
void reset();

void setup() {
  // put your setup code here, to run once:
  // Serial initialization
  Serial.begin(9600);
  while (!Serial) { };

  // Attach servos
  axis[ACTUATOR].attach(9);
  axis[ROTATION].attach(10);
  axis[EXTENSION].attach(11);
  axis[ELEVATION].attach(12);

  // Zero the motors
  reset();

  track.setPath();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Repetições: ");
  waitInput();
  uint8_t repeat = Serial.parseInt();
  Serial.println(repeat);
  run(repeat);
}

void run(uint8_t repetitions) {
  for (int repetition = 1; repetition <= repetitions; repetition++) {
    if (track.set) {
      for (uint8_t point = 0; point < track.points; point++) {
        Serial.print("Point #");
        Serial.print(point);
        Serial.print(": ");
        Serial.print("Actuator: ");
        Serial.print(track.path[point][ACTUATOR]);
        Serial.print(" Rotation: ");
        Serial.print(track.path[point][ROTATION]);
        Serial.print(" Extension: ");
        Serial.print(track.path[point][EXTENSION]);
        Serial.print(" Elevation: ");
        Serial.println(track.path[point][ELEVATION]);

        for (uint8_t segment = 0; segment < 4; segment++) {
          byte currentAxis = track.order[point][segment];
          axis[currentAxis].write(track.path[point][currentAxis], speed, true);
        }
      }
    }

    delay(500);
  }
}

void reset() {
  axis[ACTUATOR].write(0, speed, true);
  axis[ROTATION].write(90, speed, true);
  axis[EXTENSION].write(30, speed, true);
  axis[ELEVATION].write(120, speed, true);
}
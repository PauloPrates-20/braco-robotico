#ifndef __PATHPOINTS_HPP__
#define __PATHPOINTS_HPP__

#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>

enum AngleReferences {
    ANGLE_X = 0,
    ANGLE_Y,
    ANGLE_Z,
    ANGLE_A
};

// waits for user input in the serial
inline void waitInput() {
    while(!(Serial.available() > 0)) { };
}

// Sets the angle inside the 2D angles vector
inline void setAngle(std::vector<std::vector<int>>& angleCollection, int point, int angleReference, int angle) {
    angleCollection[point][angleReference] = angle;
}

std::vector<std::vector<int>> setPoints(int& points) {
    Serial.print("Amount of points in the path: ");
    // Wait for input from the user
    while (Serial.available() == 0) {}  // Adjust based on your environment's wait function
    points = Serial.parseInt();  // Reads an integer input from Serial
    Serial.println(points);

    std::vector<std::vector<int>> angles(points, std::vector<int>(4, 0));
    int angleRead;

    for (int point = 0; point < points; point++) {
        Serial.print("\nPoint #");
        Serial.print(point + 1);
        Serial.println(":");

        // Collect angle values for each axis
        Serial.print("Angle X: ");
        waitInput();
        angleRead = Serial.parseInt();
        setAngle(angles, point, ANGLE_X, angleRead);
        Serial.println(angleRead);

        Serial.print("Angle Y: ");
        waitInput();
        angleRead = Serial.parseInt();
        setAngle(angles, point, ANGLE_Y, angleRead);
        Serial.println(angleRead);

        Serial.print("Angle Z: ");
        waitInput();
        angleRead = Serial.parseInt();
        setAngle(angles, point, ANGLE_Z, angleRead);
        Serial.println(angleRead);

        Serial.print("Angle Claw: ");
        waitInput();
        angleRead = Serial.parseInt();
        setAngle(angles, point, ANGLE_A, angleRead);
        Serial.println(angleRead);
    }

    return angles;
}

#endif
#include "PathPoints.h"

// Serial functions
// Waits for user input
void waitInput() {
    while (!(Serial.available() > 0)) { };
}

// Class declarations
// Initializer
PathPoints::PathPoints() {
    set = false;
    points = 0;
    path.resize(points, std::vector<int>(4, 0));
    order.resize(points, std::vector<int>(4, 0));
}

// Function to set the order of operation of the axis in a given point
byte PathPoints::setOrder(uint8_t point, byte segment) {
    Serial.println("(0) - Actuator, (1) - Rotation, (2) - Elevation, (3) - Extension");
    Serial.print("Eixo: ");
    waitInput();
    byte axis = Serial.parseInt();
    order[point][segment] = axis;
    
    switch (axis) {
        case 0:
            Serial.println("Actuator");
            break;
        case 1:
            Serial.println("Rotation");
            break;
        case 2:
            Serial.println("Elevation");
            break;
        case 3:
            Serial.println("Extension");
            break;
    };

    return axis;
}

// Function to set the angle of the axis in a given point
void PathPoints::setAngle(uint8_t point, byte axis) {
    Serial.print("Ângulo: ");
    waitInput();
    uint8_t angle = Serial.parseInt();
    Serial.println(angle);

    path[point][axis] = angle;
}

// Function to trace the path
void PathPoints::setPath() {
    Serial.print("Points in path: ");
    waitInput();
    points = Serial.parseInt();
    Serial.println(points);

    path.resize(points, std::vector<int>(4, 0));
    order.resize(points, std::vector<int>(4, 0));

    for (uint8_t point = 0; point < points; point++) {
        Serial.print("Ponto #");
        Serial.println(point);

        for (byte segment = 0; segment < 4; segment++) {
            byte axis = setOrder(point, segment);
            setAngle(point, axis);
        }
    }

    set = true;
}

// Function to edit the segments of a given point
void PathPoints::editPoint() {
    Serial.print("Point to edit: ");
    waitInput();
    uint8_t point = Serial.parseInt();
    Serial.println(point);

    for (uint8_t segment = 0; segment < 4; segment++) {
        byte axis = setOrder(point, segment);
        setAngle(point, axis);
    }
}
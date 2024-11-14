#include "PathPoints.h"

// Serial functions
// Waits for user input
void waitInput() {
    while (!(Serial.available() > 0)) { };
}

void printOptions(std::vector<std::vector<int>> order, uint8_t point, byte segments) {
    bool actuatorDefined = false;
    bool rotationDefined = false;
    bool elevationDefined = false;
    bool extensionDefined = false;
    bool first = true;

    // Check the order segments for this point for the defined axis
    for (byte segment = 0; segment < segments; segment++) {
        if (order[point][segment] == ACTUATOR) actuatorDefined = true;
        if (order[point][segment] == ROTATION) rotationDefined = true;
        if (order[point][segment] == ELEVATION) elevationDefined = true;
        if (order[point][segment] == EXTENSION) extensionDefined = true;
    }

    // Print the options to the serial
    if (!actuatorDefined) {
        Serial.print("(0) - Actuator");
        first = false;
    } 
    if (!first) Serial.print(" ");
    if (!rotationDefined) {
        Serial.print("(1) - Rotation");
        first = false;
    }
    if (!first) Serial.print(" ");
    if (!elevationDefined) {
        Serial.print("(2) - Elevation");
        first = false;
    }
    if (!first) Serial.print(" ");
    if (!extensionDefined) {
        Serial.print("(3) - Extension");
        first = false;
    }
    Serial.println();
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
    printOptions(order, point, segment);
    Serial.print("Axis: ");
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
    Serial.print("Angle: ");
    waitInput();
    uint8_t angle = Serial.parseInt();
    Serial.println(angle);
    Serial.println();

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
        for (byte segment = 0; segment < 4; segment++) {
            Serial.print("\nPoint: #");
            Serial.print(point + 1);
            Serial.print(" - Segment: #");
            Serial.println(segment + 1);
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
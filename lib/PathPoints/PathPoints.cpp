#include "PathPoints.h"

// Serial functions
// Waits for user input
inline void waitInput() {
    while (!(Serial.available() > 0)) { };
}

// Class declarations
// Initializer
PathPoints::PathPoints() {
    _set = false;
    _points = 0;
    _path.resize(_points, std::vector<int>(4, 0));
    _order.resize(_points, std::vector<int>(4, 0));
}

// Function to set the order of operation of the axis in a given point
byte PathPoints::setOrder(uint8_t point, byte segment) {
    Serial.println("(0) - Atuador, (1) - Rotação, (2) - Elevação, (3) - Extensão");
    Serial.print("Eixo: ");
    waitInput();
    byte axis = Serial.parseInt();
    _order[point][segment] = axis;
    
    switch (axis) {
        case 0:
            Serial.println("Atuador");
            break;
        case 1:
            Serial.println("Rotação");
            break;
        case 2:
            Serial.println("Evelevação");
            break;
        case 3:
            Serial.println("Extensão");
            break;
    };

    return axis;
}

// Returns the current set state for the object
bool PathPoints::isSet() {
    return _set;
}

// Function to set the angle of the axis in a given point
void PathPoints::setAngle(uint8_t point, byte axis) {
    Serial.print("Ângulo: ");
    waitInput();
    uint8_t angle = Serial.parseInt();
    Serial.println(angle);

    _path[point][axis] = angle;
}

// Function to trace the path
void PathPoints::setPath() {
    Serial.print("Points in path: ");
    waitInput();
    _points = Serial.parseInt();
    Serial.println(_points);

    _path.resize(_points, std::vector<int>(4, 0));
    _order.resize(_points, std::vector<int>(4, 0));

    for (uint8_t point = 0; point < _points; point++) {
        Serial.print("Ponto #");
        Serial.println(point);

        for (byte segment = 0; segment < 4; segment++) {
            byte axis = setOrder(point, segment);
            setAngle(point, axis);
        }
    }

    _set = true;
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
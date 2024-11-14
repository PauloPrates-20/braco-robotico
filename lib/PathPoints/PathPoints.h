#ifndef __PATHPOINTS_H__
#define __PATHPOINTS_H__

#include "AxisReference.h"
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>

// Function declarations
// Serial functions
void waitInput(); // Function to wait for user input
void printOptions(std::vector<std::vector<int>> order, uint8_t point, byte segments); // Function to filter the axis options

// Class declarations
class PathPoints {
    public:
        PathPoints();
        void setPath(); // Function to create a path
        void editPoint(); // Function to edit a point within the path
        void setAngle(uint8_t point, byte axis); // Function to set the axis' angles for a given point
        byte setOrder(uint8_t point, byte segment); // Function to set the axis' order for a given point

        uint8_t points;
        std::vector<std::vector<int>> path;
        std::vector<std::vector<int>> order;
        bool set;
};

#endif
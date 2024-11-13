#ifndef __PATHPOINTS_H__
#define __PATHPOINTS_H__

#include "AxisReference.h"
#include <Arduino.h>
#include <ArduinoSTL.h>
#include <vector>

// Function declarations
// Serial functions
inline void waitInput(); // Function to wait for user input

// Class declarations
class PathPoints {
    public:
        PathPoints();
        void setPath(); // Function to create a path
        void editPoint(); // Function to edit a point within the path
        void setAngle(uint8_t point, byte axis); // Function to set the axis' angles for a given point
        byte setOrder(uint8_t point, byte segment); // Function to set the axis' order for a given point
        bool isSet(); // Checks if the path is defined
    
    private:
        std::vector<std::vector<int>> _path;
        std::vector<std::vector<int>> _order;
        uint8_t _points;
        bool _set;
};

#endif
#pragma once

#include "../Point.hpp"
#include <stdio.h>
#include <vector>

typedef Point<double> double2;

class BaseObject {
    private:
        static std::vector<BaseObject*> _objects;   // List of all created objects
        static uint16_t _cur_id;                    // The current max ID

        double2 _rotation;                          // Rotation in radians
        double2 _position;                          // Position in units
        uint16_t _id;                               // Object UUID

        void _assignId();                           // Helper function for assigning an ID

    public:
        BaseObject(double2 pos = double2(), double2 rot = double2());
        BaseObject();

        double2 getPos() { return _position; }
        double2 getRot() { return _rotation; }
        uint16_t getId() { return _id; }
};
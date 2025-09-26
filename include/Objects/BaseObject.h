#pragma once

#include "../Point.hpp"
#include <stdio.h>

typedef Point<double> double2;

class BaseObject {
    private:
        double2 _rotation;          // Rotation in radians
        double2 _position;          // Position in units

        static uint16_t _cur_id;    // The current max ID
        uint16_t _id;               // Object UUID

        void _assignId();           // Helper function for assigning an ID

    public:
        BaseObject(double2 pos, double2 rot = double2());
        BaseObject();

        double2 getPos() { return _position; }
        double2 getRot() { return _rotation; }
        uint16_t getId() { return _id; }
};
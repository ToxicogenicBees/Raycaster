#pragma once;

#include "../Point.hpp"

typedef Point<double> double2;

class BaseObject {
    private:
        double2 _rotation;  // Rotation in radians
        double2 _position;  // Position in units

    public:
        BaseObject();
        BaseObject(double2 pos, double2 rot = double2());
};
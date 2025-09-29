#pragma once

#include "../../Types/Point.hpp"
#include <vector>

namespace {
    using double3 = Point<double>;
}

class PointObject {
    protected:
        double3 _position = double3(0, 0, 0);
    
    public:
        // Base positioning
        virtual void positionAt(const double3& point);
        virtual void translate(const double3& dp);

        // Derived positioning
        void positionAt(double x, double y, double z);
        void translate(double dx, double dy, double dz);
};
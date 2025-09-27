#pragma once

#include "../Point.hpp"
#include <string>
#include <vector>

using double3 = Point<double>;

class Camera {
    private:
        static double3 _look_vec;   // Location the camera points at
        static double3 _up_vec;     // Camera's up vector
        static double3 _pos;        // Position in units
    
    public:
        static void setLookVector(const double3& look_vec);
        static void setPosition(const double3& pos);

        static void castRays(double field_of_view);
        
        static const double3& lookVector() { return _look_vec; }
        static const double3& position() { return _pos; }
};

extern Camera camera;
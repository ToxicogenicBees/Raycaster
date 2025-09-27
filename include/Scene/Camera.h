#pragma once

#include "../Point.hpp"
#include <string>
#include <vector>

using double3 = Point<double>;

class Camera {
    private:
        double3 _look_vec = double3(0, 0, 1);   // Location the camera points at
        double3 _pos = double3(0, 0, 0);        // Position in units

    public:
        Camera(const double3& pos, const double3& look_vector);
        Camera(const double3& pos);
        Camera();

        void setLookVector(const double3& look_vec);
        void setPosition(const double3& pos);

        const double3& view() const { return (_look_vec - _pos).normal(); }
        const double3& lookVector() const { return _look_vec; }
        const double3& position() const { return _pos; }
};
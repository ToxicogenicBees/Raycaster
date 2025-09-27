#pragma once

#include "../Types/Point.hpp"
#include <string>
#include <vector>

using double3 = Point<double>;

class Camera {
    private:
        static double3 _look_vec;       // Location the camera points at
        static double3 _up_vec;         // Camera's up vector
        static double3 _pos;            // Position in units

        static double _field_of_view;    // Vertical FOV in radians
    
    public:
        static void translate(double x, double y, double z);
        static void translate(const double3& pos);

        static void lookAt(double x, double y, double z);
        static void lookAt(const double3& look_vec);

        static void setFOV(double radians);

        static void render(const std::string& image_name);
        
        static const double3& lookVector() { return _look_vec; }
        static const double3& position() { return _pos; }
        static double fov() { return _field_of_view; }
};

extern Camera camera;
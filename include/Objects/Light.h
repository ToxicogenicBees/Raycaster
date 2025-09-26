#pragma once

#include "../Point.hpp"
#include <stdio.h>
#include <vector>

using double3 = Point<double>;

struct ColorChannel {
    double diffusive = 0.5;
    double specular = 0.5;
    double ambient = 0.5;
};

class Light {
    private:
        ColorChannel _int_r, _int_g, _int_b;    // Intensity constants
        double3 _position;                      // Position in units
    
    public:
        static std::vector<Light*> lights;      // List of all created lights

        Light(const double3& pos, const ColorChannel& red_intensity, const ColorChannel& green_intensity, const ColorChannel& blue_intensity);    
        Light(const double3& pos = double3(), const ColorChannel& intensity = ColorChannel());

        const ColorChannel& red() const { return _int_r; }
        const ColorChannel& green() const { return _int_g; }
        const ColorChannel& blue() const { return _int_b; }

        const double3& getPos() const { return _position; }
};
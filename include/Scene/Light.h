#pragma once

#include "../Rendering/Reflectance.h"
#include "../Types/Point.hpp"
#include <stdio.h>
#include <vector>

using double3 = Point<double>;

class Light {
    private:
        Intensity _int_r, _int_g, _int_b;       // Intensity constants
        double3 _pos;                           // Position in units
    
    public:
        static std::vector<Light*> lights;      // List of all created lights

        Light(const double3& pos, const Intensity& red_intensity, const Intensity& green_intensity, const Intensity& blue_intensity);    
        Light(const double3& pos = double3(), const Intensity& intensity = Intensity());

        const Intensity& red() const { return _int_r; }
        const Intensity& green() const { return _int_g; }
        const Intensity& blue() const { return _int_b; }

        const double3& position() const { return _pos; }
};
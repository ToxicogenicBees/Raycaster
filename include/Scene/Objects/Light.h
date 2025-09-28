#pragma once

#include "../../Types/Point.hpp"
#include "../../Types/Color.h"
#include <vector>

using double3 = Point<double>;

struct Light {
    double3 position = double3(0, 0, 0);    // Position in units
    Color color = Colors::WHITE;            // Light's color
    
    double diffusion = 1;                   // Diffusion intensity
    double specular = 1;                    // Specular intensity

    void translate(double dx, double dy, double dz);
    void translate(const double3& dp);
};
#pragma once

#include "../Rendering/Color.h"
#include "../Types/Point.hpp"
#include <vector>

using double3 = Point<double>;

struct Light {
    static std::vector<Light*> lights;  // List of all created lights
    static double ambient_intensity;    // Default ambient intensity

    double diffusion = 1;               // Diffusion intensity
    double specular = 1;                // Specular intensity

    Color color = Colors::WHITE;        // Light's color
    double3 position;                   // Position in units
    
    Light();

    void translate(double dx, double dy, double dz);
    void translate(const double3& dp);
};
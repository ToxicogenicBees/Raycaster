#pragma once

#include "../Types/Point.hpp"
#include <stdio.h>
#include <vector>

using double3 = Point<double>;

struct Intensity {
    double diffusion = 1;
    double specular = 1;
};

struct Light {
    static std::vector<Light*> lights;  // List of all created lights
    static double ambient_intensity;    // Default ambient intensity

    Intensity int_r, int_g, int_b;      // Intensity constants
    double3 position;                   // Position in units
    
    Light(const double3& pos, const Intensity& red_intensity, const Intensity& green_intensity, const Intensity& blue_intensity);    
    Light(const double3& pos = double3(), const Intensity& intensity = Intensity());

    void translate(double dx, double dy, double dz);
    void translate(const double3& dp);
};
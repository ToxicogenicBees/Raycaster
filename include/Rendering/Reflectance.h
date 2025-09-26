#pragma once

struct Reflectance {
    double diffusive = 0.5;
    double specular = 0.5;
    double ambient = 0.5;
};

using Intensity = Reflectance;
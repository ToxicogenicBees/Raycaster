#include "../../include/Scene/Light.h"

double Light::ambient_intensity = 0.1;
std::vector<Light*> Light::lights;

Light::Light(const double3& pos, const Intensity& red_intensity, const Intensity& green_intensity, const Intensity& blue_intensity) {
    int_r = red_intensity;
    int_g = green_intensity;
    int_b = blue_intensity;
    position = pos;

    lights.push_back(this);
}

Light::Light(const double3& pos, const Intensity& intensity) {
    int_r = int_g = int_b = intensity;
    position = pos;

    lights.push_back(this);
}

void Light::translate(double x, double y, double z) {
    position.x += x;
    position.y += y;
    position.z += z;
}

void Light::translate(const double3& dp) {
    position += dp;
}
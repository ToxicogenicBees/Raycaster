#include "../../include/Scene/Light.h"

double Light::ambient_intensity = 0.1;
std::vector<Light*> Light::lights;

Light::Light() {
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
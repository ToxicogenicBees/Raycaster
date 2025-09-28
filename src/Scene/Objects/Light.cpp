#include "../../../include/Scene/Objects/Light.h"

void Light::translate(double x, double y, double z) {
    position.x += x;
    position.y += y;
    position.z += z;
}

void Light::translate(const double3& dp) {
    position += dp;
}
#include "../../include/Objects/Light.h"

std::vector<Light*> Light::lights;

Light::Light(const double3& pos, const Intensity& red_intensity, const Intensity& green_intensity, const Intensity& blue_intensity) {
    _int_r = red_intensity;
    _int_g = green_intensity;
    _int_b = blue_intensity;
    _pos = pos;

    lights.push_back(this);
}

Light::Light(const double3& pos, const Intensity& intensity) {
    _int_r = _int_g = _int_b = intensity;
    _pos = pos;
}
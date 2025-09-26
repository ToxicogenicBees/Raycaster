#include "../../include/Objects/Light.h"

std::vector<Light*> Light::lights;

Light::Light(const double3& pos, const ColorChannel& red_intensity, const ColorChannel& green_intensity, const ColorChannel& blue_intensity) {
    _int_r = ColorChannel(red_intensity);
    _int_g = ColorChannel(green_intensity);
    _int_b = ColorChannel(blue_intensity);
    _position = double3(pos);

    lights.push_back(this);
}

Light::Light(const double3& pos, const ColorChannel& intensity) {
    _int_r = _int_g = _int_b = ColorChannel(intensity);
    _position = double3(pos);
}
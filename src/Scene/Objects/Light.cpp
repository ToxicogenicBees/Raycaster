#include "../../../include/Scene/Objects/Light.h"

void Light::setColor(const Color& color) {
    _color = color;
}

void Light::setDiffusion(double diffusion) {
    _diffusion = diffusion;
}

void Light::setSpecular(double specular) {
    _specular = specular;
}
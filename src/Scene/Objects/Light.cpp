#include "../../../include/Scene/Objects/Light.h"

void Light::setColor(const Color& color) {
    _color = color;
}

void Light::setColor(double r, double g, double b) {
    _color = Color(r, g, b);
}

void Light::setDiffusion(double diffusion) {
    _diffusion = diffusion;
}

void Light::setSpecular(double specular) {
    _specular = specular;
}
#include "../../../include/Scene/Objects/Light.h"
#include "../../../include/Scene/Scene.h"

Light::Light() {
    Scene::addObject(this);
}

Light::~Light() {
    Scene::removeObject(this);
}

void Light::positionAt(const double3& point) {
    _position = point;
}

void Light::positionAt(double x, double y, double z) {
    positionAt(double3(x, y, z));
}

void Light::translate(const double3& dp) {
    _position += dp;
}

void Light::translate(double dx, double dy, double dz) {
    translate(double3(dx, dy, dz));
}

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
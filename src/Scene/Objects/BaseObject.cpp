#include "../../../include/Scene/Objects/BaseObject.h"
#include "../../../include/Scene/Transformations.h"
#include "../../../include/Scene/Scene.h"

BaseObject::BaseObject() {
    Scene::addObject(this);
}

BaseObject::~BaseObject() {
    Scene::removeObject(this);
}

void BaseObject::translate(const double3& dp) {
    Matrix<double> translation = Transformations::translation(dp);

    for (double3& point : _points)
        Transformations::apply(translation, point);
}

void BaseObject::translate(double dx, double dy, double dz) {
    translate(double3(dx, dy, dz));
}

void BaseObject::scale(const double3& s) {
    Matrix<double> scaling = Transformations::scale(s);

    for (double3& point : _points)
        Transformations::apply(scaling, point);
}

void BaseObject::scale(double sx, double sy, double sz) {
    scale(double3(sx, sy, sz));
}

void BaseObject::scale(const double s) {
    scale(s, s, s);
}

void BaseObject::rotate(const double3& r) {
    rotate(r.x, r.y, r.z);
}

void BaseObject::rotate(double rx, double ry, double rz) {
    Matrix<double> rotX = Transformations::rotateX(rx);
    Matrix<double> rotY = Transformations::rotateY(ry);
    Matrix<double> rotZ = Transformations::rotateZ(rz);
    Matrix<double> rotation = rotZ * rotY * rotX;

    for (double3& point : _points)
        Transformations::apply(rotation, point);
}

void BaseObject::setColor(const Color& color) {
    _color = color;
}

void BaseObject::setColor(double r, double g, double b) {
    _color = Color(r, g, b);
}

void BaseObject::setReflectance(double reflectance) {
    _reflectance = reflectance;
}

void BaseObject::setTransparency(double transparency) {
    _transparency = transparency;
}

void BaseObject::setDiffusion(double diffusion) {
    _diffusion = diffusion;
}

void BaseObject::setShininess(double shininess) {
    _shininess = shininess;
}

void BaseObject::setSpecular(double specular) {
    _specular = specular;
}

void BaseObject::setAmbience(double ambience) {
    _ambience = ambience;
}

Intersection::Intersection(const BaseObject* obj, double3 pos, double3 normal) {
    this->obj = obj;
    this->pos = pos;
    this->normal = normal;
}

Intersection::Intersection() {
    obj = nullptr;
}
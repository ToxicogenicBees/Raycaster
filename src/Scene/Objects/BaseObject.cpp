#include "../../../include/Scene/Objects/BaseObject.h"
#include "../../../include/Scene/Transformations.h"

std::vector<BaseObject*> BaseObject::objects;

BaseObject::BaseObject() {
    objects.push_back(this);
}

void BaseObject::rotate(double rx, double ry, double rz) {
    auto rotX = Transformations::rotateX(rx);
    auto rotY = Transformations::rotateY(ry);
    auto rotZ = Transformations::rotateZ(rz);
    auto rotation = rotZ * rotY * rotX;

    for (double3& point : _points)
        Transformations::apply(rotation, point);
}

void BaseObject::rotate(const double3& r) {
    rotate(r.x, r.y, r.z);
}

void BaseObject::translate(double dx, double dy, double dz) {
    auto translation = Transformations::translation(dx, dy, dz);

    for (double3& point : _points)
        Transformations::apply(translation, point);
}

void BaseObject::translate(const double3& dp) {
    translate(dp.x, dp.y, dp.z);
}

void BaseObject::scale(double sx, double sy, double sz) {
    auto scaling = Transformations::scale(sx, sy, sz);

    for (double3& point : _points)
        Transformations::apply(scaling, point);
}

void BaseObject::scale(const double3& s) {
    scale(s.x, s.y, s.z);
}

void BaseObject::scale(const double s) {
    scale(s, s, s);
}

void BaseObject::setReflectance(const Reflectance& ref) {
    _ref = ref;
}

void BaseObject::setColor(const Color& color) {
    _color = color;
}

Intersection::Intersection(const BaseObject* obj, double3 pos, double3 normal) {
    this->obj = obj;
    this->pos = pos;
    this->normal = normal;
}

Intersection::Intersection() {
    obj = nullptr;
}
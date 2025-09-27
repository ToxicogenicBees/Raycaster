#include "../../../include/Scene/Objects/BaseObject.h"

std::vector<BaseObject*> BaseObject::objects;

BaseObject::BaseObject(const std::string& type) : _TYPE(type) {
    objects.push_back(this);
}

void BaseObject::translate(double x, double y, double z) {
    _pos = double3(x, y, z);
}

void BaseObject::translate(const double3& pos) {
    _pos = pos;
}

void BaseObject::rotate(double x, double y, double z) {
    _rot = double3(x, y, z);
}

void BaseObject::rotate(const double3& rot) {
    _rot = rot;
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
#include "../../../include/Scene/Objects/BaseObject.h"

Intersection::Intersection(BaseObject* obj, double3 pos, double3 normal) {
    this->obj = obj;
    this->pos = pos;
    this->normal = normal;
}

Intersection::Intersection() {
    obj = nullptr;
}

std::vector<BaseObject*> BaseObject::objects;

BaseObject::BaseObject(const std::string& type, const double3& pos, const double3& rot, const Reflectance& ref) : _TYPE(type) {
    objects.push_back(this);

    _pos = pos;
    _ref = ref;
    _rot = rot;
}

BaseObject::BaseObject(const std::string& type, const double3& pos, const Reflectance& ref) : _TYPE(type) {
    objects.push_back(this);

    _pos = pos;
    _ref = ref;
}

BaseObject::BaseObject(const std::string& type, const Reflectance& ref) : _TYPE(type) {
    objects.push_back(this);

    _ref = ref;
}

BaseObject::BaseObject(const std::string& type, const double3& pos) : _TYPE(type) {
    objects.push_back(this);

    _pos = pos;
}

BaseObject::BaseObject(const std::string& type) : _TYPE(type) {
    objects.push_back(this);
}

void BaseObject::setPosition(const double3& pos) {
    _pos = pos;
}

void BaseObject::setReflectance(const Reflectance& ref) {
    _ref = ref;
}

void BaseObject::setRotation(const double3& rot) {
    _rot = rot;
}
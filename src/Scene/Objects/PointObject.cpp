#include "../../../include/Scene/Objects/PointObject.h"

void PointObject::positionAt(const double3& point) {
    _position = point;
}

void PointObject::positionAt(double x, double y, double z) {
    positionAt(double3(x, y, z));
}

void PointObject::translate(const double3& dp) {
    _position += dp;
}

void PointObject::translate(double dx, double dy, double dz) {
    translate(double3(dx, dy, dz));
}
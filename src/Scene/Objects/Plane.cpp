#include "../../../include/Scene/Objects/Plane.h"
#include <cmath>

namespace {
    constexpr const uint16_t NORMAL = 0;
    constexpr const uint16_t ORIGIN = 1;
}

Plane::Plane(double3 normal, double3 origin) {
    _points.push_back(normal.normal());     // Insert normal vector "point" for plane
    _points.push_back(origin);              // Insert distance "point" for plane
}

Plane::Plane(double3 origin) {
    _points.push_back(double3(0, 0, 1));    // Insert normal vector "point" for plane
    _points.push_back(origin);              // Insert distance "point" for plane
}

void Plane::translate(double dx, double dy, double dz) {
    BaseObject::translate(dx, dy, dz);
    _points[NORMAL] = _points[NORMAL].normal();
}

void Plane::rotate(double rx, double ry, double rz) {
    BaseObject::rotate(rx, ry, rz);
    _points[NORMAL] = _points[NORMAL].normal();
}

void Plane::scale(double sx, double sy, double sz) {
    BaseObject::scale(sx, sy, sz);
    _points[NORMAL] = _points[NORMAL].normal();
}

Intersection Plane::findIntersection(const double3& start, const double3& dir) const {
    double n_dot_v = _points[NORMAL].dot(dir);

    // If the ray is parallel to the plane (n_dot_v is zero, with some tolerance for f-p error), return invalid intersection
    if (std::fabs(n_dot_v) < 1e-8) return Intersection();

    // Find "time" of intersection
    double t = -_points[NORMAL].dot(start - _points[ORIGIN]) / n_dot_v;

    // If the intersection is behind the ray, return invalid intersection
    if (t < 0) return Intersection();

    // Return the proper intersection
    double3 intersectionNormal = n_dot_v > 0 ? -_points[NORMAL] : _points[NORMAL];
    double3 intersection = start + t * dir;

    return Intersection(this, intersection, intersectionNormal);
}
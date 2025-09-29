#include "../../../include/Scene/Objects/Plane.h"
#include <cmath>

namespace {
    constexpr const uint16_t ORIGIN = 0;
    constexpr const uint16_t NORMAL = 1;
}

Plane::Plane(double3 normal, double distance) {
    double3 true_normal = normal.normal();
    points.push_back(true_normal * distance);   // Insert distance "point" for plane
    points.push_back(true_normal);              // Insert normal vector "point" for plane
}

Plane::Plane(double distance) {
    points.push_back(double3(0, 0, distance));  // Insert distance "point" for plane
    points.push_back(double3(0, 0, 1));         // Insert normal vector "point" for plane
}

void Plane::translate(double dx, double dy, double dz) {
    BaseObject::translate(dx, dy, dz);
    points[NORMAL] = points[NORMAL].normal();
}

void Plane::rotate(double rx, double ry, double rz) {
    BaseObject::rotate(rx, ry, rz);
    points[NORMAL] = points[NORMAL].normal();
}

void Plane::scale(double sx, double sy, double sz) {
    BaseObject::scale(sx, sy, sz);
    points[NORMAL] = points[NORMAL].normal();
}

Intersection Plane::findIntersection(const double3& start, const double3& view_dir) const {
    // https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#SECTION00023500000000000000
    
    double n_dot_v = points[NORMAL].dot(view_dir);

    // Ray is parallel to the plane if n_dot_v is 0. Return invalid intersection.
    if (std::fabs(n_dot_v) < 1e-8) return Intersection();

    // Find time of intersection
    double t = points[NORMAL].dot(points[ORIGIN] - start) / n_dot_v;

    // Ray intersects plane behind if t < 0, return invalid intersection
    if (t < 0) return Intersection();

    // Return the proper intersection
    double3 intersectionNormal = n_dot_v > 0 ? -points[NORMAL] : points[NORMAL];
    double3 intersection = start + t * view_dir;

    return Intersection(this, intersection, intersectionNormal);
}
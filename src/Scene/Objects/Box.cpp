#include "../../../include/Scene/Transformations.h"
#include "../../../include/Scene/Objects/Box.h"
#include "../../../include/Scene/Scene.h"
#include <stdint.h>
#include <algorithm>
#include <cmath>

namespace {
    const double ERR = 1e-8;
    const uint16_t CENTER = 0;
    const uint16_t U = 1;
    const uint16_t V = 2;
    const uint16_t W = 3;
}

double safeDivision(double num, double den) {
    return (std::fabs(den) < ERR) ? ((num > 0) ? +INFINITY : -INFINITY) : (num / den);
}

void Box::_renormalize_axis() {
    _points[U] = _points[U].normal();
    _points[V] = _points[V].normal();
    _points[W] = _points[W].normal();
}

Box::Box(const double3 c1, const double3 c2) {
    _points.push_back((c1 + c2) / 2);   // Center of the box

    _points.push_back({1, 0, 0});       // u-direction vector
    _points.push_back({0, 1, 0});       // v-direction vector
    _points.push_back({0, 0, 1});       // w-direction vector

    _half_size = double3(
        std::fabs((c2.x - c1.x) / 2),
        std::fabs((c2.y - c1.y) / 2),
        std::fabs((c2.z - c1.z) / 2)
    );
}

Intersection Box::findIntersection(const Ray& ray) const {
    // Axis-Aligned Bounding Box collision detection

    // Transform ray to OOB local space
    double3 origin_prime(
        _points[U].dot(ray.origin - _points[CENTER]),
        _points[V].dot(ray.origin - _points[CENTER]),
        _points[W].dot(ray.origin - _points[CENTER])
    );

    double3 dir_prime(
        _points[U].dot(ray.dir),
        _points[V].dot(ray.dir),
        _points[W].dot(ray.dir)
    );

    // Run OOB calculations
    double3 t1 = double3(
        safeDivision(-_half_size.x - origin_prime.x, dir_prime.x),
        safeDivision(-_half_size.y - origin_prime.y, dir_prime.y),
        safeDivision(-_half_size.z - origin_prime.z, dir_prime.z)
    );

    double3 t2 = double3(
        safeDivision(_half_size.x - origin_prime.x, dir_prime.x),
        safeDivision(_half_size.y - origin_prime.y, dir_prime.y),
        safeDivision(_half_size.z - origin_prime.z, dir_prime.z)
    );

    if (t1.x > t2.x) std::swap(t1.x, t2.x);
    if (t1.y > t2.y) std::swap(t1.y, t2.y);
    if (t1.z > t2.z) std::swap(t1.z, t2.z);

    double t_entry = std::max({t1.x, t1.y, t1.z});
    double t_exit = std::min({t2.x, t2.y, t2.z});

    // If t_entry > t_exit, the ray misses
    // If t_exit < 0, the box is behind the ray
    if (t_entry > t_exit || t_exit < 0)
        return Intersection();

    // Translate back to world space
    double t_hit = (t_entry >= 0) ? t_entry : t_exit;
    double3 hit_point = ray.origin + t_hit * ray.dir;
    
    double3 normal;
    if (std::fabs(t_hit - t1.x) < ERR)
        normal = (dir_prime.x > 0 ? -_points[U] : _points[U]);
    else if (std::fabs(t_hit - t1.y) < ERR)
        normal = (dir_prime.y > 0 ? -_points[V] : _points[V]);
    else if (std::fabs(t_hit - t1.z) < ERR)
        normal = (dir_prime.z > 0 ? -_points[W] : _points[W]);
    else if (std::fabs(t_hit - t2.x) < ERR)
        normal = (dir_prime.x > 0 ? _points[U] : -_points[U]);
    else if (std::fabs(t_hit - t2.y) < ERR)
        normal = (dir_prime.y > 0 ? _points[V] : -_points[V]);
    else
        normal = (dir_prime.z > 0 ? _points[W] : -_points[W]);

    // Return intersection
    return Intersection(this, hit_point, normal);
}

void Box::translate(const double3& dp) {
    Matrix<double> translation = Transformations::translation(dp);
    Transformations::apply(translation, _points[CENTER]);
}

void Box::rotate(const double3& r) {
    BaseObject::rotate(r);
    _renormalize_axis();
}

void Box::scale(const double3& s) {
    BaseObject::scale(s);
    _renormalize_axis();
    _half_size *= s;
}
#include "../../../include/Scene/Objects/Polygon.h"
#include <cmath>

namespace {
    const double ERR = 1e-8;
}

double3 Polygon::_normal() const {
    return (_points[2] - _points[1]).cross(_points[0] - _points[1]).normal();
}

Intersection Polygon::findIntersection(const Ray& ray) const {
    // https://www.cl.cam.ac.uk/teaching/1999/AGraphHCI/SMAG/node2.html#SECTION00023600000000000000
    
    /*---------------------------------------------------------------------
        First, determine if the ray intersects the plane of the polygon
    ---------------------------------------------------------------------*/

    double3 normal = _normal();

    // Extra check: if normal's magnitude is 0, the polygon is invalid
    if (normal.magnitude() < ERR)
        return Intersection();

    double n_dot_v = normal.dot(ray.dir);

    // Ray is parallel to the plane if n_dot_v is 0. Return invalid intersection.
    if (std::fabs(n_dot_v) < 1e-8) return Intersection();

    // Find time of intersection
    double t = normal.dot(_points[0] - ray.origin) / n_dot_v;

    // Ray intersects plane behind if t < 0, return invalid intersection
    if (t < 0) return Intersection();

    // Calculate the proper intersection
    double3 intersectionNormal = n_dot_v > 0 ? -normal : normal;
    double3 intersection = ray.origin + t * ray.dir;

    Intersection calculated_intersection = Intersection(this, intersection, intersectionNormal);

    /*-----------------------------------------------------------
        Then, determine if this point lies within the polygon
    -----------------------------------------------------------*/

    // Project polygon onto the XY-plane
    double3 u;
    for (size_t i = 1; i < _points.size(); ++i) {
        u = _points[i] - _points[0];
        if (u.magnitude() > ERR && std::fabs(normal.dot(u)) > ERR)
            break;
    }

    u = u.normal();
    double3 v = (normal.cross(u)).normal();

    std::vector<double3> flat_points;
    for (double3 p : _points) {
        flat_points.push_back(double3(
            (p - _points[0]).dot(u),
            (p - _points[0]).dot(v),
            0
        ));
    }

    // Project intersection point
    double3 proj_inter = double3((calculated_intersection.pos - _points[0]).dot(u), (calculated_intersection.pos - _points[0]).dot(v), 0);

    // Run an odd/even test on the polygon
    bool inside = false;
    double3 a, b;

    for (size_t i = 0; i < flat_points.size(); i++) {
        // Get current point and previous point around the polygon
        b = flat_points[(i == 0) ? flat_points.size() - 1 : i - 1];
        a = flat_points[i];

        // If this point is a vertex, it is on the shape
        if (std::abs(proj_inter.x -a.x) < ERR && std::abs(proj_inter.y - a.y) < ERR)
            return calculated_intersection;

        if ((a.y > proj_inter.y) != (b.y > proj_inter.y)) {
            double slope = (proj_inter.x - a.x) * (b.y - a.y) - (b.x - a.x) * (proj_inter.y - a.y);

            // Point is directly on the edge (slope == 0)
            if (std::abs(slope) < ERR)
                return calculated_intersection;
            
            // Toggle state
            if ((slope < 0) != (b.y < a.y))
                inside = !inside;
        }
    }

    // Return results
    return (inside ? calculated_intersection : Intersection());
}
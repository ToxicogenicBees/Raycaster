#include "../../../include/Scene/Objects/PolygonMesh.h"

Intersection PolygonMesh::findIntersection(const Ray& ray) const {
    // Iterate over each object, store closest intersection
    Intersection closest_inter;

    for (Polygon* p : _polygons) {
        // Attempt to intersect a ray with this object
        Intersection new_inter = p->findIntersection(ray);
        
        // If the intersection succeeded, and is the closest thus far, mark it
        if (new_inter.obj && !closest_inter.obj)
            closest_inter = new_inter;
        else if (new_inter.obj && (ray.origin - new_inter.pos).squaredMagnitude() < (ray.origin - closest_inter.pos).squaredMagnitude()) {
            closest_inter = new_inter;
        }
    }

    // Return intersection, if one was found
    if (closest_inter.obj)
        closest_inter.obj = this;
    return closest_inter;
}

void PolygonMesh::translate(const double3& dp) {
    for (Polygon* p : _polygons)
        p->translate(dp);
}

void PolygonMesh::rotate(const double3& r) {
    for (Polygon* p : _polygons)
        p->rotate(r);
}

void PolygonMesh::scale(const double3& s) {
    for (Polygon* p : _polygons)
        p->scale(s);
}
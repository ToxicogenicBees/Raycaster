#pragma once

#include "../../Rendering/Color.h"
#include "../../Types/Point.hpp"
#include <string>
#include <vector>

// Forward declaration of intersection struct
struct Intersection;

namespace {
    using double3 = Point<double>;
}

struct BaseObject {
    // Object's points
    std::vector<double3> points;                // Vector of related points for this object
    
    // Reflection variables
    Color color = Colors::WHITE;                // Object's color
    double diffusion = 0.6;                     // Diffusion reflection
    double shininess = 20;                      // Shininess coefficient
    double specular = 0.9;                      // Specular reflection
    double ambient = 0.1;                       // Ambient reflection

    virtual Intersection findIntersection(const double3& start, const double3& view_dir) const = 0;

    // Base translations
    virtual void translate(double dx, double dy, double dz);
    virtual void rotate(double rx, double ry, double rz);
    virtual void scale(double sx, double sy, double sz);

    // Derived translations
    void rotate(const double3& r);
    void scale(const double3& s);
    void scale(const double s);
    void translate(const double3& dp);
};

struct Intersection {
    double3 pos, normal;
    const BaseObject* obj;

    Intersection(const BaseObject* obj, double3 pos, double3 normal);
    Intersection();
};
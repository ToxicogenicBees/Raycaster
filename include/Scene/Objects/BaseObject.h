#pragma once

#include "../../Rendering/Reflectance.h"
#include "../../Rendering/Color.h"
#include "../../Types/Point.hpp"
#include <string>
#include <vector>

namespace {
    using double3 = Point<double>;
    using Points = std::vector<double3>;
}

struct Intersection;

class BaseObject {
    protected:
        std::vector<double3> _points;   // Vector of related points for this object
        Color _color = Colors::WHITE;   // Object's color
        Reflectance _ref;               // Object's reflectance coefficients

    public:
        static std::vector<BaseObject*> objects;    // List of all created objects

        virtual Intersection findIntersection(const double3& start, const double3& dir) const = 0;

        BaseObject();

        void setReflectance(const Reflectance& ref);
        void setColor(const Color& color);

        // Base translations
        virtual void translate(double dx, double dy, double dz);
        virtual void rotate(double rx, double ry, double rz);
        virtual void scale(double sx, double sy, double sz);

        // Derived translations
        void rotate(const double3& r);
        void scale(const double3& s);
        void scale(const double s);
        void translate(const double3& dp);
        
        const double3& point(uint16_t index) const { return _points[index]; }
        const std::vector<double3>& points() const { return _points; }
        const Reflectance& reflectance() const { return _ref; }
        const Color& color() const { return _color; }
};

struct Intersection {
    double3 pos, normal;
    const BaseObject* obj;

    Intersection(const BaseObject* obj, double3 pos, double3 normal);
    Intersection();
};
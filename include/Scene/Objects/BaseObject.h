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
        const std::string _TYPE;        // Object type
        
        std::vector<double3> _points;   // Vector of related points for this object
        Reflectance _ref;               // Object's reflectance coefficients
        Color _color;                   // Object's color

    public:
        static std::vector<BaseObject*> objects;    // List of all created objects

        BaseObject(const std::string& type);

        virtual Intersection findIntersection(const double3& start, const double3& dir) const = 0;

        void setReflectance(const Reflectance& ref);
        void setColor(const Color& color);

        void rotate(double rx, double ry, double rz);
        void rotate(const double3& r);
        void scale(double sx, double sy, double sz);
        void scale(const double3& s);
        void scale(const double s);
        void translate(double dx, double dy, double dz);
        void translate(const double3& dp);
        
        const double3& point(uint16_t index) const { return _points[index]; }
        const std::vector<double3>& points() const { return _points; }
        const Reflectance& reflectance() const { return _ref; }
        const std::string& type() const { return _TYPE; }
        const Color& color() const { return _color; }
};

struct Intersection {
    double3 pos, normal;
    const BaseObject* obj;

    Intersection(const BaseObject* obj, double3 pos, double3 normal);
    Intersection();
};
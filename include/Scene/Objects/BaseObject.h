#pragma once

#include "../../Rendering/Reflectance.h"
#include "../../Rendering/Color.h"
#include "../../Types/Point.hpp"
#include <string>
#include <vector>

using double3 = Point<double>;

struct Intersection;

class BaseObject {
    protected:
        const std::string _TYPE;    // Object type

        double3 _pos, _rot;         // Position/rotation in units/radians
        Reflectance _ref;           // Object's reflectance coefficients
        Color _color;               // Object's color

    public:
        static std::vector<BaseObject*> objects;    // List of all created objects

        BaseObject(const std::string& type);

        virtual Intersection findIntersection(const double3& start, const double3& dir) const = 0;

        void setReflectance(const Reflectance& ref);
        void setColor(const Color& color);

        void translate(double x, double y, double z);
        void translate(const double3& pos);
        
        void rotate(double x, double y, double z);
        void rotate(const double3& rot);

        const Reflectance& reflectance() const { return _ref; }
        const std::string& type() const { return _TYPE; }
        const double3& position() const { return _pos; }
        const double3& rotation() const { return _rot; }
        const Color& color() const { return _color; }
};

struct Intersection {
    double3 pos, normal;
    const BaseObject* obj;

    Intersection(const BaseObject* obj, double3 pos, double3 normal);
    Intersection();
};
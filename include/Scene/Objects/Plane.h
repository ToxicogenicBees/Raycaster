#pragma once

#include "BaseObject.h"

class Plane : public BaseObject {
    public:
        Plane(double3 normal, double distance);
        Plane(double distance);

        void translate(double dx, double dy, double dz) override;
        void rotate(double rx, double ry, double rz) override;
        void scale(double sx, double sy, double sz) override;

        Intersection findIntersection(const double3& start, const double3& dir) const override;
};
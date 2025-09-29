#pragma once

#include "BaseObject.h"

class Sphere : public BaseObject {
    public:
        friend class PhongShading;

        /**
         * @brief Creates a sphere centered at the origin, with the desired radius
         * 
         * @param radius    The radius of the sphere
        */
        Sphere(double radius);

        /**
         * @brief Finds the intersection between a camera's view ray and this object, if one exists
         * 
         * @param start     The origin of the view ray
         * @param view_dir  The direction of the view ray
         * 
         * @return An intersection object containing the results of the intersection calculation
         */
        Intersection findIntersection(const double3& start, const double3& view_dir) const override;
};
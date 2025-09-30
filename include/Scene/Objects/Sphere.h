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
         * @brief Finds the intersection between a view ray and this object, if one exists
         * 
         * @param ray   The view ray
         * 
         * @return An intersection object containing the results of the intersection calculation
         */
        Intersection findIntersection(const Ray& ray) const override;
};
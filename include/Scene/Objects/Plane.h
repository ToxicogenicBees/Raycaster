#pragma once

#include "BaseObject.h"

class Plane : public BaseObject {
    public:
        using BaseObject::translate;
        using BaseObject::rotate;
        using BaseObject::scale;

        friend class PhongShading;

        /**
         * @brief Creates a plane defined by a normal vector and a distance from the origin along that vector
         * 
         * @param normal    The desired normal vector
         * @param distance  The desired distance
         */
        Plane(const double3& normal, double distance);

        /**
         * @brief Creates a plane defined by the unit-z axis, and a distance from the origin along the z-axis
         * 
         * @param normal    The desired normal vector
         * @param distance  The desired distance
         */
        Plane(double distance);

         /**
         * @brief Destroys and removes the plane from the scene
        */
        ~Plane() = default;
        
        /**
         * @brief Finds the intersection between a view ray and this object, if one exists
         * 
         * @param ray   The view ray
         * 
         * @return An intersection object containing the results of the intersection calculation
         */
        Intersection findIntersection(const Ray& ray) const override;

        /**
         * @brief Translates the object by a desired (x, y, z) distance
         * 
         * @param dp    The desired position change
         */
        void translate(const double3& dp) override;

        /**
         * @brief Rotates the object by a desired (x, y, z) angle, in radians
         * 
         * @param r     The desired rotation change
         */
        void rotate(const double3& r) override;

        /**
         * @brief Scales the object by a desired (x, y, z) scale
         * 
         * @param s     The desired scale
         */
        void scale(const double3& s) override;
};
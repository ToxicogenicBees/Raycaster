#pragma once

#include "BaseObject.h"
#include "Polygon.h"

class Box : public BaseObject {
    private:
        double3 _half_size;

        void _renormalizeAxis();

    public:
        using BaseObject::translate;
        using BaseObject::rotate;
        using BaseObject::scale;
        
        friend class PhongShading;

        /**
         * @brief Creates a box with the two specified corners
         * 
         * @param c1    One corner of the box
         * @param c2    The opposite corner of the box
        */
        Box(const double3 c1, const double3 c2);

        /**
         * @brief Destroys and removes the box from the scene
        */
        ~Box() = default;

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
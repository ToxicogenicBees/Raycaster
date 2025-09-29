#pragma once

#include "../../Types/Point.hpp"

namespace {
    using double3 = Point<double>;
}

class PointObject {
    protected:
        // The position of the object
        double3 _position = double3(0, 0, 0);
    
    public:
        friend class PhongShading;
        
        /***
         * @brief Places the object at a desired (x, y, z) position
         * 
         * @param point The desired position
         */
        virtual void positionAt(const double3& point);

        /***
         * @brief Places the object at a desired (x, y, z) position
         * 
         * @param x    The desired x-position
         * @param y    The desired y-position
         * @param z    The desired z-position
         */
        void positionAt(double x, double y, double z);

        /***
         * @brief Translates the object by a desired (x, y, z) distance
         * 
         * @param dp   The desired position change
         */
        virtual void translate(const double3& dp);

        /***
         * @brief Translates the object by a desired (x, y, z) distance
         * 
         * @param dx   The desired x-position change
         * @param dy   The desired y-position change
         * @param dz   The desired z-position change
         */
        void translate(double dx, double dy, double dz);
};
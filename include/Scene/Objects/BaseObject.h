#pragma once

#include "../../Rendering/Color.h"
#include "../../Types/Point.hpp"
#include <vector>

// Forward declaration of intersection struct
struct Intersection;

namespace {
    using double3 = Point<double>;
}

class BaseObject {
    protected:
        // Object's points
        std::vector<double3> _points;   // Vector of related points for this object
        
        // Reflection variables
        Color _color = Colors::WHITE;   // Object's color
        double _diffusion = 0.6;        // Diffusion reflection
        double _shininess = 20;         // Shininess coefficient
        double _specular = 0.9;         // Specular reflection
        double _ambience = 0.1;         // Ambient reflection

    public:
        friend class PhongShading;

        /**
         * @brief Finds the intersection between a camera's view ray and this object, if one exists
         * 
         * @param start     The origin of the view ray
         * @param view_dir  The direction of the view ray
         * 
         * @return An intersection object containing the results of the intersection calculation
         */
        virtual Intersection findIntersection(const double3& start, const double3& view_dir) const = 0;

        /**
         * @brief Translates the object by a desired (x, y, z) distance
         * 
         * @param dp    The desired position change
         */
        virtual void translate(const double3& dp);

        /**
         * @brief Translates the object by a desired (x, y, z) distance
         * 
         * @param x     The desired x-position change
         * @param y     The desired y-position change
         * @param z     The desired z-position change
         */
        void translate(double dx, double dy, double dz);

        /**
         * @brief Scales the object by a desired (x, y, z) scale
         * 
         * @param s     The desired scale
         */
        virtual void scale(const double3& s);
        
        /**
         * @brief Scales the object by a desired (x, y, z) scale
         * 
         * @param sx    The desired x-scale
         * @param sy    The desired y-scale
         * @param sz    The desired z-scale
         */
        void scale(double sx, double sy, double sz);

        /**
         * @brief Scales the object by a desired uniform scale
         * 
         * @param s     The desired uniform scale
         */
        void scale(const double s);

        /**
         * @brief Rotates the object by a desired (x, y, z) angle, in radians
         * 
         * @param r     The desired rotation change
         */
        virtual void rotate(const double3& r);

        /**
         * @brief Rotates the object by a desired (x, y, z) angle, in radians
         * 
         * @param rx    The desired x-rotation change
         * @param ry    The desired y-rotation change
         * @param rz    The desired z-rotation change
         */
        void rotate(double rx, double ry, double rz);

        /**
         * @brief Sets the color of the object
         * 
         * @param color     The desired color
         */
        void setColor(const Color& color);

        /**
         * @brief Sets the diffusion of the object
         * 
         * @param diffusion The desired diffusion
         */
        void setDiffusion(double diffusion);

        /**
         * @brief Sets the shininess of the object
         * 
         * @param shininess The desired shininess
         */
        void setShininess(double shininess);

        /**
         * @brief Sets the specular of the object
         * 
         * @param specular  The desired specular
         */
        void setSpecular(double specular);

        /**
         * @brief Sets the ambience of the object
         * 
         * @param ambience  The desired ambience
         */
        void setAmbience(double ambience);
};

struct Intersection {
    double3 pos, normal;    // Position of and normal vector at the intersection point
    const BaseObject* obj;  // Pointer to the object the intersection is for, or nullptr if it's invalid

    /**
     * @brief Creates a valid intersection object
     * 
     * @param obj       Pointer to the object being intersected
     * @param pos       The position of the intersection
     * @param normal    The surface normal at the point of intersection
    */
    Intersection(const BaseObject* obj, double3 pos, double3 normal);

    /**
     * @brief Creates an invalid intersection object, with the object pointer set to nullptr
    */
    Intersection();
};
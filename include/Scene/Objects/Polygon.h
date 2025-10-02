#pragma once

#include "BaseObject.h"

class Polygon : public BaseObject {
    private:
        // Calculate the normal of the polygon
        double3 _normal() const;

    public:
        friend class PhongShading;
        friend class Box;
        
        /**
         * @brief Creates a polygon from the provided points
         * 
         * @param points    A list of the points forming this polygon
        */
        template<typename... Points>
        Polygon(Points&&... points) {
            (_points.push_back(points), ...);
        }

        /**
         * @brief Destroys and removes the polygon from the scene
         */
        ~Polygon() = default;

        /**
         * @brief Finds the intersection between a view ray and this object, if one exists
         * 
         * @param ray   The view ray
         * 
         * @return An intersection object containing the results of the intersection calculation
         */
        Intersection findIntersection(const Ray& ray) const override;
};
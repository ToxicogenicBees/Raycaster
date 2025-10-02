#pragma once

#include "BaseObject.h"
#include "../Scene.h"
#include "Polygon.h"

class PolygonMesh : public BaseObject {
    private:
        std::vector<Polygon*> _polygons;

    public:
        using BaseObject::translate;
        using BaseObject::rotate;
        using BaseObject::scale;

        friend class PhongShading;

        /**
         * @brief Constructs a mesh of polygons
         * 
         * @param polygons  List of polygons in the mesh
         */
        template<typename... Polygons>
        PolygonMesh(Polygons&&... polygons) : BaseObject() {
            (_polygons.push_back(&polygons), ...);
            (Scene::removeObject(&polygons), ...);
        }
        
        /**
         * @brief Constructs a mesh of polygons
         * 
         * @param polygons  List of pointers to polygons in the mesh
         */
        template<typename... Polygons>
        PolygonMesh(Polygons*... polygons) : BaseObject() {
            (_polygons.push_back(polygons), ...);
            (Scene::removeObject(polygons), ...);
        }

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
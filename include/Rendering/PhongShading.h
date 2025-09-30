#pragma once

#include "../Scene/BasicObjects.h"
#include "FrameBuffer.h"
#include <string>

class PhongShading {
    private:
        static uint16_t _MAX_RECURSIVE_DEPTH;   // Maximum recursive ray depth
        static FrameBuffer _frame_buffer;        // The frame buffer used to store pixel data

        // Finds the closest intersection with an object on a specified ray
        static Intersection _closestIntersectionOnRay(const Ray& ray);

        // Determines if a light ray is obstructed by an object
        static bool _lightRayObstructed(Light* light, const Intersection& intersection);

        // Calculate the reflection vector between a vector and a normal vector
        static double3 _reflectionBetween(const double3& vec, const double3& normal);

        // Recursive Phong shading
        static Color _recursiveI(const Intersection& intersection, const Ray& view_ray, uint16_t depth = 0);

        // Regular Phong shading
        static Color _regularI(const Intersection& intersection, const Ray& view_ray);

        // Rendering helper function
        static void _render(const std::string& file_name, bool use_recursive_shading);

    public:
        /***
         * @brief Renders the current Scene using recursive Phong shading
         *        and outputs to a file
         * 
         * @param file_name The name the file should output to
         */
        static void renderWithRecursiveShading(const std::string& file_name);

        /***
         * @brief Renders the current Scene using simple Phong shading
         *        and outputs to a file
         * 
         * @param file_name The name the file should output to
         */
        static void renderWithSimpleShading(const std::string& file_name);
};
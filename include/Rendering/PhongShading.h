#pragma once

#include "../Scene/BasicObjects.h"
#include "FrameBuffer.h"
#include <string>

class PhongShading {
    private:
        static uint8_t _MAX_RECURSIVE_DEPTH;    // Maximum recursive ray depth
        static FrameBuffer _frame_buffer;       // The frame buffer used to store pixel data

        // Ray manipulations
        static Intersection _closestIntersectionOnRay(const Ray& ray);
        static std::vector<Intersection> _allIntersectionsOnRay(const Ray& ray);
        static double3 _reflectionBetween(const double3& vec, const double3& normal);

        // Phong Reflection Model Calculations
        static Color _recursiveI(const Intersection& intersection, const Ray& view_ray, uint8_t depth = 0);
        static Color _regularI(const Intersection& intersection, const Ray& view_ray);

        // Rendering helpers
        static void _renderStrip(Camera* camera, size_t scan_line_start, size_t scan_line_end, bool use_recursive_shading);
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
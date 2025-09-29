#pragma once

#include "../Scene/BasicObjects.h"
#include "FrameBuffer.h"
#include "Color.h"
#include <string>

class PhongShading {
    private:
        // The frame buffer used to store pixel data
        static FrameBuffer _frameBuffer;

        // Finds the object intersecting the view ray through a pixel for a specific camera
        static Intersection _findIntersectionAt(Camera* camera, uint16_t x, uint16_t y);

        // Recursive Phong shading
        static Color _recursiveI();

        // Regular Phong shading
        static Color _regularI(Camera* camera, const Intersection& intersection);

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
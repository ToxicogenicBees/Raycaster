#pragma once

#include "../Scene/BasicObjects.h"
#include "../Scene/Scene.h"
#include "FrameBuffer.h"
#include "Color.h"
#include <string>

class PhongShading {
    private:
        static FrameBuffer _frameBuffer;

        static void _initFrameBuffer();
        static void _initRender();

        static Intersection _findIntersectionAt(Camera* camera, uint16_t x, uint16_t y);

    public:
        static Color recursiveI(Camera* camera, const Intersection& intersection);
        static Color regularI(Camera* camera, const Intersection& intersection);

        static void renderWithRecursiveShading(const std::string& file_name);
        static void renderWithSimpleShading(const std::string& file_name);
};
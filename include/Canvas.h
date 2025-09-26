#pragma once

#include "Buffer.hpp"
#include "Color.h"
#include <string>

class Canvas {
    private:
        static Buffer<Color>* _frame_buffer;
        static uint16_t _size_x, _size_y;

    public:
        static void resize(uint16_t size_x, uint16_t size_y);
        static void render(const std::string& image_name);

        static void setPixel(uint16_t x, uint16_t y, const Color& color);
        static void fill(const Color& color);

        static uint16_t sizeX() { return _size_x; }
        static uint16_t sizeY() { return _size_y; }
};

extern Canvas canvas;
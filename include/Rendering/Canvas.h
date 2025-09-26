#pragma once

#include "../Vector2.hpp"
#include "../Color.h"
#include <string>

class Canvas {
    private:
        static Vector2<Color> _frame_buffer;

    public:
        static void outputToFile(const std::string& image_name);
        
        static void setPixel(uint16_t x, uint16_t y, const Color& color);

        static void resize(uint16_t size_x, uint16_t size_y) { _frame_buffer.resize(size_x, size_y); }
        static void resize(const Point<uint16_t>& size) { _frame_buffer.resize(size); }
        static void fill(const Color& color) { _frame_buffer.fill(color); }
        static uint16_t sizeX() { return _frame_buffer.sizeX(); }
        static uint16_t sizeY() { return _frame_buffer.sizeY(); }
};

extern Canvas canvas;

namespace ImageSize {
    extern const Point<uint16_t> SIZE_1080x1080;
    extern const Point<uint16_t> SIZE_1024x768;
    extern const Point<uint16_t> SIZE_1600x1200;
    extern const Point<uint16_t> SIZE_1920x1080;
    extern const Point<uint16_t> SIZE_3840x2160;
    extern const Point<uint16_t> SIZE_2560x1080;
    extern const Point<uint16_t> SIZE_1080x1920;
    extern const Point<uint16_t> SIZE_1280x1024;
    extern const Point<uint16_t> SIZE_2000x1000;
}
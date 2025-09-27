#pragma once

#include <stdint.h>

struct Color {
    uint8_t r, g, b;

    Color(uint8_t r, uint8_t g, uint8_t b);
    Color(double r, double g, double b);
    Color(const Color& color);
    Color(uint32_t hex);
    Color();

    Color& operator=(const Color& color);
};

namespace Colors {
    extern const Color RED;
    extern const Color ORANGE;
    extern const Color YELLOW;
    extern const Color GREEN;
    extern const Color CYAN;
    extern const Color BLUE;
    extern const Color PURPLE;
    extern const Color WHITE;
    extern const Color BLACK;
}
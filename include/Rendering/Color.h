#pragma once

#include <stdint.h>

struct Color {
    double r, g, b;

    Color(double r, double g, double b);
    Color(const Color& color);
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
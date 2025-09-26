#include "../include/Color.h"

namespace Colors {
    const Color RED(255, 0, 0);
    const Color ORANGE(255, 127, 0);
    const Color YELLOW(255, 255, 0);
    const Color GREEN(0, 255, 0);
    const Color CYAN(0, 255, 255);
    const Color BLUE(0, 0, 255);
    const Color PURPLE(255, 0, 255);
    const Color WHITE(255, 255, 255);
    const Color BLACK(0, 0, 0);
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(uint32_t hex) {
    r = (hex & 0x00FF0000) >> 16;
    g = (hex & 0x0000FF00) >> 8;
    b = (hex & 0x000000FF);
}

Color::Color() {
    r = g = b = 0;
}

Color& Color::operator=(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    return *this;
}
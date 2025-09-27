#include "../include/Rendering/Color.h"
#include <cmath>

namespace Colors {
    const Color RED     (1.0, 0.0, 0.0);
    const Color ORANGE  (1.0, 0.5, 0.0);
    const Color YELLOW  (1.0, 1.0, 0.0);
    const Color GREEN   (0.0, 1.0, 0.0);
    const Color CYAN    (0.0, 1.0, 1.0);
    const Color BLUE    (0.0, 0.0, 1.0);
    const Color PURPLE  (1.0, 0.0, 1.0);
    const Color WHITE   (1.0, 1.0, 1.0);
    const Color BLACK   (0.0, 0.0, 0.0);
}

Color::Color(uint8_t r, uint8_t g, uint8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(double r, double g, double b) {
    this->r = floor(255 * r);
    this->g = floor(255 * g);
    this->b = floor(255 * b);
}

Color::Color(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
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
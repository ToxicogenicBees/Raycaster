#include "../../include/Rendering/Color.h"
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

Color::Color(double r, double g, double b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::Color(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
}

Color::Color() {
    r = g = b = 0.0;
}

Color& Color::operator=(const Color& color) {
    r = color.r;
    g = color.g;
    b = color.b;
    return *this;
}
#include "../../include/Rendering/FrameBuffer.h"
#include <algorithm>
#include <iostream>
#include <fstream>

color FrameBuffer::_gammaCorrection(const color& color) const{
    return color(
        std::clamp(std::pow(color.x, 1.0 / 2.2), 0.0, 1.0),
        std::clamp(std::pow(color.y, 1.0 / 2.2), 0.0, 1.0),
        std::clamp(std::pow(color.z, 1.0 / 2.2), 0.0, 1.0)
    );
}

void FrameBuffer::outputToFile(const std::string& image_name) const {
    std::ofstream img((image_name + ".ppm").c_str(), std::ios::binary);

    if (!img.is_open()) {
        std::cout << "Failed to create " << image_name << ".ppm\n";
        return;
    }

    // File header: P6 = binary RGB
    img << "P6\n" << sizeX() << " " << sizeY() << "\n255\n";

    // Write pixel data
    color corrected_color;

    for (size_t y = 0; y < sizeY(); y++) {
        for (size_t x = 0; x < sizeX(); x++) {
            corrected_color = _gammaCorrection(_buffer(x, y));
            img.put(std::round(255 * corrected_color.x));
            img.put(std::round(255 * corrected_color.y));
            img.put(std::round(255 * corrected_color.z));
        }
    }

    img.close();
}

void FrameBuffer::setPixel(size_t x, size_t y, const color& color) {
    _buffer(x, y) = color;
}

void FrameBuffer::resize(size_t size_x, size_t size_y) {
    _buffer.resize(size_x, size_y);
}

void FrameBuffer::fill(const color& color) {
    _buffer.fill(color);
}
#include "../../include/Rendering/FrameBuffer.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>

namespace ImageSize {
    const Point<uint16_t> SIZE_1080x1080(1080, 1080);
    const Point<uint16_t> SIZE_1024x768(1024, 768);
    const Point<uint16_t> SIZE_1600x1200(1600, 1200);
    const Point<uint16_t> SIZE_1920x1080(1920, 1080);
    const Point<uint16_t> SIZE_3840x2160(3840, 2160);
    const Point<uint16_t> SIZE_2560x1080(2560, 1080);
    const Point<uint16_t> SIZE_1080x1920(1080, 1920);
    const Point<uint16_t> SIZE_1280x1024(1280, 1024);
    const Point<uint16_t> SIZE_2000x1000(2000, 1000);
}

Vector2<Color> FrameBuffer::_buffer(ImageSize::SIZE_1080x1080);
FrameBuffer frameBuffer;

void FrameBuffer::_gammaCurrection() {
    for (uint16_t y = 0; y < sizeY(); y++) {
        for (uint16_t x = 0; x < sizeX(); x++) {
            // Gamma correction
            _buffer[y][x].r = std::clamp(std::pow(_buffer[y][x].r, 1.0 / 2.2), 0.0, 1.0);
            _buffer[y][x].g = std::clamp(std::pow(_buffer[y][x].g, 1.0 / 2.2), 0.0, 1.0);
            _buffer[y][x].b = std::clamp(std::pow(_buffer[y][x].b, 1.0 / 2.2), 0.0, 1.0);
        } 
    }
}

void FrameBuffer::outputToFile(const std::string& image_name) {
    std::ofstream img((image_name + ".ppm").c_str(), std::ios::binary);

    if (!img.is_open()) {
        std::cout << "Failed to create image " << image_name << std::endl;
        return;
    }

    // File header: P6 = binary RGB
    img << "P6\n" << sizeX() << " " << sizeY() << "\n255\n";

    // Image processing
    _gammaCurrection();

    // Write pixel data
    for (uint16_t y = 0; y < sizeY(); y++) {
        for (uint16_t x = 0; x < sizeX(); x++) {
            img.put(255 * _buffer[y][x].r);
            img.put(255 * _buffer[y][x].g);
            img.put(255 * _buffer[y][x].g);
        }
    }

    img.close();
}

void FrameBuffer::setPixel(uint16_t x, uint16_t y, const Color& color) {
    _buffer[y][x] = color;
}
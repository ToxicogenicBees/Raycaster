#include "../../include/Rendering/FrameBuffer.h"
#include <iostream>
#include <fstream>

Vector2<Color> FrameBuffer::_buffer(300, 200);
FrameBuffer frameBuffer;

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

void FrameBuffer::outputToFile(const std::string& image_name) {
    std::ofstream img((image_name + ".ppm").c_str(), std::ios::binary);

    if (!img.is_open()) {
        std::cerr << "Failed to create image file\n";
        return;
    }

    // File header: P6 = binary RGB
    img << "P6\n" << sizeX() << " " << sizeY() << "\n255\n";

    // Write pixel data
    for (uint16_t y = 0; y < sizeY(); y++) {
        for (uint16_t x = 0; x < sizeX(); x++) {
            unsigned char rgb[3] = {
                _buffer[y][x].r,
                _buffer[y][x].g,
                _buffer[y][x].b
            };
            
            img.write(reinterpret_cast<char*>(rgb), 3);
        }
    }

    img.close();
    std::cout << "New image file created: " << image_name << ".ppm\n";
}

void FrameBuffer::setPixel(uint16_t x, uint16_t y, const Color& color) {
    _buffer[y][x] = color;
}
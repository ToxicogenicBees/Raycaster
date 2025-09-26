#include "../include/Canvas.h"
#include <iostream>
#include <fstream>

uint16_t Canvas::_size_x = 100;
uint16_t Canvas::_size_y = 100;

Buffer<Color>* Canvas::_frame_buffer = new Buffer<Color>(_size_x, _size_y);

Canvas canvas;

void Canvas::resize(uint16_t size_x, uint16_t size_y) {
    delete _frame_buffer;

    _size_x = size_x;
    _size_y = size_y;

    _frame_buffer = new Buffer<Color>(size_x, size_y);

    std::cout << "Canvas resized\n";
}

void Canvas::fill(const Color& color) {
    _frame_buffer->fill(color);
}

void Canvas::setPixel(uint16_t x, uint16_t y, const Color& color) {
    (*_frame_buffer)[y][x] = color;
}

void Canvas::render(const std::string& image_name) {
    std::cout << "Dumping image\n";
    std::ofstream img((image_name + ".ppm").c_str(), std::ios::binary);

    if (!img.is_open()) {
        std::cerr << "Failed to create image file\n";
        return;
    }

    // File header: P6 = binary RGB
    img << "P6\n" << _size_x << " " << _size_y << "\n255\n";

    // Write pixel data
    for (uint16_t y = 0; y < _size_y; y++) {
        for (uint16_t x = 0; x < _size_x; x++) {
            unsigned char rgb[3] = {
                (*_frame_buffer)[y][x].r,
                (*_frame_buffer)[y][x].g,
                (*_frame_buffer)[y][x].b
            };
            
            img.write(reinterpret_cast<char*>(rgb), 3);
        }
    }


    img.close();
    std::cout << "New image file created: " << image_name << ".ppm\n";
}
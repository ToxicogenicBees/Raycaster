#pragma once

#include "../Rendering/Color.h"
#include "../Types/Vector2.hpp"
#include <string>

class FrameBuffer {
    private:
        Vector2<Color> _buffer = Vector2<Color>(1920, 1080);
        Color _gammaCorrection(const Color& color) const;

    public:
        void outputToFile(const std::string& image_name) const;
        
        void setPixel(uint16_t x, uint16_t y, const Color& color);
        void resize(uint16_t size_x, uint16_t size_y);
        void fill(const Color& color);

        uint16_t sizeX() const { return _buffer.sizeX(); }
        uint16_t sizeY() const { return _buffer.sizeY(); }
};
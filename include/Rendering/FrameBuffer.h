#pragma once

#include "../Types/Vector2.hpp"
#include "../Types/Point.hpp"
#include <string>

class FrameBuffer {
    private:
        // 2D buffer of color objects
        Vector2<Color> _buffer = Vector2<Color>(1920, 1080);

        // Run gamma correction on a color to attempt to avoid color banding
        Color _gammaCorrection(const Color& color) const;

    public:
        /***
         * @brief Dumps the buffer's contents into a .ppm file
         * 
         * @param image_name    The name for the created image file
         */
        void outputToFile(const std::string& image_name) const;
        
        /***
         * @brief Stores a color at an (x, y) position in the buffer
         * 
         * @param x     The desired x-index of the buffer
         * @param y     The desired y-index of the buffer
         * @param color The desired color to place in the buffer
         */
        void setPixel(uint16_t x, uint16_t y, const Color& color);

        /**
         * @brief Resizes the buffer to a desired size
         * 
         * @param size_x    The desired buffer width
         * @param size_y    The desired buffer height
         */
        void resize(uint16_t size_x, uint16_t size_y);

        /***
         * @brief Fills every pixel of the buffer with a desired color
         * 
         * @param color The desired color to place in the buffer
         */
        void fill(const Color& color);

        /***
         * @brief Get the buffer's width
         * 
         * @param color Another color object
         * 
         * @return      The buffer's width
         */
        uint16_t sizeX() const { return _buffer.sizeX(); }

        /***
         * @brief Get the buffer's height
         * 
         * @param color Another color object
         * 
         * @return      The buffer's height
         */
        uint16_t sizeY() const { return _buffer.sizeY(); }
};
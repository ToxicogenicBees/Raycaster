#pragma once

#include <stdint.h>

struct Color {
    // Color channels within the range [0, 1]
    double r, g, b;

    /***
     * @brief Construct a color using doubles
     * 
     * @param r     Red color channel
     * @param g     Green color channel
     * @param b     Blue color channel
     */
    Color(double r, double g, double b);

    /***
     * @brief Copy constructor
     * 
     * @param color Another color object
     */
    Color(const Color& color);

    /***
     * @brief Default constructor (creates a color set to black)
     */
    Color();

    /***
     * @brief Assignment operator overload
     * 
     * @param color Another color object
     * 
     * @return      A reference to this color object
     */
    Color& operator=(const Color& color);
};

// Color constants defined in Color.cpp
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
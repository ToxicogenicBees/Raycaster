#include "../include/Canvas.h"
#include <random>
#include <string>

int main(int argc, char *argv[]) {
    // Resize canvas to desired siw
    canvas.resize(1920, 1080);

    // Random colors for now
    for (int x = 0; x < canvas.sizeX(); x++ ) {
        for (int y = 0; y < canvas.sizeY(); y++) {
            canvas.setPixel(x, y, Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
        }
    }

    // Determine if a file name was passed
    std::string fileName = (argc > 1 ? argv[1] : "Output");

    // Render an image
    canvas.render(fileName);
    
    return 0;
}
#include "../include/Rendering/Canvas.h"
#include <random>
#include <string>

using namespace ImageSize;
using namespace Colors;

int main(int argc, char *argv[]) {
    // Resize canvas to desired size
    canvas.resize(SIZE_1920x1080);

    // Random colors for now
    Color colors[8] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, WHITE, BLACK};

    for (int x = 0; x < canvas.sizeX(); x++ ) {
        for (int y = 0; y < canvas.sizeY(); y++) {
            canvas.setPixel(x, y, colors[std::rand() % 8]);
        }
    }

    // Determine if a file name was passed
    std::string fileName = (argc > 1 ? argv[1] : "out");

    // Render an image
    canvas.outputToFile(fileName);
    
    return 0;
}
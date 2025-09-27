#include "../include/Rendering/FrameBuffer.h"
#include "../include/Rendering/Camera.h"
#include "../include/Scene/Objects/Sphere.h"
#include <random>
#include <string>

using namespace ImageSize;
using namespace Colors;

// int main(int argc, char *argv[]) {
//     // Resize frame buffer to desired size
//     frameBuffer.resize(SIZE_1920x1080);

//     // Random colors for now
//     Color colors[8] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, WHITE, BLACK};

//     for (int x = 0; x < frameBuffer.sizeX(); x++ ) {
//         for (int y = 0; y < frameBuffer.sizeY(); y++) {
//             frameBuffer.setPixel(x, y, colors[std::rand() % 8]);
//         }
//     }

//     // Determine if a file name was passed
//     std::string fileName = (argc > 1 ? argv[1] : "out");

//     // Render an image
//     frameBuffer.outputToFile(fileName);
    
//     return 0;
// }

int main() {
    frameBuffer.resize(SIZE_1920x1080);
    
    // Position camera
    camera.setPosition(double3(5, 5, 5));
    camera.setLookVector(double3(0, 0, 0));

    // Place sphere
    Sphere sphere(double3(0, 0, 0), 2);

    // Cast rays
    camera.castRays(3.141592 / 2);

    return 0;
}
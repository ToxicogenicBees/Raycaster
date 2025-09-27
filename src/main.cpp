#include "../include/Rendering/FrameBuffer.h"
#include "../include/Rendering/Camera.h"
#include "../include/Scene/Objects/Sphere.h"
#include <random>
#include <string>

using namespace ImageSize;
using namespace Colors;

int main() {
    frameBuffer.resize(SIZE_1920x1080); // Adjusting image size
    
    // Position camera
    camera.translate(5, 0, 5);          // Camera's position
    camera.lookAt(0, 0, 0);             // Point camera's pointing towards

    // Place sphere
    Sphere sphere(2);                   // Sphere, centered at origin, with radius 2
    sphere.translate(0, 0, 0);          // Translate sphere (at origin by default)

    // Cast rays
    camera.render("CameraOutput");      // Rendering the scene

    return 0;
}
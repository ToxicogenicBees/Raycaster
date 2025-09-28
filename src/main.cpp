#include "../include/Rendering/FrameBuffer.h"
#include "../include/Scene/BasicObjects.h"
#include <random>
#include <string>

using namespace ImageSize;
using namespace Colors;

int main() {
    frameBuffer.resize(SIZE_1920x1080); // Adjusting image size

    double3 sphere_center(0.0, 0.0, 0.0);
    double sphere_radius = 2;
    
    // Position camera
    camera.translate(sphere_center + double3(5, 5, 5));
    camera.lookAt(sphere_center);

    // Place sphere (radius 2)
    Sphere sphere(2);
    sphere.color = Color(1.0, 0.1, 0.1);
    sphere.specular = 0.9;
    sphere.shininess = 30;

    // Place plane
    Plane plane(sphere_center - double3(0, 0, sphere_radius));
    plane.color = Color(0.0, 1.0, 0.2);

    // Place lights
    Light light1(double3(1.0, 3.0, 5.0));
    
    // Rendering the scene
    camera.render("CameraOutput");

    return 0;
}
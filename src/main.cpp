#include "../include/Scene/Scene.h"

int main(int argc, char **argv) {
    // Position camera
    Camera camera;
    camera.position = double3(5, 5, 5);
    camera.look_vec = double3(0, 0, 0);

    // Place sphere (radius 2)
    Sphere sphere(2);
    sphere.color = Color(1, 0.1, 0.1);
    sphere.specular = 0.9;
    sphere.shininess = 30;

    // Place plane
    Plane plane(-2);
    plane.color = Colors::CYAN;

    // Place lights
    Light light;
    light.translate(1, 3, 5);
    
    // Rendering the scene
    scene.addObject(&camera);
    scene.addObject(&sphere);
    scene.addObject(&plane);
    scene.addObject(&light);

    // Render file
    std::string file_name = (argc > 1 ? argv[1] : "out");
    scene.render(file_name);

    return 0;
}
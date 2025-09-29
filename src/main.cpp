#include "../include/Rendering/PhongShading.h"
#include "../include/Scene/Scene.h"

int main(int argc, char **argv) {
    // Determine file name
    std::string file_name = (argc > 1 ? argv[1] : "out");

    // Position camera
    Camera camera;
    camera.positionAt(5.0, 5.0, 5.0);
    camera.lookAt(0.0, 0.0, 0.0);

    // Place sphere (radius 2)
    Sphere sphere(2);
    sphere.setColor(Color(1, 0.1, 0.1));
    sphere.setSpecular(0.9);
    sphere.setShininess(30);

    // Place plane
    Plane plane(-2);
    plane.setColor(Colors::CYAN);

    // Place lights
    Light light;
    light.positionAt(1, 3, 5);
    
    // Rendering the scene ( replaces Scene::parseSceneFile(file_name) )
    Scene::addObject(&camera);
    Scene::addObject(&sphere);
    Scene::addObject(&plane);
    Scene::addObject(&light);

    // Render scene
    PhongShading::renderWithSimpleShading(file_name);

    return 0;
}
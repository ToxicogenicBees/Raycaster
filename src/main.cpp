#include "../include/Rendering/PhongShading.h"
#include "../include/Scene/Scene.h"

int main(int argc, char **argv) {
    // Determine file name
    std::string file_name = (argc > 1 ? argv[1] : "out");

    // Position camera
    Camera camera;
    camera.positionAt(5, 1, 2);
    camera.lookAt(0, 0, 0);

    // Place sphere (radius 2)
    Sphere sphere1(2);
    sphere1.setColor(Color(1, 0.1, 0.1));
    sphere1.setSpecular(0.9);
    sphere1.setShininess(30);
    sphere1.setReflectance(0.25);

    // Place sphere (radius 4)
    Sphere sphere2(4);
    sphere2.setColor(Color(0.9, 0.8, 0.1));
    sphere2.setSpecular(0.6);
    sphere2.setShininess(20);
    sphere2.setReflectance(0.15);
    sphere2.translate(-3, -2.5, 2);

    // Place plane
    Plane plane(-2);
    plane.setColor(Color(0, 1, 1));
    plane.setReflectance(0.35);

    // Place lights
    Light light1;
    light1.positionAt(1, 3, 2);

    Light light2;
    light2.positionAt(2.5, -1, 2);
    
    // Rendering the scene ( replaces Scene::parseSceneFile(file_name) )
    Scene::setRenderSize(1920, 1080);
    Scene::setShadows(true);

    Scene::addObject(&camera);
    Scene::addObject(&sphere1);
    Scene::addObject(&sphere2);
    Scene::addObject(&plane);
    Scene::addObject(&light1);
    Scene::addObject(&light2);

    // Render scene
    PhongShading::renderWithRecursiveShading(file_name);
    //PhongShading::renderWithSimpleShading(file_name);

    return 0;
}
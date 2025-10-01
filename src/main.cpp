#include "../include/Rendering/PhongShading.h"
#include "../include/Scene/Scene.h"

int main(int argc, char **argv) {
    // Determine file name
    std::string file_name = (argc > 1 ? argv[1] : "out");

    // Position camera
    Camera camera;
    camera.positionAt(8.47, 4.58, 2.5);
    camera.lookAt(0, 0, 0);

    // Place sphere (radius 2.5)
    Sphere sphere1(2.5);
    sphere1.translate(0.47, 5.36, 0.5);
    sphere1.setColor(Color(1, 1, 1));
    sphere1.setReflectance(0.45);

    // Place sphere (radius 4)
    Sphere sphere2(4);
    sphere2.translate(-2.16, -1.5, 2);
    sphere2.setColor(Color(1, 1, 1));
    sphere2.setReflectance(0.45);

    // Place sphere (radius 2)
    Sphere sphere3(2);
    sphere3.translate(4.71, -0.73, 0);
    sphere3.setColor(Color(1, 1, 1));
    sphere3.setReflectance(0.45);

    // Place plane
    Plane plane(-2);
    plane.setColor(Color(1, 1, 1));
    plane.setReflectance(0.65);

    // Place lights
    Light light1;
    light1.positionAt(-5, 4.5, 4);
    light1.setColor(0.1, 0.1, 1);

    Light light2;
    light2.positionAt(4.16, -4.92, 3);
    light2.setColor(1, 0.1, 0.1);

    Light light3;
    light3.positionAt(5.36, 4.6, 3.5);
    light3.setColor(0.1, 1, 0.1);
    
    // Scene initialization
    Scene::setRenderSize(2560, 1440);
    Scene::setAttenuation(1, 0, 0.05);
    Scene::setShadows(true);

    Scene::addObject(&camera);
    Scene::addObject(&sphere1);
    Scene::addObject(&sphere2);
    Scene::addObject(&sphere3);
    Scene::addObject(&plane);
    Scene::addObject(&light1);
    Scene::addObject(&light2);
    Scene::addObject(&light3);

    // Render scene
    PhongShading::renderWithRecursiveShading(file_name);
    return 0;
}
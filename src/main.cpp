#include "../include/Rendering/PhongShading.h"
#include "../include/Scene/Scene.h"

int main(int argc, char **argv) {
    // Determine file name
    std::string file_name = (argc > 1 ? argv[1] : "out");

    // Place camera
    Camera camera;
    camera.lookAt(0, 0, 0);

    Sphere sphere1(2.5);
    sphere1.translate(0.47, 5.36, 0.5);
    sphere1.setReflectance(0.35);
    sphere1.setColor(0.1, 1, 0.1);

    Sphere sphere2(4);
    sphere2.translate(-2.16, -1.5, 2);
    sphere2.setReflectance(0.35);
    sphere2.setColor(0.1, 0.1, 1);

    Box box(double3(-2, -2, -2), double3(2, 2, 2));
    box.setReflectance(0.05);
    box.rotate(0, 0, 0.52359878);
    box.translate(4.71, -0.73, 0);
    box.setColor(1, 0.1, 0.1);
    box.setTransparency(0.75);

    Light light1;
    light1.positionAt(-5, 4.5, 4);
    light1.setColor(1, 0.5, 0.5);

    Light light2;
    light2.positionAt(4.16, -4.92, 3);
    light2.setColor(0.5, 0.5, 1);

    Light light3;
    light3.positionAt(5.36, 4.6, 3.5);
    light3.setColor(0.5, 1, 0.5);

    Plane plane(-2.0625);
    plane.setColor(Color(0.1, 0.1, 0.1));
    plane.setReflectance(0);
    
    // Scene initialization
    Scene::setRenderSize(1920, 1080);
    Scene::setAttenuation(1, 0, 0.05);
    Scene::setShadows(true);

    // Render scene
    for (int i = 0; i < 360; i++) {
        double angle = i * 0.0174532925199;
        camera.positionAt(10 * std::cos(angle), 10 * std::sin(angle), 2.5);
        PhongShading::renderWithRecursiveShading(file_name + "_" + std::to_string(i));
    }

    return 0;
}
#include "../../include/Rendering/FrameBuffer.h"
#include "../../include/Scene/Scene.h"

std::vector<BaseObject*> Scene::_objects;
std::vector<Camera*> Scene::_cameras;
std::vector<Light*> Scene::_lights;

Point<uint16_t> Scene::_size = Point<uint16_t>(1920, 1080);
bool Scene::_attenuation = false;
double Scene::_fov = 1.57079633;
double Scene::_ambience = 0.1;

void Scene::parseSceneFile(const std::string& file_name) {
    std::cout << "Parsing file " << file_name << std::endl;

    // File parsing

    std::cout << "Parsed file " << file_name << std::endl << std::endl;
}

void Scene::addObject(BaseObject* obj) {
    _objects.push_back(obj);
}

void Scene::addObject(Camera* camera) {
    _cameras.push_back(camera);
}

void Scene::addObject(Light* light) {
    _lights.push_back(light);
}

void Scene::setRenderSize(const Point<uint16_t> size) {
    _size = size;
}

void Scene::setRenderSize(uint16_t sx, uint16_t sy) {
    _size = Point<uint16_t>(sx, sy);
}

void Scene::setAttenuation(bool attenuation) {
    _attenuation = attenuation;
}

void Scene::setAmbience(double ambience) {
    _ambience = ambience;
}

void Scene::setFOV(double fov) {
    _fov = fov;
}
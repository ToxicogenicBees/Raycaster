#include "../../include/Scene/BasicObjects.h"
#include "../../include/Scene/Scene.h"

#include <algorithm>

std::vector<BaseObject*> Scene::_objects;
std::vector<Camera*> Scene::_cameras;
std::vector<Light*> Scene::_lights;

size3 Scene::_size = size3(512, 512);
double3 Scene::_attenuation(1, 0, 0);
bool Scene::_shadows = false;
double Scene::_fov = 1.57079633;
double Scene::_ambience = 0.1;

// Helper function for removing from container
template <class Container, class Object>
void removeFrom(Container& container, Object* object) {
    auto it = std::find(container.begin(), container.end(), object);
    if (it != container.end())
        container.erase(it);
}

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

void Scene::removeObject(BaseObject* obj) {
    removeFrom(_objects, obj);
}

void Scene::removeObject(Camera* camera) {
    removeFrom(_cameras, camera);
}

void Scene::removeObject(Light* light) {
    removeFrom(_lights, light);
}

void Scene::setRenderSize(const size3 size) {
    _size = size;
}

void Scene::setRenderSize(uint16_t sx, uint16_t sy) {
    _size = size3(sx, sy);
}

void Scene::setAttenuation(double3 attenuation) {
    _attenuation = attenuation;
}

void Scene::setAttenuation(double a, double b, double c) {
    _attenuation = double3(a, b, c);
}

void Scene::setAmbience(double ambience) {
    _ambience = ambience;
}

void Scene::setFOV(double fov) {
    _fov = fov;
}

void Scene::setShadows(bool shadows) {
    _shadows = shadows;
}
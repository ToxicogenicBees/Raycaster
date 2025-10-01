#include "../../include/Scene/BasicObjects.h"
#include "../../include/Scene/Scene.h"

std::vector<BaseObject*> Scene::_objects;
std::vector<Camera*> Scene::_cameras;
std::vector<Light*> Scene::_lights;

size3 Scene::_size = size3(512, 512);
double3 Scene::_attenuation(1, 0, 0);
bool Scene::_shadows = false;
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

void Scene::removeObject(BaseObject* obj) {
    uint16_t index = _objects.size() + 1;
    for (uint16_t i = 0; i < _objects.size(); i++) {
        if (_objects[i] == obj) {
            index = i;
            break;
        }
    }

    if (index < _objects.size())
        _objects.erase(_objects.begin() + index);
}

void Scene::removeObject(Camera* camera) {
    uint16_t index = _cameras.size() + 1;
    for (uint16_t i = 0; i < _cameras.size(); i++) {
        if (_cameras[i] == camera) {
            index = i;
            break;
        }
    }

    if (index < _cameras.size())
        _cameras.erase(_cameras.begin() + index);
}

void Scene::removeObject(Light* light) {
    uint16_t index = _lights.size() + 1;
    for (uint16_t i = 0; i < _lights.size(); i++) {
        if (_lights[i] == light) {
            index = i;
            break;
        }
    }

    if (index < _lights.size())
        _lights.erase(_lights.begin() + index);
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
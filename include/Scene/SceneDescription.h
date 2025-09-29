#pragma once

#include "BasicObjects.h"
#include <vector>

struct SceneDescription {
    std::vector<BaseObject*> objects;
    std::vector<Camera*> cameras;
    std::vector<Light*> lights;

    bool attenuation = false;
    double fov = 1.57079633;
    double ambience = 0.1;
};
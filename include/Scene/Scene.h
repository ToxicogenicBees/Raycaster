#pragma once

#include "BasicObjects.h"
#include <string>

class Scene {
    private:
        static std::vector<BaseObject*> _objects;
        static std::vector<Camera*> _cameras;
        static std::vector<Light*> _lights;
        static std::vector<Color*> _colors;

        static double _ambient_intensity;
        static bool _attenuation;
        static double _fov;

        static Intersection _findIntersectionAt(Camera* camera, uint16_t x, uint16_t y);
        static Color _phongReflection(Camera* camera, const Intersection& intersection);
        static void _parseSceneFile(const std::string& file_name);

    public:
        static void addObject(BaseObject* obj);
        static void addObject(Camera* camera);
        static void addObject(Light* light);

        static void setAttenuation(bool state);
        static void render(const std::string& file_name);
};

extern Scene scene;
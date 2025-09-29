#pragma once

#include "SceneDescription.h"
#include "BasicObjects.h"
#include <string>

class Scene {
    private:
        static std::vector<BaseObject*> _objects;
        static std::vector<Camera*> _cameras;
        static std::vector<Light*> _lights;

        static Point<uint16_t> _size;
        static bool _attenuation;
        static double _ambience;
        static double _fov;

        
    public:
        friend class PhongShading;
        
        static void parseSceneFile(const std::string& file_name);

        static void addObject(BaseObject* obj);
        static void addObject(Camera* camera);
        static void addObject(Light* light);

        static void setRenderSize(const Point<uint16_t> size);
        static void setRenderSize(uint16_t sx, uint16_t sy);
        static void setAttenuation(bool attenuation);
        static void setAmbience(double ambience);
        static void setFOV(double fov);
};
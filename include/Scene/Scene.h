#pragma once

#include <string>

class Scene {
    private:
        static bool _attenuation;

        static void _parseSceneFile(const std::string& file_name);

    public:
        static bool useAttenuation(bool state);
        static void renderScene(const std::string& file_name);
};
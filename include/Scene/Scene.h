#pragma once

#include "BasicObjects.h"
#include <string>

class Scene {
    private:
        // Objects in the scene
        static std::vector<BaseObject*> _objects;
        static std::vector<Camera*> _cameras;
        static std::vector<Light*> _lights;

        // Generic scene values
        static Point<uint16_t> _size;   // Image size
        static bool _attenuation;       // Whether or not attenuation is accounted for
        static double _ambience;        // Abient light intensity
        static double _fov;             // Field of view
        
    public:
        friend class PhongShading;
        
        /***
         * @brief Parses a custom .scene file (similar to POV-Ray files) to construct an object list
         *        to be sent out for rendering
         * 
         * @param file_name The name of the .scene file (without the file type)
         */
        static void parseSceneFile(const std::string& file_name);

        /***
         * @brief Adds an object to the scene
         * 
         * @param obj   Pointer to the object added to the scene
         */
        static void addObject(BaseObject* obj);

        /***
         * @brief Adds a camera to the scene
         * 
         * @param obj   Pointer to the camera added to the scene
         */
        static void addObject(Camera* camera);

        /***
         * @brief Adds a light to the scene
         * 
         * @param obj   Pointer to the light added to the scene
         */
        static void addObject(Light* light);

        /***
         * @brief Sets the rendered image's size
         * 
         * @param size  A point containing the image's (x, y) size, in pixels
         */
        static void setRenderSize(const Point<uint16_t> size);

        /***
         * @brief Sets the rendered image's size
         * 
         * @param x The image's width, in pixels
         * @param y The image's height, in pixels
         */
        static void setRenderSize(uint16_t sx, uint16_t sy);

        /***
         * @brief Updates the attenuation flag to enable/disable attenuation
         * 
         * @param attenuation   The attenuation flag (true enabled attenuation)
         */
        static void setAttenuation(bool attenuation);

        /***
         * @brief Sets the intensity of ambient light in the scene
         * 
         * @param ambience  The ambient light intensity coefficient, [0, 1]
         */
        static void setAmbience(double ambience);

        /***
         * @brief Sets the vertical field of view of the scene
         * 
         * @param fov   The vertical field of view, in radians
         */
        static void setFOV(double fov);
};
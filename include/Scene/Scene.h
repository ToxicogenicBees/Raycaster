#pragma once

#include <string>
#include <vector>

class BaseObject;
class Camera;
class Light;

class Scene {
    private:
        // Objects in the scene
        static std::vector<BaseObject*> _objects;
        static std::vector<Camera*> _cameras;
        static std::vector<Light*> _lights;

        // Generic scene values
        static double3 _attenuation;    // Attenuation coefficients
        static size3 _size;             // Image size

        static double _ambience;        // Abient light intensity
        static double _fov;             // Field of view

        static bool _shadows;           // Whether or not shadows are enabled
        
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
         * @param camera    Pointer to the camera added to the scene
         */
        static void addObject(Camera* camera);

        /***
         * @brief Adds a light to the scene
         * 
         * @param light     Pointer to the light added to the scene
         */
        static void addObject(Light* light);

        /***
         * @brief Removes an object from the scene
         * 
         * @param obj   Pointer to the object removed from the scene
         */
        static void removeObject(BaseObject* obj);

        /***
         * @brief Removes a camera from the scene
         * 
         * @param camera    Pointer to the camera removed from the scene
         */
        static void removeObject(Camera* camera);

        /***
         * @brief Removes a light from the scene
         * 
         * @param light     Pointer to the light removed from the scene
         */
        static void removeObject(Light* light);

        /***
         * @brief Sets the rendered image's size
         * 
         * @param size  A point containing the image's (x, y) size, in pixels
         */
        static void setRenderSize(const size3 size);

        /***
         * @brief Sets the rendered image's size
         * 
         * @param x The image's width, in pixels
         * @param y The image's height, in pixels
         */
        static void setRenderSize(size_t sx, size_t sy);

        /***
         * @brief Updates the attenuation coefficients
         * 
         * @param attenuation   The desired attenuation coefficients
         */
        static void setAttenuation(double3 attenuation);

        /***
         * @brief Updates the attenuation coefficients
         * 
         * @param attenuation   The desired attenuation coefficients
         */
        static void setAttenuation(double a, double b, double c);

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
        
        /***
         * @brief Updates the shadows flag to enable/disable shadows
         * 
         * @param attenuation   The attenuation flag (true enables shadows)
         */
        static void setShadows(bool shadows);
};
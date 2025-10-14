#pragma once

#include "../../Rendering/FrameBuffer.h"
#include "../../Rendering/Ray.h"
#include "../../Types/Point.hpp"

class Camera {
    private:
        // Position
        double3 _position = double3(0, 0, 0);

        // Independent orientation vectors         
        double3 _look_vec = double3(0, 0, 0);
        double3 _up_vec = double3(0, 0, 1);

        // Dependent orientation vectors
        double3 _look_vec_norm, _right_vec, _exact_up;  

        // Per-render values
        double _tan_fov_x, _tan_fov_y;
        size_t _size_x, _size_y;

        // Update the camera's orientation vectors
        void _updateOrientation();

    public:
        friend class PhongShading;

        /***
         * @brief Creates and places a camera into the scene
         */
        Camera();

        /***
         * @brief Destroys and removes the camera from the scene
         */
        ~Camera();

        /***
         * @brief Places the camera at a desired (x, y, z) position
         * 
         * @param point The desired position
         */
        virtual void positionAt(const double3& point);

        /***
         * @brief Places the camera at a desired (x, y, z) position
         * 
         * @param x    The desired x-position
         * @param y    The desired y-position
         * @param z    The desired z-position
         */
        void positionAt(double x, double y, double z);

        /***
         * @brief Translates the camera by a desired (x, y, z) distance
         * 
         * @param dp   The desired position change
         */
        virtual void translate(const double3& dp);

        /***
         * @brief Translates the camera by a desired (x, y, z) distance
         * 
         * @param dx   The desired x-position change
         * @param dy   The desired y-position change
         * @param dz   The desired z-position change
         */
        void translate(double dx, double dy, double dz);

        /***
         * @brief Sets the camera's up-vector
         * 
         * @param up_vec    A vector pointing in the desired upward direction
         */
        void setWorldUp(const double3& up_vec);

        /***
         * @brief Sets the camera's up-vector
         * 
         * @param x     The x-component of a vector pointing in the desired upward direction
         * @param y     The y-component of a vector pointing in the desired upward direction
         * @param z     The z-component of a vector pointing in the desired upward direction
         */
        void setWorldUp(double x, double y, double z);

        /***
         * @brief Sets the focus of the camera to a desired (x, y, z) position
         * 
         * @param point The desired focal position
         */
        void lookAt(const double3& point);

        /***
         * @brief Sets the focus of the camera to a desired (x, y, z) position
         * 
         * @param x     The desired focal x-position
         * @param y     The desired focal y-position
         * @param z     The desired focal z-position
         */
        void lookAt(double x, double y, double z);

        /***
         * @brief Calculates the unit view vector passing through a pixel of the screen
         * 
         * @param window_size   The height and width of the window of pixels
         * @param x             The desired pixel's x-coordinate
         * @param y             The desired pixel's y-coordinate
         * 
         * @return The ray passing through the pixel, starting at the camera
         */
        Ray rayThroughPixel(const size3& window_size, size_t x, size_t y) const;

        /***
         * @brief Runs pre-rendering calculations required for finding the camera's view vector through pixels
         * 
         * @param frameBuffer   Reference to the current working frame buffer
         * @param fov           The desired image fov
         */
        void preRenderInit(const FrameBuffer& frameBuffer, double fov);
};
#pragma once

#include "../../Rendering/FrameBuffer.h"
#include "PointObject.h"

namespace {
    using double3 = Point<double>;
}

class Camera : public PointObject {
    private:
        // Independent orientation vectors         
        double3 _look_vec = double3(0, 0, 0);
        double3 _up_vec = double3(0, 0, 1);

        // Dependent orientation vectors
        double3 _look_vec_norm, _right_vec, _exact_up;  

        // Per-render values
        double _tan_fov_x, _tan_fov_y;
        uint16_t _size_x, _size_y;

        // Update the camera's orientation vectors
        void _updateOrientation();

    public:
        using PointObject::translate;
        using PointObject::positionAt;

        friend class PhongShading;

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
         * @brief Places the object at a desired (x, y, z) position
         * 
         * @param point The desired position
         */
        void positionAt(const double3& point) override;

        /***
         * @brief Translates the object by a desired (x, y, z) distance
         * 
         * @param dp   The desired position change
         */
        void translate(const double3& dp) override;

        /***
         * @brief Calculates the unit view vector passing through a pixel of the screen
         * 
         * @param frameBuffer   Reference to the current working frame buffer
         * @param x             The desired pixel's x-coordinate
         * @param y             The desired pixel's y-coordinate
         * 
         * @return The direction of the ray passing through the pixel
         */
        double3 rayThroughPixel(const FrameBuffer& frameBuffer, uint16_t x, uint16_t y) const;

        /***
         * @brief Runs pre-rendering calculations required for finding the camera's view vector through pixels
         * 
         * @param frameBuffer   Reference to the current working frame buffer
         * @param fov           The desired image fov
         */
        void preRenderInit(const FrameBuffer& frameBuffer, double fov);
};
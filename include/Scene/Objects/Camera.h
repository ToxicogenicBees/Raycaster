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

        void setWorldUp(double x, double y, double z);
        void setWorldUp(const double3& up_vec);

        void lookAt(double x, double y, double z);
        void lookAt(const double3& point);

        void positionAt(const double3& point) override;
        void translate(const double3& dp) override;

        double3 rayThroughPixel(const FrameBuffer& frameBuffer, uint16_t x, uint16_t y) const;
        void preRenderInit(const FrameBuffer& frameBuffer, double fov);
};
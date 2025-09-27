#include "../../include/Scene/Objects/BaseObject.h"
#include "../../include/Rendering/FrameBuffer.h"
#include "../../include/Rendering/Camera.h"
#include "../../include/Scene/Light.h"
#include "../../include/Vector2.hpp"
#include <cmath>

double3 Camera::_look_vec(0, 0, 0);
double3 Camera::_up_vec(0, 0, 1);
double3 Camera::_pos(0, 0, 1);

Camera camera;

void Camera::setLookVector(const double3& look_vec) {
    _look_vec = look_vec;
}

void Camera::setPosition(const double3& pos) {
    _pos = pos;
}

void Camera::castRays(double field_of_view) {
    // Clear buffer
    frameBuffer.fill(Colors::BLACK);

    // Calculate necessary values
    double3 look_vec_norm = (_look_vec - _pos).normal();
    double3 right_vec = cross(look_vec_norm, _up_vec).normal();
    double3 exact_up = cross(right_vec, look_vec_norm);

    double aspect_ratio = (double)(frameBuffer.sizeX()) / frameBuffer.sizeY();      // Aspect ratio
    double field_of_view_horiz = 2 * atan(aspect_ratio * tan(field_of_view / 2));   // Horizontal FOV

    double tan_fov_x = tan(0.5 * field_of_view_horiz);
    double tan_fov_y = tan(0.5 * field_of_view);
    
    // Iterate over each pixel in the buffer
    for (uint16_t i = 0; i < frameBuffer.sizeX(); i++) {
        for (uint16_t j = 0; j < frameBuffer.sizeY(); j++) {
            // Determine the ray from this pixel out from the camera
            double s_x = (i + 0.5) / frameBuffer.sizeX();
            double s_y = (j + 0.5) / frameBuffer.sizeY();

            double x = (2 * s_x - 1) * tan_fov_x;
            double y = (1 - 2 * s_y) * tan_fov_y;

            double3 view_dir = (x * right_vec + y * exact_up + look_vec_norm).normal();

            // Save closest intersection
            Intersection closest;

            // Iterate over each object
            for (BaseObject* obj : BaseObject::objects) {
                // Attempt to intersect a ray with this object
                Intersection inter = obj->findIntersection(_pos, view_dir);
                
                // If the intersection succeeded, and is the closest thus far, mark it
                if (inter.obj && !closest.obj)
                    closest = inter;
                else if (inter.obj && (_pos - inter.pos).squaredMagnitude() < (_pos - closest.pos).squaredMagnitude()) {
                    closest = inter;
                }
            }

            // Set pixel's color if an intersection was found
            if (closest.obj) {
                frameBuffer.setPixel(i, j, Colors::WHITE);
            }
        }
    }

    // Output image to a file
    frameBuffer.outputToFile("CameraOutput");
}
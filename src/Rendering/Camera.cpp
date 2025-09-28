#include "../../include/Scene/Objects/BaseObject.h"
#include "../../include/Rendering/FrameBuffer.h"
#include "../../include/Rendering/Camera.h"
#include "../../include/Types/Vector2.hpp"
#include "../../include/Scene/Light.h"
#include <algorithm>
#include <cmath>

double Camera::_field_of_view = 1.57079633; // 90 degrees
double3 Camera::_look_vec(0, 0, 0);
double3 Camera::_up_vec(0, 0, 1);
double3 Camera::_pos(0, 0, 1);

Camera camera;

void Camera::translate(double x, double y, double z) {
    _pos = double3(x, y, z);
}

void Camera::translate(const double3& pos) {
    _pos = pos;
}

void Camera::lookAt(double x, double y, double z) {
    _look_vec = double3(x, y, z);
}

void Camera::lookAt(const double3& look_vec) {
    _look_vec = look_vec;
}

void Camera::setFOV(double radians) {
    _field_of_view = radians;
}

void Camera::render(const std::string& image_name) {
    // Clear buffer
    frameBuffer.fill(Colors::BLACK);

    // Calculate necessary values
    double3 look_vec_norm = (_look_vec - _pos).normal();
    double3 right_vec = look_vec_norm.cross(_up_vec).normal();
    double3 exact_up = right_vec.cross(look_vec_norm);

    double aspect_ratio = (double)(frameBuffer.sizeX()) / frameBuffer.sizeY();      // Aspect ratio
    double field_of_view_horiz = 2 * atan(aspect_ratio * tan(_field_of_view / 2));  // Horizontal FOV

    double tan_fov_x = tan(0.5 * field_of_view_horiz);
    double tan_fov_y = tan(0.5 * _field_of_view);
    
    // Iterate over each pixel in the buffer
    for (uint16_t i = 0; i < frameBuffer.sizeX(); i++) {
        for (uint16_t j = 0; j < frameBuffer.sizeY(); j++) {
            // Determine the ray from this pixel out from the camera
            double s_x = (i + 0.5) / frameBuffer.sizeX();
            double s_y = (j + 0.5) / frameBuffer.sizeY();

            double x = (2 * s_x - 1) * tan_fov_x;
            double y = (1 - 2 * s_y) * tan_fov_y;

            double3 view_dir = (x * right_vec + y * exact_up + look_vec_norm).normal();
            
            // Iterate over each object, store closest intersection
            Intersection intersection;

            for (BaseObject* obj : BaseObject::objects) {
                // Attempt to intersect a ray with this object
                Intersection inter = obj->findIntersection(_pos, view_dir);
                
                // If the intersection succeeded, and is the closest thus far, mark it
                if (inter.obj && !intersection.obj)
                    intersection = inter;
                else if (inter.obj && (_pos - inter.pos).squaredMagnitude() < (_pos - intersection.pos).squaredMagnitude()) {
                    intersection = inter;
                }
            }

            // Set pixel's color if an intersection was found
            if (intersection.obj) {
                double r, g, b;

                // Phong shading calculations for ambient reflection
                r = Light::ambient_intensity * intersection.obj->ambient * intersection.obj->color.r;
                g = Light::ambient_intensity * intersection.obj->ambient * intersection.obj->color.g;
                b = Light::ambient_intensity * intersection.obj->ambient * intersection.obj->color.b;
                
                // Iterate over each light to determine their contributions
                for (Light* light : Light::lights) {
                    double3 light_dist = (light->position - intersection.pos);
                    double3 light_vec = light_dist.normal();

                    // Reflection and view vector
                    double3 reflection_vec = (2 * (intersection.normal.dot(light_vec)) * intersection.normal - light_vec).normal();
                    double3 view_vec = (_pos - intersection.pos).normal();

                    // Attenuation coefficients: a = 0, b = 0, c = 5
                    // double f_att = 1 / light_dist.squaredMagnitude();
                    double f_att = 1;

                    // Calculate diffusive and specular components (clamped to avoid subtracting color when dot products go negative)
                    double spec = std::pow(std::max(0.0, view_vec.dot(reflection_vec)), intersection.obj->shininess);
                    double diff = std::max(0.0, light_vec.dot(intersection.normal));
                    
                    // Phong shading calculations for diffusive and specular reflection components
                    r += f_att * (light->diffusion * light->color.r * intersection.obj->diffusion * intersection.obj->color.r * diff
                        + light->specular * light->color.r * intersection.obj->specular * intersection.obj->color.r * spec);
                    g += f_att * (light->diffusion * light->color.g * intersection.obj->diffusion * intersection.obj->color.g * diff
                        + light->specular * light->color.g * intersection.obj->specular * intersection.obj->color.g * spec);
                    b += f_att * (light->diffusion * light->color.b * intersection.obj->diffusion * intersection.obj->color.b * diff
                        + light->specular * light->color.b * intersection.obj->specular * intersection.obj->color.b * spec);
                }

                frameBuffer.setPixel(i, j, Color(r, g, b));
            }
        }
    }

    // Output image to a file
    frameBuffer.outputToFile(image_name);
}
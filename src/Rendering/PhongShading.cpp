#include "../../include/Rendering/PhongShading.h"
#include "../../include/Rendering/FrameBuffer.h"

FrameBuffer PhongShading::_frameBuffer;

Intersection PhongShading::_findIntersectionAt(Camera* camera, uint16_t x, uint16_t y) {
    // Get view direction through pixel
    double3 view_dir = camera->rayThroughPixel(_frameBuffer, x, y);

    // Iterate over each object, store closest intersection
    Intersection intersection;

    for (BaseObject* obj : Scene::_objects) {
        // Attempt to intersect a ray with this object
        Intersection inter = obj->findIntersection(camera->_position, view_dir);
        
        // If the intersection succeeded, and is the closest thus far, mark it
        if (inter.obj && !intersection.obj)
            intersection = inter;
        else if (inter.obj && (camera->_position - inter.pos).squaredMagnitude() < (camera->_position - intersection.pos).squaredMagnitude()) {
            intersection = inter;
        }
    }

    // Return intersection, if one was found
    return intersection;
}

Color PhongShading::regularI(Camera* camera, const Intersection& intersection) {
    // Phong ambient reflection
    Color color(
        Scene::_ambience * intersection.obj->ambient * intersection.obj->color.r,
        Scene::_ambience * intersection.obj->ambient * intersection.obj->color.g,
        Scene::_ambience * intersection.obj->ambient * intersection.obj->color.b
    );
    
    // Iterate over each light to determine their contributions
    for (Light* light : Scene::_lights) {
        double3 light_dist = (light->_position - intersection.pos);
        double3 light_vec = light_dist.normal();

        // Reflection and view vector
        double3 reflection_vec = (2 * (intersection.normal.dot(light_vec)) * intersection.normal - light_vec).normal();
        double3 view_vec = (camera->_position - intersection.pos).normal();

        // Attenuation coefficients: a = 0, b = 0, c = 5
        double f_att = (Scene::_attenuation ? 5 / light_dist.squaredMagnitude() : 1);

        // Calculate diffusive and specular components (clamped to avoid subtracting color when dot products go negative)
        double spec = std::pow(std::max(0.0, view_vec.dot(reflection_vec)), intersection.obj->shininess);
        double diff = std::max(0.0, light_vec.dot(intersection.normal));
        
        // Phong shading calculations for diffusive and specular reflection components
        color.r += f_att * (light->_diffusion * light->_color.r * intersection.obj->diffusion * intersection.obj->color.r * diff
            + light->_specular * light->_color.r * intersection.obj->specular * intersection.obj->color.r * spec);
        color.g += f_att * (light->_diffusion * light->_color.g * intersection.obj->diffusion * intersection.obj->color.g * diff
            + light->_specular * light->_color.g * intersection.obj->specular * intersection.obj->color.g * spec);
        color.b += f_att * (light->_diffusion * light->_color.b * intersection.obj->diffusion * intersection.obj->color.b * diff
            + light->_specular * light->_color.b * intersection.obj->specular * intersection.obj->color.b * spec);
    }

    // Return color
    return color;
}

void PhongShading::renderWithSimpleShading(const std::string& file_name) {
    uint16_t cur_camera_id = 0;

    // Set size of frame buffer
    _frameBuffer.resize(Scene::_size.x, Scene::_size.y);

    for (Camera* camera : Scene::_cameras) {
        // Determine the image's new file name
        std::string new_img_name = file_name;
        if (Scene::_cameras.size() > 1)
            new_img_name += "_camera" + std::to_string(cur_camera_id);

        // Clear the frame buffer
        _frameBuffer.fill(Colors::BLACK);

        // Let the camera pre-calculate values for view vector calculations
        camera->preRenderInit(_frameBuffer, Scene::_fov);

        // Iterate over each pixel in the image
        for (uint16_t i = 0; i < Scene::_size.x; i++) {
            for (uint16_t j = 0; j < Scene::_size.y; j++) {
                // Find intersection from ray through this pixel
                Intersection intersection = _findIntersectionAt(camera, i, j);

                // Set pixel's color at the intersection point
                if (intersection.obj) _frameBuffer.setPixel(i, j, regularI(camera, intersection));
            }
        }

        // Output current image data to file
        _frameBuffer.outputToFile(new_img_name);
        cur_camera_id++;
    }
}
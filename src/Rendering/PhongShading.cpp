#include "../../include/Rendering/PhongShading.h"
#include "../../include/Rendering/FrameBuffer.h"
#include "../../include/Scene/Scene.h"

uint16_t PhongShading::_MAX_RECURSIVE_DEPTH = 255;
FrameBuffer PhongShading::_frame_buffer;

namespace {
    const Color BACKGROUND_COLOR(0, 0, 0);
}

Intersection PhongShading::_closestIntersectionOnRay(const Ray& ray) {
    // Iterate over each object, store closest intersection
    Intersection closest_inter;

    for (BaseObject* obj : Scene::_objects) {
        // Attempt to intersect a ray with this object
        Intersection new_inter = obj->findIntersection(ray);
        
        // If the intersection succeeded, and is the closest thus far, mark it
        if (new_inter.obj && !closest_inter.obj)
            closest_inter = new_inter;
        else if (new_inter.obj && (ray.origin - new_inter.pos).squaredMagnitude() < (ray.origin - closest_inter.pos).squaredMagnitude()) {
            closest_inter = new_inter;
        }
    }

    // Return intersection, if one was found
    return closest_inter;
}

double3 PhongShading::_reflectionBetween(const double3& vec, const double3& normal) {
    return (vec - 2 * vec.dot(normal) * normal);
}

Color PhongShading::_regularI(const Intersection& intersection, const Ray& view_ray) {
    // Phong ambient reflection
    Color color = Scene::_ambience * intersection.obj->_ambience * intersection.obj->_color;
    
    // Iterate over each light to determine their contributions
    for (Light* light : Scene::_lights) {
        // TODO: Shadows
        // if (Scene::_shadows && ...)
        //     continue;

        double3 light_vec = (intersection.pos - light->_position);
        double3 light_dir = light_vec.normal();

        // Reflection vector
        double3 reflection_dir = _reflectionBetween(light_dir, intersection.normal);

        // Attenuation coefficients: a = 0, b = 0, c = 5
        double f_att = (Scene::_attenuation ? 0.2 / light_vec.squaredMagnitude() : 1);

        // Calculate diffusive and specular components (clamped to avoid subtracting color when dot products go negative)
        // Phong reflection model requires light & view rays to be reversed for calculations, as they need to point away from the intersection
        double spec = std::pow(std::max(0.0, -view_ray.dir.dot(reflection_dir)), intersection.obj->_shininess);
        double diff = std::max(0.0, -light_dir.dot(intersection.normal));
        
        // Phong shading calculations for diffusive and specular reflection components
        color += light->_color * intersection.obj->_color * f_att * (   // Calculated color channel weight (component-wise product of object & light color)
            light->_diffusion * intersection.obj->_diffusion * diff +   // Diffusive reflection component
            light->_specular * intersection.obj->_specular * spec       // Specular reflection component
        );
    }

    // Return color
    return color;
}

Color PhongShading::_recursiveI(const Intersection& intersection, const Ray& view_ray, uint16_t depth) {
    // Find regular I color for this intersection
    Color regular_i = _regularI(intersection, view_ray);

    // If recursion is too deep, return the color at this intersection
    if (depth >= _MAX_RECURSIVE_DEPTH)
        return regular_i;

    // Determine if an intersection with the reflected ray exists
    double3 nudged_intersection = intersection.pos + intersection.normal * 1e-4;                    // Nudge the intersection a little bit to potentially avoid self-intersections
    Ray new_view_ray(nudged_intersection, _reflectionBetween(view_ray.dir, intersection.normal));   // Calculate the reflection ray
    Intersection new_intersection = _closestIntersectionOnRay(new_view_ray);                        // Determine if an intersection exists

    // If there was a new intersection, run the recursive logic
    Color transparency_color = BACKGROUND_COLOR;
    Color reflected_color = BACKGROUND_COLOR;

    if (new_intersection.obj) {
        // TODO: Calculate transparency color if the transparency is > 0
        // if (intersection.obj->_transparency > 0)
        //     transparency_color = intersection.obj->_transparency * _recursiveI(...);

        // Calculate reflected color if the reflectance is > 0
        if (intersection.obj->_reflectance > 0)
            reflected_color = intersection.obj->_reflectance * _recursiveI(new_intersection, new_view_ray, depth + 1);
    }

    return (1 - intersection.obj->_reflectance - intersection.obj->_transparency) * regular_i
        + transparency_color * intersection.obj->_transparency
        + reflected_color * intersection.obj->_reflectance;
}

void PhongShading::_render(const std::string& file_name, bool use_recursive_shading) {
    uint16_t cur_camera_id = 0;

    // Set size of frame buffer
    _frame_buffer.resize(Scene::_size.x, Scene::_size.y);

    for (Camera* camera : Scene::_cameras) {
        // Determine the image's new file name
        std::string new_img_name = file_name;
        if (Scene::_cameras.size() > 1)
            new_img_name += "_camera" + std::to_string(cur_camera_id);

        // Clear the frame buffer
        _frame_buffer.fill(BACKGROUND_COLOR);

        // Let the camera pre-calculate values for view vector calculations
        camera->preRenderInit(_frame_buffer, Scene::_fov);

        // Iterate over each pixel in the image
        for (uint16_t i = 0; i < Scene::_size.x; i++) {
            for (uint16_t j = 0; j < Scene::_size.y; j++) {
                // Find view ray
                Ray view_ray = camera->rayThroughPixel(Scene::_size, i, j);

                // Find intersection from ray through this pixel
                Intersection intersection = _closestIntersectionOnRay(view_ray);

                // Set pixel's color at the intersection point
                if (intersection.obj) {
                    Color color = (use_recursive_shading ? _recursiveI(intersection, view_ray) : _regularI(intersection, view_ray));
                    _frame_buffer.setPixel(i, j, color);
                }  

            }
            
            if ((i + 1) % 100 == 0)
                std::cout << "Rendered line " << i + 1 << std::endl;
        }

        // Output current image data to file
        _frame_buffer.outputToFile(new_img_name);
        cur_camera_id++;
    }
}

void PhongShading::renderWithSimpleShading(const std::string& file_name) {
    _render(file_name, false);
}

void PhongShading::renderWithRecursiveShading(const std::string& file_name) {
    _render(file_name, true);
}
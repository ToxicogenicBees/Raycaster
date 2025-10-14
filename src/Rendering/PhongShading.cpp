#include "../../include/Rendering/PhongShading.h"
#include "../../include/Rendering/FrameBuffer.h"
#include "../../include/Scene/BasicObjects.h"
#include "../../include/Scene/Scene.h"

#include <iomanip>
#include <chrono>
#include <thread>

uint8_t PhongShading::_MAX_RECURSIVE_DEPTH = 30;
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

std::vector<Intersection> PhongShading::_allIntersectionsOnRay(const Ray& ray) {
    std::vector<Intersection> intersections;

    for (BaseObject* obj : Scene::_objects) {
        // Attempt to intersect a ray with this object
        Intersection new_inter = obj->findIntersection(ray);
        
        // If the intersection succeeded, and is the closest thus far, mark it
        if (new_inter.obj)
            intersections.push_back(new_inter);
    }

    // Return intersections
    return intersections;
}

double3 PhongShading::_reflectionBetween(const double3& vec, const double3& normal) {
    return (vec - 2 * vec.dot(normal) * normal);
}

Color PhongShading::_regularI(const Intersection& intersection, const Ray& view_ray) {
    // Phong ambient reflection
    Color color = Scene::_ambience * intersection.obj->_ambience * intersection.obj->_color;
    
    // Iterate over each light to determine their contributions
    for (Light* light : Scene::_lights) {
        double net_light_contribution = 1;

        if (Scene::_shadows) {
            // Nudge intersection point slightly out of the object to avoid floating-point error
            double3 shadow_origin = intersection.pos + intersection.normal * 1e-8;

            // Cast a ray from the intersection point to the light source
            double3 shadow_dir = (light->_position - shadow_origin);
            
            // Test intersections with shadow ray
            for (Intersection& inter : _allIntersectionsOnRay(Ray(shadow_origin, shadow_dir))) {
                // Ignore this object's contribution if the collision is already with this object
                if (inter.obj == intersection.obj)
                    continue;

                // Ensure intersection doesn't occur after passing through the light
                double3 to_inter = inter.pos - shadow_origin;
                double3 to_light = light->_position - shadow_origin;

                if (to_inter.squaredMagnitude() > to_light.squaredMagnitude())
                    continue;
                
                // Calculate light contribution and break early if it's negligable
                net_light_contribution *= inter.obj->_transparency;
                if (net_light_contribution < 1e-8)
                    break;
            }
        }

        // If this light's contribution is negligable, move on
        if (net_light_contribution < 1e-8)
            continue;

        // Light direction
        double3 light_vec = (intersection.pos - light->_position);
        double3 light_dir = light_vec.normal();

        // Reflection vector
        double3 reflection_dir = _reflectionBetween(light_dir, intersection.normal);

        // Attenuation + shadow coefficient
        double f_att = net_light_contribution / ( Scene::_attenuation.x + Scene::_attenuation.y * light_vec.magnitude() + Scene::_attenuation.z * light_vec.squaredMagnitude() );

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

Color PhongShading::_recursiveI(const Intersection& intersection, const Ray& view_ray, uint8_t depth) {
    // Ensure the intersection exists
    if (!intersection.obj)
        return BACKGROUND_COLOR;

    // Find regular I color for this intersection
    Color regular_i = _regularI(intersection, view_ray);

    // If recursion is too deep, return the color at this intersection
    if (depth >= _MAX_RECURSIVE_DEPTH)
        return regular_i;
    
    // Calculate transparency color if the transparency is > 0
    Color transparency_color = BACKGROUND_COLOR;

    if (intersection.obj->_transparency > 0) {
        Ray transparency_ray(intersection.pos + view_ray.dir * 1e-8, view_ray.dir);
        Intersection transparency_intersection = _closestIntersectionOnRay(transparency_ray);
        transparency_color = intersection.obj->_transparency * _recursiveI(transparency_intersection, transparency_ray, depth + 1);
    }
    
    // Calculate reflected color if the reflectance is > 0
    Color reflected_color = BACKGROUND_COLOR;

    if (intersection.obj->_reflectance > 0) {
        Ray reflected_ray(intersection.pos + intersection.normal * 1e-8, _reflectionBetween(view_ray.dir, intersection.normal));
        Intersection reflected_intersection = _closestIntersectionOnRay(reflected_ray);
        reflected_color = intersection.obj->_reflectance * _recursiveI(reflected_intersection, reflected_ray, depth + 1);
    }

    // Return weighted results
    return (1 - intersection.obj->_reflectance - intersection.obj->_transparency) * regular_i
        + transparency_color * intersection.obj->_transparency
        + reflected_color * intersection.obj->_reflectance;
}

void PhongShading::_renderStrip(Camera* camera, size_t scan_line_start, size_t scan_line_end, bool use_recursive_shading) {
    for (size_t i = 0; i < Scene::_size.x; i++) {
        for (size_t j = scan_line_start; j < scan_line_end; j++) {
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
    }
}

void PhongShading::_render(const std::string& file_name, bool use_recursive_shading) {
    size_t num_threads = std::thread::hardware_concurrency();
    size_t cur_camera_id = 0;

    // Set size of frame buffer

    _frame_buffer.resize(Scene::_size.x, Scene::_size.y);

    // Iterate over each camera
    for (Camera* camera : Scene::_cameras) {
        /*-------------------------------
            Initialize the new camera
        -------------------------------*/

        // Determine the image's new file name
        std::string new_img_name = file_name;
        if (Scene::_cameras.size() > 1)
            new_img_name += "_camera" + std::to_string(cur_camera_id);

        // Clear the frame buffer
        _frame_buffer.fill(BACKGROUND_COLOR);

        // Let the camera pre-calculate values for view vector calculations
        camera->preRenderInit(_frame_buffer, Scene::_fov);

        // Log start in console
        std::cout << "Rendering image \"" << new_img_name << "\": ";

        /*----------------------
            Render the scene
        ----------------------*/

        // Start timer
        auto start = std::chrono::high_resolution_clock::now();

        // Create vector of threads
        std::vector<std::thread> threads;

        // Render each strip of the image
        size_t strip_height = Scene::_size.y / num_threads;
        size_t max_height = Scene::_size.y + (Scene::_size.y % strip_height);

        for (size_t height = 0; height < max_height; height += strip_height) {
            threads.push_back(std::thread(_renderStrip, camera, height, std::min(height + strip_height, Scene::_size.y), use_recursive_shading));
        }

        // Ensure each thread will complete before continuing
        for (auto& t : threads)
            t.join();
        
        // End timer
        auto end = std::chrono::high_resolution_clock::now();

        /*--------------------------
            Output the new image
        --------------------------*/

        // Output current image data to file
        _frame_buffer.outputToFile(new_img_name);
        cur_camera_id++;

        // Log completion in console
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout << "Finished in " << duration.count() << " milliseconds\n";
    }
}

void PhongShading::renderWithSimpleShading(const std::string& file_name) {
    _render(file_name, false);
}

void PhongShading::renderWithRecursiveShading(const std::string& file_name) {
    _render(file_name, true);
}
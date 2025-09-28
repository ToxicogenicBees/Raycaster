#include "../../include/Rendering/FrameBuffer.h"
#include "../../include/Scene/Scene.h"

std::vector<BaseObject*> Scene::_objects;
std::vector<Camera*> Scene::_cameras;
std::vector<Light*> Scene::_lights;
std::vector<Color*> Scene::_colors;

double Scene::_ambient_intensity = 0.1; // Ambient light coefficient
bool Scene::_attenuation = false;       // Attenuation disabled by default
double Scene::_fov = 1.57079633;        // 90 degrees

Scene scene;

Intersection Scene::_findIntersectionAt(Camera* camera, uint16_t x, uint16_t y) {
    // Get view direction through pixel
    double3 view_dir = camera->rayThroughPixel(x, y, _fov);

    // Iterate over each object, store closest intersection
    Intersection intersection;

    for (BaseObject* obj : _objects) {
        // Attempt to intersect a ray with this object
        Intersection inter = obj->findIntersection(camera->position, view_dir);
        
        // If the intersection succeeded, and is the closest thus far, mark it
        if (inter.obj && !intersection.obj)
            intersection = inter;
        else if (inter.obj && (camera->position - inter.pos).squaredMagnitude() < (camera->position - intersection.pos).squaredMagnitude()) {
            intersection = inter;
        }
    }

    // Return intersection, if one was found
    return intersection;
}

Color Scene::_phongReflection(Camera* camera, const Intersection& intersection) {
    // Phong ambient reflection
    Color color(
        _ambient_intensity * intersection.obj->ambient * intersection.obj->color.r,
        _ambient_intensity * intersection.obj->ambient * intersection.obj->color.g,
        _ambient_intensity * intersection.obj->ambient * intersection.obj->color.b
    );
    
    // Iterate over each light to determine their contributions
    for (Light* light : _lights) {
        double3 light_dist = (light->position - intersection.pos);
        double3 light_vec = light_dist.normal();

        // Reflection and view vector
        double3 reflection_vec = (2 * (intersection.normal.dot(light_vec)) * intersection.normal - light_vec).normal();
        double3 view_vec = (camera->position - intersection.pos).normal();

        // Attenuation coefficients: a = 0, b = 0, c = 5
        double f_att = (_attenuation ? 5 / light_dist.squaredMagnitude() : 1);

        // Calculate diffusive and specular components (clamped to avoid subtracting color when dot products go negative)
        double spec = std::pow(std::max(0.0, view_vec.dot(reflection_vec)), intersection.obj->shininess);
        double diff = std::max(0.0, light_vec.dot(intersection.normal));
        
        // Phong shading calculations for diffusive and specular reflection components
        color.r += f_att * (light->diffusion * light->color.r * intersection.obj->diffusion * intersection.obj->color.r * diff
            + light->specular * light->color.r * intersection.obj->specular * intersection.obj->color.r * spec);
        color.g += f_att * (light->diffusion * light->color.g * intersection.obj->diffusion * intersection.obj->color.g * diff
            + light->specular * light->color.g * intersection.obj->specular * intersection.obj->color.g * spec);
        color.b += f_att * (light->diffusion * light->color.b * intersection.obj->diffusion * intersection.obj->color.b * diff
            + light->specular * light->color.b * intersection.obj->specular * intersection.obj->color.b * spec);
    }

    // Return color
    return color;
}

void Scene::_parseSceneFile(const std::string& file_name) {
    std::cout << "Parsing file " << file_name << std::endl;

    // File parsing

    std::cout << "Parsed file " << file_name << std::endl << std::endl;
}

void Scene::addObject(BaseObject* obj) {
    _objects.push_back(obj);
}
void Scene::addObject(Camera* camera) {
    _cameras.push_back(camera);
}
void Scene::addObject(Light* light) {
    _lights.push_back(light);
}

void Scene::setAttenuation(bool state) {
    _attenuation = state;
}

void Scene::render(const std::string& file_name) {
    
    // Create scene objects
    _parseSceneFile(file_name);
    
    // Render scene from each camera
    uint16_t cur_camera_id = 0;
    for (Camera* camera : _cameras) {
        // Determine file name
        std::string new_img_name = file_name;
        if (_cameras.size() > 1)
            new_img_name += "_camera" + std::to_string(cur_camera_id);

        // Start rendering
        std::cout << "Started rendering from camera " + std::to_string(cur_camera_id) << std::endl;

        // Clear buffer
        frameBuffer.fill(Colors::BLACK);
        
        // Iterate over each pixel in the buffer
        for (uint16_t i = 0; i < frameBuffer.sizeX(); i++) {
            for (uint16_t j = 0; j < frameBuffer.sizeY(); j++) {
                // Find intersection from ray through this pixel
                Intersection intersection = _findIntersectionAt(camera, i, j);

                // Set pixel's color at the intersection point
                if (intersection.obj) frameBuffer.setPixel(i, j, _phongReflection(camera, intersection));
            }
        }

        // Output image to a file
        frameBuffer.outputToFile(new_img_name);

        // Finish rendering
        std::cout << "Finished rendering from camera " + std::to_string(cur_camera_id) << std::endl << std::endl;
        cur_camera_id++;
    }
}
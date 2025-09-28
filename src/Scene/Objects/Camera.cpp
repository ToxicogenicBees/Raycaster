#include "../../../include/Scene/Objects/BaseObject.h"
#include "../../../include/Rendering/FrameBuffer.h"
#include "../../../include/Scene/Objects/Camera.h"
#include "../../../include/Scene/Objects/Light.h"
#include "../../../include/Types/Vector2.hpp"
#include <algorithm>
#include <cmath>

double3 Camera::rayThroughPixel(uint16_t x, uint16_t y, double fov) const {
    double3 look_vec_norm = (look_vec - position).normal();
    double3 right_vec = look_vec_norm.cross(up_vec).normal();
    double3 exact_up = right_vec.cross(look_vec_norm);

    double aspect_ratio = (double)(frameBuffer.sizeX()) / frameBuffer.sizeY();      // Aspect ratio
    double fov_horiz = 2 * atan(aspect_ratio * tan(fov / 2));  // Horizontal FOV

    double tan_fov_x = tan(0.5 * fov_horiz);
    double tan_fov_y = tan(0.5 * fov);

    double s_x = (x + 0.5) / frameBuffer.sizeX();
    double s_y = (y + 0.5) / frameBuffer.sizeY();

    double x2 = (2 * s_x - 1) * tan_fov_x;
    double y2 = (1 - 2 * s_y) * tan_fov_y;

    return (x2 * right_vec + y2 * exact_up + look_vec_norm).normal();
}
#include "../../../include/Scene/Objects/Camera.h"
#include "../../../include/Scene/Scene.h"

#include <cmath>

void Camera::_updateOrientation() {
    _look_vec_norm = (_look_vec - _position).normal();
    _right_vec = _look_vec_norm.cross(_up_vec).normal();
    _exact_up = _right_vec.cross(_look_vec_norm);
}

Camera::Camera() {
    Scene::addObject(this);
}

Camera::~Camera() {
    Scene::removeObject(this);
}

void Camera::positionAt(const double3& point) {
    _position = point;
    _updateOrientation();
}

void Camera::positionAt(double x, double y, double z) {
    positionAt(double3(x, y, z));
}

void Camera::translate(const double3& dp) {
    _position += dp;
    _updateOrientation();
}

void Camera::translate(double dx, double dy, double dz) {
    translate(double3(dx, dy, dz));
}

void Camera::setWorldUp(const double3& up_vec) {
    _up_vec = up_vec;
    _updateOrientation();
}

void Camera::setWorldUp(double x, double y, double z) {
    setWorldUp(double3(x, y, z));
}

void Camera::lookAt(const double3& point) {
    _look_vec = point;
    _updateOrientation();
}

void Camera::lookAt(double x, double y, double z) {
    lookAt(double3(x, y, z));
}

Ray Camera::rayThroughPixel(const size3& window_size, size_t x, size_t y) const {
    double s_x = (x + 0.5) / window_size.x;
    double s_y = (y + 0.5) / window_size.y;

    double x2 = (2 * s_x - 1) * _tan_fov_x;
    double y2 = (1 - 2 * s_y) * _tan_fov_y;

    return Ray(_position, (x2 * _right_vec + y2 * _exact_up + _look_vec_norm).normal());
}

void Camera::preRenderInit(const FrameBuffer& frameBuffer, double fov) {
    double aspect_ratio = (double)(frameBuffer.sizeX()) / frameBuffer.sizeY();      // Aspect ratio
    double fov_horiz = 2 * std::atan(aspect_ratio * std::tan(fov / 2));  // Horizontal FOV

    _tan_fov_x = std::tan(0.5 * fov_horiz);
    _tan_fov_y = std::tan(0.5 * fov);
}
#include "../../include/Scene/Camera.h"

Camera::Camera(const double3& pos, const double3& look_vector) {
    _look_vec = look_vector;
    _pos = pos;
}

Camera::Camera(const double3& pos) {
    _pos = pos;
}

Camera::Camera() {

}

void Camera::setLookVector(const double3& look_vec) {

}

void Camera::setPosition(const double3& pos) {

}
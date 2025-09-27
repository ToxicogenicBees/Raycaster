#include "../../include/Scene/Transformations.h"
#include <cmath>

Matrix<double> baseMat() {
    Matrix<double> matrix(4, 4);
    for (uint16_t i = 0; i < 4; i++)
        matrix(i, i) = 1;
    return matrix;
}

void Transformations::apply(Matrix<double> transformation, Point<double>& point) {
    Matrix<double> homog_coord(4, 1);

    homog_coord(0) = point.x;
    homog_coord(1) = point.y;
    homog_coord(2) = point.z;
    homog_coord(3) = 1;

    homog_coord = transformation * homog_coord;

    point.x = homog_coord(0) / homog_coord(3);
    point.y = homog_coord(1) / homog_coord(3);
    point.z = homog_coord(2) / homog_coord(3);
}

Matrix<double> Transformations::translation(double dx, double dy, double dz) {
    Matrix<double> transformation = baseMat();

    transformation(0, 3) = dx;
    transformation(1, 3) = dy;
    transformation(2, 3) = dz;

    return transformation;
}

Matrix<double> Transformations::translation(const Point<double>& dp) {
    return Transformations::translation(dp.x, dp.y, dp.z);
}

Matrix<double> Transformations::scale(double sx, double sy, double sz) {
    Matrix<double> transformation = baseMat();

    transformation(0, 0) *= sx;
    transformation(1, 1) *= sy;
    transformation(2, 2) *= sz;

    return transformation;
}

Matrix<double> Transformations::scale(Point<double> s) {
    return Transformations::scale(s.x, s.y, s.z);
}

Matrix<double> Transformations::scale(double s) {
    return Transformations::scale(s, s, s);
}

Matrix<double> Transformations::rotateX(double theta_x) {
    Matrix<double> transformation = baseMat();

    transformation(1, 1) = cos(theta_x);
    transformation(1, 2) = -sin(theta_x);
    transformation(2, 1) = sin(theta_x);
    transformation(2, 2) = cos(theta_x);

    return transformation;
}

Matrix<double> Transformations::rotateY(double theta_y) {
    Matrix<double> transformation = baseMat();

    transformation(0, 0) = cos(theta_y);
    transformation(0, 2) = sin(theta_y);
    transformation(2, 0) = -sin(theta_y);
    transformation(2, 2) = cos(theta_y);

    return transformation;
}

Matrix<double> Transformations::rotateZ(double theta_z) {
    Matrix<double> transformation = baseMat();

    transformation(0, 0) = cos(theta_z);
    transformation(0, 1) = -sin(theta_z);
    transformation(1, 0) = sin(theta_z);
    transformation(1, 1) = cos(theta_z);

    return transformation;
}

#include "../../include/Scene/Transformations.h"
#include <cmath>

Matrix<double> baseMat() {
    Matrix<double> matrix(4, 4);
    for (uint16_t i = 0; i < 4; i++)
        matrix(i, i) = 1;
    return matrix;
}

Point<double> apply(Matrix<double> transformation, Point<double> point) {
    Matrix<double> homog_coord(4, 1);

    homog_coord(0) = point.x;
    homog_coord(1) = point.y;
    homog_coord(2) = point.z;
    homog_coord(3) = 1;

    homog_coord = transformation * homog_coord;

    return Point<double>(
        homog_coord(0) / homog_coord(3),
        homog_coord(1) / homog_coord(3),
        homog_coord(2) / homog_coord(3)
    );
}

Matrix<double> translation(double x, double y, double z) {
    Matrix<double> transformation = baseMat();

    transformation(0, 3) = x;
    transformation(1, 3) = y;
    transformation(2, 3) = z;

    return transformation;
}

Matrix<double> translation(const Point<double>& t) {
    return translation(t.x, t.y, t.z);
}

Matrix<double> scale(double x, double y, double z) {
    Matrix<double> transformation = baseMat();

    transformation(0, 0) *= x;
    transformation(1, 1) *= y;
    transformation(2, 2) *= z;

    return transformation;
}

Matrix<double> scale(Point<double> s) {
    return scale(s.x, s.y, s.z);
}

Matrix<double> rotateX(double radians) {
    Matrix<double> transformation = baseMat();

    transformation(1, 1) = cos(radians);
    transformation(1, 2) = -sin(radians);
    transformation(2, 1) = sin(radians);
    transformation(2, 2) = cos(radians);

    return transformation;
}

Matrix<double> rotateY(double radians) {
    Matrix<double> transformation = baseMat();

    transformation(0, 0) = cos(radians);
    transformation(0, 2) = sin(radians);
    transformation(2, 0) = -sin(radians);
    transformation(2, 2) = cos(radians);

    return transformation;
}

Matrix<double> rotateZ(double radians) {
    Matrix<double> transformation = baseMat();

    transformation(0, 0) = cos(radians);
    transformation(0, 1) = -sin(radians);
    transformation(1, 0) = sin(radians);
    transformation(1, 1) = cos(radians);

    return transformation;
}

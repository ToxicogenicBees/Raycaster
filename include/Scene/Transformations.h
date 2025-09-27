#pragma once

#include "../Types/Matrix.hpp"
#include "../Types/Point.hpp"

namespace Transformations {
    void apply(Matrix<double> transformation, Point<double>& point);

    Matrix<double> translation(double dx, double dy, double dz);
    Matrix<double> translation(const Point<double>& dp);

    Matrix<double> scale(double sx, double sy, double sz);
    Matrix<double> scale(Point<double> s);
    Matrix<double> scale(double s);

    Matrix<double> rotateX(double theta_x);
    Matrix<double> rotateY(double theta_y);
    Matrix<double> rotateZ(double theta_z);
};
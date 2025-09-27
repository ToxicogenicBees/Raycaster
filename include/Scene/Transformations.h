#pragma once

#include "../Types/Matrix.hpp"
#include "../Types/Point.hpp"

namespace Transformations {
    Point<double> apply(Matrix<double> transformation, Point<double> point);

    Matrix<double> translation(double x, double y, double z);
    Matrix<double> translation(const Point<double>& t);

    Matrix<double> scale(double x, double y, double z);
    Matrix<double> scale(Point<double> s);

    Matrix<double> rotateX(double radians);
    Matrix<double> rotateY(double radians);
    Matrix<double> rotateZ(double radians);
};
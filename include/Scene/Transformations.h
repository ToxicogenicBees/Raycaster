#pragma once

#include "../Types/Matrix.hpp"
#include "../Types/Point.hpp"

namespace Transformations {
    /**
     * @brief Applies the desired transformation to a point
     * 
     * @param transformation    The desired transformation matrix
     * @param point             The point being transformed
     */
    void apply(Matrix<double> transformation, Point<double>& point);

    /***
     * @brief Constructs the translation matrix with the desired translation
     * 
     * @param dp    The desired position change
     * 
     * @return The resulting transformation matrix for this translation
     */
    Matrix<double> translation(const Point<double>& dp);

    /***
     * @brief Constructs the translation matrix with the desired translation
     * 
     * @param x     The desired x-position change
     * @param y     The desired y-position change
     * @param z     The desired z-position change
     * 
     * @return The resulting transformation matrix for this translation
     */
    Matrix<double> translation(double dx, double dy, double dz);

    /***
     * @brief Constructs the scaling matrix with the desired scale
     * 
     * @param s     The desired scale
     * 
     * @return The resulting transformation matrix for this scaling
     */
    Matrix<double> scale(Point<double> s);

    /***
     * @brief Constructs the scaling matrix with the desired scale
     * 
     * @param sx    The desired x-scale
     * @param sy    The desired y-scale
     * @param sz    The desired z-scale
     * 
     * @return The resulting transformation matrix for this scaling
     */
    Matrix<double> scale(double sx, double sy, double sz);

    /***
     * @brief Constructs the scaling matrix with the desired uniform scale
     * 
     * @param s     The desired uniform scale
     * 
     * @return The resulting transformation matrix for this uniform scaling
     */
    Matrix<double> scale(double s);

    /***
     * @brief Constructs the rotation matrix along the x-axis for a desired angle
     * 
     * @param theta_x   The desired rotation, in radians
     * 
     * @return The resulting transformation matrix for this rotation
     */
    Matrix<double> rotateX(double theta_x);

    /***
     * @brief Constructs the rotation matrix along the y-axis for a desired angle
     * 
     * @param theta_y   The desired rotation, in radians
     * 
     * @return The resulting transformation matrix for this rotation
     */
    Matrix<double> rotateY(double theta_y);

    /***
     * @brief Constructs the rotation matrix along the z-axis for a desired angle
     * 
     * @param theta_z   The desired rotation, in radians
     * 
     * @return The resulting transformation matrix for this rotation
     */
    Matrix<double> rotateZ(double theta_z);
};
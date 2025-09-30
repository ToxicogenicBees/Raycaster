#pragma once

#include <iostream>
#include <cmath>

template <class T>
struct Point {
    // The x-, y-, and z-components of the point
    T x, y, z;

    /***
     * @brief Creates a point with the desired x-, y-, and z-components
     * 
     * @param x     The desired x-component
     * @param y     The desired y-component
     * @param z     The desired z-component
     */
    Point(T x = T(), T y = T(), T z = T());

    /***
     * @brief Creates a point copying the values of another point
     * 
     * @param point The point being copied
     */
    Point(const Point& point);

    /***
     * @brief Overloaded assignment operator
     * 
     * @param point Another point object
     * 
     * @return A reference to this point
     */
    Point& operator=(const Point& point);
    
    /***
     * @brief Overloaded addition operator
     * 
     * @param point Another point object
     * 
     * @return The resulting point
     */
    Point operator+(const Point& point) const;

    /***
     * @brief Overloaded chained addition + assignment operator
     * 
     * @param point Another point object
     */
    void operator+=(const Point& point);
    
    /***
     * @brief Overloaded subtraction operator
     * 
     * @param point Another point object
     * 
     * @return The resulting point
     */
    Point operator-(const Point& point) const;

    /***
     * @brief Overloaded chained subtraction + assignment operator
     * 
     * @param point Another point object
     */
    void operator-=(const Point& point);

    /***
     * @brief Overloaded unary negation operator
     * 
     * @param point Another point object
     * 
     * @return The resulting point
     */
    Point operator-() const;

    /***
     * @brief Overloaded multiplication operator [Hadamard (component-wise) product]
     * 
     * @param point Another point object
     * 
     * @return The Hadamard (component-wise) product of the points
     */
    Point operator*(const Point& point) const;
    
    /***
     * @brief Overloaded multiplication operator
     * 
     * @param s     A scalar value
     * 
     * @return The resulting point
     */
    Point operator*(T s) const;

    /***
     * @brief Overloaded chained multiplication + assignment operator [Hadamard (component-wise) product]
     * 
     * @param point Another point object
     */
    void operator*=(const Point& point);

    /***
     * @brief Overloaded chained multiplication + assignment operator
     * 
     * @param s     A scalar value
     */
    void operator*=(T s);

    /***
     * @brief Overloaded division operator [Hadamard (component-wise) quotient]
     * 
     * @param point Another point object
     * 
     * @return The Hadamard (component-wise) quotient of the points
     */
    Point operator/(const Point& point) const;
    
    /***
     * @brief Overloaded division operator
     * 
     * @param s     A scalar value
     * 
     * @return The resulting point
     */
    Point operator/(T s) const;

    /***
     * @brief Overloaded chained division + assignment operator [Hadamard (component-wise) quotient]
     * 
     * @param point Another point object
     */
    void operator/=(const Point& point);

    /***
     * @brief Overloaded chained division + assignment operator
     * 
     * @param s     A scalar value
     */
    void operator/=(T s);
    
    /***
     * @brief Calculate the cross product between this point and another point
     * 
     * @param point Another point object
     * 
     * @return The cross product
     */
    Point cross(const Point& point) const;

    /***
     * @brief Calculate the dot product between this point and another point
     * 
     * @param point Another point object
     * 
     * @return The dot product
     */
    T dot(const Point& point) const;

    /***
     * @brief Calculate the normal of this point
     * 
     * @return The normal of this point
     */
    Point normal() const;

    /***
     * @brief Calculate the magnitude of this point
     * 
     * @return The magnitude of this point
     */
    T magnitude() const;

    /***
     * @brief Calculate the squared magnitude of this point
     * 
     * @return The squared magnitude of this point
     */
    T squaredMagnitude() const;

    /***
     * @brief Overloaded insertion operator
     * 
     * @param o     A reference to an output stream
     * @param point The point being output to the stream
     * 
     * @result A reference to the output stream being output to
     */
    friend std::ostream& operator<<(std::ostream& o, const Point<T>& point) {
        o << "(" << point.x << ", " << point.y << ", " << point.z << ")";
        return o;
    }
};

using double3 = Point<double>;
using Color = Point<double>;

template <class T>
Point<T>::Point(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Point<T>::Point(const Point<T>& point) {
    x = point.x;
    y = point.y;
    z = point.z;
}

template <class T>
Point<T>& Point<T>::operator=(const Point<T>& point) {
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
}

template <class T>
Point<T> Point<T>::operator+(const Point<T>& point) const {
    return Point<T>(x + point.x, y + point.y, z + point.z);
}

template <class T>
void Point<T>::operator+=(const Point<T>& point) {
    x += point.x;
    y += point.y;
    z += point.z;
}

template <class T>
Point<T> Point<T>::operator-(const Point<T>& point) const {
    return Point(x - point.x, y - point.y, z - point.z);
}

template <class T>
void Point<T>::operator-=(const Point<T>& point) {
    x -= point.x;
    y -= point.y;
    z -= point.z;
}

template <class T>
Point<T> Point<T>::operator-() const {
    return Point(-x, -y, -z);
}

template <class T>
Point<T> Point<T>::operator*(const Point& point) const {
    return Point(x * point.x, y * point.y, z * point.z);
}

template <class T>
Point<T> operator*(T s, const Point<T>& point) {
    return point * s;
}

template <class T>
Point<T> Point<T>::operator*(T s) const {
    return Point(x * s, y * s, z * s);
}

template <class T>
void Point<T>::operator*=(const Point& point) {
    x *= point.x;
    y *= point.y;
    z *= point.z;
}

template <class T>
void Point<T>::operator*=(T s) {
    x *= s;
    y *= s;
    z *= s;
}

template <class T>
Point<T> Point<T>::operator/(const Point& point) const {
    return Point(x / point.x, y / point.y, z / point.z);
}

template <class T>
Point<T> operator/(T s, const Point<T>& point) {
    return point / s;
}

template <class T>
Point<T> Point<T>::operator/(T s) const {
    return Point(x / s, y / s, z / s);
}

template <class T>
void Point<T>::operator/=(const Point& point) {
    x /= point.x;
    y /= point.y;
    z /= point.z;
}

template <class T>
void Point<T>::operator/=(T s) {
    x /= s;
    y /= s;
    z /= s;
}

template <class T>
Point<T> Point<T>::cross(const Point<T>& point) const {
    return Point(
        y * point.z - z * point.y,
        z * point.x - x * point.z,
        x * point.y - y * point.x
    );
}

template <class T>
T Point<T>::dot(const Point<T>& point) const {
    return (x * point.x) + (y * point.y) + (z * point.z);
}

template <class T>
Point<T> Point<T>::normal() const {
    double mag = magnitude();
    return (mag != 0 ? (*this / mag) : *this);
}

template <class T>
T Point<T>::magnitude() const {
    return std::sqrt(dot(*this));
}

template <class T>
T Point<T>::squaredMagnitude() const {
    return dot(*this);
}
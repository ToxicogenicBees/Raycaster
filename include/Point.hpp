#pragma once

#include <cmath>

template <class T>
struct Point {
    T x, y, z;

    Point(T x = 0.0, T y = 0.0, T z = 0.0);
    Point(const Point& point);

    Point& operator=(const Point& point);
    
    Point operator+(const Point& point) const;
    void operator+=(const Point& point);
    
    Point operator-(const Point& point) const;
    void operator-=(const Point& point);
    Point operator-();
    
    Point operator*(T s) const;
    void operator*=(T s);
    
    Point operator/(T s) const;
    void operator/=(T s);
    
    Point normal() const;
    T magnitude() const;
    T squaredMagnitude() const;
};

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
Point<T> Point<T>::operator-() {
    return Point(-x, -y, -z);
}

template <class T>
Point<T> operator*(T s, const Point<T>& p) {
    return p * s;
}

template <class T>
Point<T> Point<T>::operator*(T s) const {
    return Point(x * s, y * s, z * s);
}

template <class T>
void Point<T>::operator*=(T s) {
    x *= s;
    y *= s;
    z *= s;
}

template <class T>
Point<T> operator/(T s, const Point<T>& p) {
    return p / s;
}

template <class T>
Point<T> Point<T>::operator/(T s) const {
    return Point(x / s, y / s, z / s);
}

template <class T>
void Point<T>::operator/=(T s) {
    x /= s;
    y /= s;
    z /= s;
}

template <class T>
Point<T> cross(const Point<T>& p1, const Point<T>& p2) {
    return Point(
        p1.y * p2.z - p1.z * p2.y,
        p1.z * p2.x - p1.x * p2.z,
        p1.x * p2.y - p1.y * p2.x
    );
}

template <class T>
T dot(const Point<T>& p1, const Point<T>& p2) {
    return (p1.x * p2.x) + (p1.y * p2.y) + (p1.z * p2.z);
}

template <class T>
Point<T> Point<T>::normal() const {
    double mag = magnitude();
    return (mag != 0 ? (*this / mag) : *this);
}

template <class T>
T Point<T>::magnitude() const {
    return sqrt(x * x + y * y + z * z);
}

template <class T>
T Point<T>::squaredMagnitude() const {
    return dot(*this, *this);
}
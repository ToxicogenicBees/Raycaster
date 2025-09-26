#pragma once

#include <stdint.h>

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
    
    Point cross(const Point& point) const;
    T dot(const Point& point) const;
    Point normal() const;
    T magnitude() const;
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
Point<T> Point<T>::cross(const Point<T>& point) const {
    return Point(
        y * point.z - z * point.y,
        z * point.x - x * point.z,
        x * point.y - y * point.x
    );
}

template <class T>
T Point<T>::dot(const Point<T>& point) const {
    return x * point.x + y * point.y + z * point.z;
}

template <class T>
Point<T> Point<T>::normal() const {
    return *this / magnitude();
}

template <class T>
T Point<T>::magnitude() const {
    return sqrt(x * x + y * y + z * z);
}
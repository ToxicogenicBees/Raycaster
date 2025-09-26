#pragma once

#include <stdint.h>

template <class T>
struct Point {
    T x, y, z;

    Point(T x = 0.0, T y = 0.0, T z = 0.0);

    Point& operator=(const Point& point);
    
    Point operator+(const Point& point);
    void operator+=(const Point& point);
    
    Point operator-(const Point& point);
    void operator-=(const Point& point);
    Point operator-();
    
    Point cross(const Point& point);
    T dot(const Point& point);
    Point operator*(T s);
    void operator*=(T s);
    
    Point operator/(T s);
    void operator/=(T s);
};

template <class T>
Point<T>::Point(T x, T y, T z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

template <class T>
Point<T>& Point<T>::operator=(const Point<T>& point) {
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
}

template <class T>
Point<T> Point<T>::operator+(const Point<T>& point) {
    return Point<T>(x + point.x, y + point.y, z + point.z);
}

template <class T>
void Point<T>::operator+=(const Point<T>& point) {
    x += point.x;
    y += point.y;
    z += point.z;
}

template <class T>
Point<T> Point<T>::operator-(const Point<T>& point) {
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
Point<T> Point<T>::cross(const Point<T>& point) {
    return Point(
        y * point.z - z * point.y,
        z * point.x - x * point.z,
        x * point.y - y * point.x
    );
}

template <class T>
T Point<T>::dot(const Point<T>& point) {
    return x * point.x + y * point.y + z * point.z;
}

template <class T>
Point<T> Point<T>::operator*(T s) {
    return Point(x * s, y * s, z * s);
}

template <class T>
void Point<T>::operator*=(T s) {
    x *= s;
    y *= s;
    z *= s;
}

template <class T>
Point<T> Point<T>::operator/(T s) {
    return Point(x / s, y / s, z / s);
}

template <class T>
void Point<T>::operator/=(T s) {
    x /= s;
    y /= s;
    z /= s;
}
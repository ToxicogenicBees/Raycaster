#pragma once

#include <iostream>
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
    Point operator-() const;
    
    Point operator*(T s) const;
    void operator*=(T s);
    
    Point operator/(T s) const;
    void operator/=(T s);
    
    Point cross(const Point& p) const;
    T dot(const Point& p) const;
    Point normal() const;
    T magnitude() const;
    T squaredMagnitude() const;

    friend std::ostream& operator<<(std::ostream& o, const Point<T>& p) {
        o << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return o;
    }
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
Point<T> Point<T>::operator-() const {
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
Point<T> Point<T>::cross(const Point<T>& p) const {
    return Point(
        y * p.z - z * p.y,
        z * p.x - x * p.z,
        x * p.y - y * p.x
    );
}

template <class T>
T Point<T>::dot(const Point<T>& p) const {
    return (x * p.x) + (y * p.y) + (z * p.z);
}

template <class T>
Point<T> Point<T>::normal() const {
    double mag = magnitude();
    return (mag != 0 ? (*this / mag) : *this);
}

template <class T>
T Point<T>::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

template <class T>
T Point<T>::squaredMagnitude() const {
    return dot(*this);
}
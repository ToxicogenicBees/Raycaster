#include "../include/Point.h"

Point::Point(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Point& Point::operator=(const Point& point) {
    x = point.x;
    y = point.y;
    z = point.z;

    return *this;
}
    
Point Point::operator+(const Point& point) {
    return Point(x + point.x, y + point.y, z + point.z);
}

void Point::operator+=(const Point& point) {
    x += point.x;
    y += point.y;
    z += point.z;
}
    
Point Point::operator-(const Point& point) {
    return Point(x - point.x, y - point.y, z - point.z);
}

void Point::operator-=(const Point& point) {
    x -= point.x;
    y -= point.y;
    z -= point.z;
}

Point Point::operator-() {
    return Point(-x, -y, -z);
}
    
Point Point::cross(const Point& point) {
    return Point(
        y * point.z - z * point.y,
        z * point.x - x * point.z,
        x * point.y - y * point.x
    );
}

double Point::dot(const Point& point) {
    return x * point.x + y * point.y + z * point.z;
}

Point Point::operator*(double s) {
    return Point(x * s, y * s, z * s);
}

void Point::operator*=(double s) {
    x *= s;
    y *= s;
    z *= s;
}
    
Point Point::operator/(double s) {
    return Point(x / s, y / s, z / s);
}
void Point::operator/=(double s) {
    x /= s;
    y /= s;
    z /= s;
}
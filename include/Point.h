#pragma once

struct Point {
    double x, y, z;

    Point(double x = 0.0, double y = 0.0, double z = 0.0);

    Point& operator=(const Point& point);
    
    Point operator+(const Point& point);
    void operator+=(const Point& point);
    
    Point operator-(const Point& point);
    void operator-=(const Point& point);
    Point operator-();
    
    Point cross(const Point& point);
    double dot(const Point& point);
    Point operator*(double s);
    void operator*=(double s);
    
    Point operator/(double s);
    void operator/=(double s);
};
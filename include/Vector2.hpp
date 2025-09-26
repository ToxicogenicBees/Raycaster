#pragma once

#include "Point.hpp"
#include <stdint.h>
#include <vector>

template <class T>
class Vector2 {
    private:
        std::vector<std::vector<T>> _data;
        uint16_t _size_x, _size_y;

    public:
        Vector2(uint16_t size_x, uint16_t size_y);
        Vector2(const Point<uint16_t>& size);

        std::vector<T>& operator[](uint16_t index);
        
        void resize(uint16_t size_x, uint16_t size_y);
        void resize(const Point<uint16_t>& size);
        void fill(const T& value);

        uint16_t sizeX() { return _size_x; }
        uint16_t sizeY() { return _size_y; }
};

template <class T>
Vector2<T>::Vector2(uint16_t size_x, uint16_t size_y) {
    resize(size_x, size_y);
}

template <class T>
Vector2<T>::Vector2(const Point<uint16_t>& size) {
    resize(size.x, size.y);
}

template <class T>
void Vector2<T>::resize(uint16_t size_x, uint16_t size_y) {
    _size_x = size_x;
    _size_y = size_y;

    _data.resize(_size_y);
    for (uint16_t y = 0; y < _size_y; y++)
        _data[y].resize(_size_x);
}

template <class T>
void Vector2<T>::resize(const Point<uint16_t>& size) {
    resize(size.x, size.y);
}

template <class T>
std::vector<T>& Vector2<T>::operator[](uint16_t index) {
    return _data[index];
}

template <class T>
void Vector2<T>::fill(const T& value) {
    for (uint16_t i = 0; i < _size_y; i++) {
        for (uint16_t j = 0; j < _size_x; j++) {
            _data[i][j] = value;
        }
    }
}
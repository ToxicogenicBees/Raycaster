#pragma once

#include "Types/Point.hpp"
#include <stdint.h>
#include <vector>

template <class T>
class Vector2 {
    private:
        // Grid of nested vectors
        std::vector<std::vector<T>> _data;

        // Size in both x and y
        uint16_t _size_x, _size_y;

    public:
        /***
         * @brief Creates a grid of vectors of the desired size
         * 
         * @param size_x    The desired width of the grid
         * @param size_y    The desired height of the grid
         */
        Vector2(uint16_t size_x = 0, uint16_t size_y = 0);

        /***
         * @brief Creates a grid of vectors of the desired size
         * 
         * @param size      The desired (x, y) size of the grid
         */
        Vector2(const Point<uint16_t>& size);

        /***
         * @brief Creates a grid of vectors copying the values of another grid of vectors
         * 
         * @param vec2      The grid being copied
         */
        Vector2(const Vector2& vec2);

        /***
         * @brief Overloaded subscript operator, accessing a row of a constant Vector2
         * 
         * @param index The desired y-index
         * 
         * @return Constant reference to the desired row of data
         */
        const std::vector<T>& operator[](uint16_t index) const;

        /***
         * @brief Overloaded subscript operator, accessing a row of a Vector2
         * 
         * @param index The desired y-index
         * 
         * @return Reference to the desired row of data
         */
        std::vector<T>& operator[](uint16_t index);
        
        /***
         * @brief Overloaded assignment operator
         * 
         * @param vec2 Another Vector2 object
         * 
         * @return A reference to this Vector2
         */
        Vector2& operator=(const Vector2& vec2);

        /***
         * @brief Resizes the Vector2 to be able to store the specific number of elements
         * 
         * @param size      The desired (x, y) size
         */
        void resize(const Point<uint16_t>& size);
        
        /***
         * @brief Resizes the Vector2 to be able to store the specific number of elements
         * 
         * @param size_x    The desired width
         * @param size_y    The desired height
         */
        void resize(uint16_t size_x, uint16_t size_y);

        /***
         * @brief Fill all the entries of the Vector2 with a specific value
         * 
         * @param value The desired value
         */
        void fill(const T& value);

        /***
         * @brief Get the width of this Vector2
         * 
         * @return The width of this Vector2
         */
        uint16_t sizeX() const { return _size_x; }

        /***
         * @brief Get the height of this Vector2
         * 
         * @return The height of this Vector2
         */
        uint16_t sizeY() const { return _size_y; }
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
Vector2<T>::Vector2(const Vector2& vec2) {
    _size_x = vec2._size_x;
    _size_y = vec2._size_y;
    _data = vec2._data;
}

template <class T>
void Vector2<T>::resize(const Point<uint16_t>& size) {
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
const std::vector<T>& Vector2<T>::operator[](uint16_t index) const {
    return _data[index];
}

template <class T>
std::vector<T>& Vector2<T>::operator[](uint16_t index) {
    return _data[index];
}

template <class T>
Vector2<T>& Vector2<T>::operator=(const Vector2& vec2) {
    _size_x = vec2._size_x;
    _size_y = vec2._size_y;
    _data = vec2._data;

    return *this;
}

template <class T>
void Vector2<T>::fill(const T& value) {
    for (uint16_t i = 0; i < _size_y; i++) {
        for (uint16_t j = 0; j < _size_x; j++) {
            _data[i][j] = value;
        }
    }
}
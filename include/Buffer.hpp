#pragma once

#include <stdint.h>

template <class T>
class Buffer {
    private:
        const uint16_t SIZE_X, SIZE_Y;
        T** buffer;

    public:
        Buffer(uint16_t size_x, uint16_t size_y);
        ~Buffer();

        T* operator[](uint16_t index);
        void fill(const T& value);
};

template <class T>
Buffer<T>::Buffer(uint16_t size_x, uint16_t size_y) : SIZE_X(size_x), SIZE_Y(size_y) {
    buffer = new T*[SIZE_Y];

    for (uint16_t i = 0; i < SIZE_Y; i++)
        buffer[i] = new T[SIZE_X];
}

template <class T>
Buffer<T>::~Buffer() {
    for (uint16_t i = 0; i < SIZE_Y; i++)
        delete[] buffer[i];

    delete[] buffer;
}

template <class T>
T* Buffer<T>::operator[](uint16_t index) {
    return buffer[index];
}

template <class T>
void Buffer<T>::fill(const T& value) {
    for (uint16_t i = 0; i < SIZE_Y; i++) {
        for (uint16_t j = 0; j < SIZE_X; j++) {
            buffer[i][j] = value;
        }
    }
}
#pragma once

#include "Vector2.hpp"
#include <stdexcept>
#include <iostream>

template <class T>
class Matrix {
    private:
        uint16_t _rows, _cols;      // Matrix rows and columns
        Vector2<T> _data;           // Matrix entries

    public:
        Matrix(uint16_t rows, uint16_t cols, const T& init_val);
        Matrix(uint16_t rows, uint16_t cols);
        Matrix(const Matrix& m);

        const T& operator()(uint16_t row, uint16_t col) const;
        const T& operator()(uint16_t index) const;
        T& operator()(uint16_t row, uint16_t col);
        T& operator()(uint16_t index);

        Matrix& operator=(const Matrix& m);

        Matrix operator+(const Matrix& m) const;
        void operator+=(const Matrix& m);

        Matrix operator-(const Matrix& m) const;
        void operator-=(const Matrix& m);

        Matrix operator*(const Matrix& m) const;
        Matrix operator*(T s) const noexcept;
        void operator*=(const Matrix& m);
        void operator*=(T s) noexcept;

        Matrix operator/(T s) const noexcept;
        void operator/=(T s) noexcept;

        uint16_t rows() const { return _rows; }
        uint16_t cols() const { return _cols; }

        friend std::ostream& operator<<(std::ostream& o, const Matrix<T>& m) {
            for (uint16_t row = 0; row < m._rows; row++) {
                for (uint16_t col = 0; col < m._cols; col++) {
                    o << m(row, col) << (col == m._cols - 1 ? "\n" : " ");
                }
            }

            return o;
        }
};

template <class T>
Matrix<T>::Matrix(uint16_t rows, uint16_t cols, const T& init_val) {
    _data.resize(rows, cols);
    _rows = rows;
    _cols = cols;

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            set(i, j, init_val);
        }
    }
}

template <class T>
Matrix<T>::Matrix(uint16_t rows, uint16_t cols) {
    _data.resize(rows, cols);
    _rows = rows;
    _cols = cols;
}

template <class T>
Matrix<T>::Matrix(const Matrix& m) {
    _data = m._data;
    _rows = m._rows;
    _cols = m._cols;
}

template <class T>
const T& Matrix<T>::operator()(uint16_t row, uint16_t col) const {
    if (row >= _rows || col >= _cols)
        throw std::out_of_range("Index out of range");
    return _data[col][row];
}

template <class T>
const T& Matrix<T>::operator()(uint16_t index) const {
    if (_rows > 1 && _cols > 1)
        throw std::invalid_argument("Matrix isn't a vector, requires multiple indexes");
    if (index >= (_rows > _cols ? _rows : _cols))
        throw std::out_of_range("Index out of range");
    return (_cols == 1 ? _data[0][index] : _data[index][0]);
}

template <class T>
T& Matrix<T>::operator()(uint16_t row, uint16_t col) {
    if (row >= _rows || col >= _cols)
        throw std::out_of_range("Index out of range");
    return _data[col][row];
}

template <class T>
T& Matrix<T>::operator()(uint16_t index) {
    if (_rows > 1 && _cols > 1)
        throw std::invalid_argument("Matrix isn't a vector, requires multiple indexes");
    if (index >= (_rows > _cols ? _rows : _cols))
        throw std::out_of_range("Index out of range");
    return (_cols == 1 ? _data[0][index] : _data[index][0]);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m) {
    _data = m._data;
    _rows = m._rows;
    _cols = m._cols;

    return *this;
}

template <class T>
Matrix<T> Matrix<T>::operator+(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols)
        throw std::invalid_argument("Incompatible matrix sizes");

    Matrix result(_rows, _cols);

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            result(i, j) = (i, j) + m(i, j);
        }
    }

    return result;
}

template <class T>
void Matrix<T>::operator+=(const Matrix& m) {
    if (_rows != m._rows || _cols != m._cols)
        throw std::invalid_argument("Incompatible matrix sizes");

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            (*this)(i, j) += m(i, j);
        }
    }
}

template <class T>
Matrix<T> Matrix<T>::operator-(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols)
        throw std::invalid_argument("Incompatible matrix sizes");

    Matrix result(_rows, _cols);

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            result(i, j) = (*this)(i, j) - m(i, j);
        }
    }

    return result;
}

template <class T>
void Matrix<T>::operator-=(const Matrix& m) {
    if (_rows != m._rows || _cols != m._cols)
        throw std::invalid_argument("Incompatible matrix sizes");

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            (*this)(i, j) -= m(i, j);
        }
    }
}

template <class T>
Matrix<T> Matrix<T>::operator*(const Matrix& m) const {
    if (_cols != m._rows)
        throw std::invalid_argument("Incompatible matrix sizes");

    Matrix result(_rows, m._cols);

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < m._cols; j++) {
            T sum = T();
            for (uint16_t k = 0; k < _cols; k++)
                sum += (*this)(i, k) * m(k, j);
            result(i, j) = sum;
        }
    }

    return result;
}

template <class T>
Matrix<T> Matrix<T>::operator*(T s) const noexcept {
    Matrix result(_rows, _cols);

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            result(i, j) = (*this)(i, j) * s;
        }
    }

    return result;
}

template <class T>
void Matrix<T>::operator*=(const Matrix& m) {
    (*this) = (*this) * m;
}

template <class T>
void Matrix<T>::operator*=(T s) noexcept {
    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            (*this)(i, j) *= s;
        }
    }
}

template <class T>
Matrix<T> Matrix<T>::operator/(T s) const noexcept {
    Matrix result(_rows, _cols);

    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            result(i, j) = (*this)(i, j) / s;
        }
    }

    return result;
}

template <class T>
void Matrix<T>::operator/=(T s) noexcept {
    for (uint16_t i = 0; i < _rows; i++) {
        for (uint16_t j = 0; j < _cols; j++) {
            (*this)(i, j) /= s;
        }
    }
}

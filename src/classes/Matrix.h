//
// Created by rysan on 21/12/23.
//
#pragma once
#include <vector>
#include <iostream>
#include "cell.h"

template <class T>
class Matrix {
private:
    int _rows, _cols;

    void allocSpace();
    T **p;

public:
    Matrix(int, int, T);  // Based on the shape and a initializer element
    Matrix(int, int, T**);  // From an existing matrix
    Matrix() : _rows(1), _cols(1) { allocSpace(); }
    ~Matrix() = default;
    Matrix(const Matrix<T>&);
    Matrix& operator=(const Matrix<T>&);

    inline T& operator()(int x, int y) { return p[x][y]; }  // Getting an element based on the position

    // Getters
    int getRows() const {return _rows;}
    int getCols() const {return _cols;}
    T** getPoin() const {return p;}
};

std::ostream& operator<<(std::ostream&, const Matrix<int>&);
std::ostream& operator<<(std::ostream&, const Matrix<bool>&);
std::ostream& operator<<(std::ostream&, const Matrix<Cell>&);

// ****************************************************************************************************
// Created by rysan on 21/12/23.
// Based on the matrix implementation by https://github.com/akalicki/matrix.git
//
// PS.: this implementation utilizes vectors to represent the 2D array, which is not
//      indicated if efficiency is core to the project; as the vectors may be scattered around memory
// ****************************************************************************************************
//

#pragma once
#include <vector>
#include <iostream>
#include "cell.h"

template <class T>
class Matrix {
private:
    int _rows;
    int _cols;

    void allocSpace();
    std::vector<std::vector<T>> _matrix;

public:
    Matrix(int, int, T);  // Based on the shape and an initializer element
    Matrix(int, int, T**);  // From an existing matrix
    Matrix() : _rows(1), _cols(1) { allocSpace(); }
    ~Matrix() = default;
    Matrix(const Matrix<T>&);
    Matrix& operator=(const Matrix<T>&);

    inline T& operator()(int x, int y) { return _matrix[x][y]; }  // Getting an element based on the position

    // Getters
    [[nodiscard]] int getRows() const {return _rows;}
    [[nodiscard]] int getCols() const {return _cols;}
    std::vector<std::vector<T>> getPoin() const {return _matrix;}

    void update();

    std::vector<T> check_surroundings(int,int,int);
    void generate_life(int);
    void alternateCell(int i, int j);
    void KILL();
};

std::ostream& operator<<(std::ostream&, const Matrix<int>&);
std::ostream& operator<<(std::ostream&, const Matrix<bool>&);
std::ostream& operator<<(std::ostream&, const Matrix<Cell>&);

//
// Created by rysan on 21/12/23.
//

#include "Matrix.h"
#include <random>

// This creates a new matrix based on the needed space
template <class T>
void Matrix<T>::allocSpace()
{
  // First creates the rows
  _matrix.resize(_rows);
  // For each space, creates another vector to represent the columns
  for(auto& c : _matrix)
    c.resize(_cols);
}

/* PUBLIC MEMBER FUNCTIONS */
// CONSTRUCTORS
template<class T>
Matrix<T>::Matrix(int rows, int cols, T e) : _rows(rows), _cols(cols)
{
  allocSpace();
  for (const auto& row : _matrix)
    for (auto elem : row)
      elem = e;
}

template<class T>
Matrix<T>::Matrix(int rows, int cols, T** a) : _rows(rows), _cols(cols)
{
  allocSpace();
  for(int i = 0; i < _rows; ++i)
    for(int j = 0; j < cols; ++j)
      _matrix[i][j] = a[i][j];
}

template<class T>
Matrix<T>::Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols), _matrix(m._matrix) {}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m)
{
  if(this == &m) return *this;

  // Destroy the matrix if their shape is different
  if(_rows != m._rows || _cols != m._cols)
  {
    // Reshape it
    _rows = m._rows;
    _cols = m._cols;
    allocSpace();
  }

  // Populates it with the elements of tbe other matrix
  _matrix = m._matrix;
  return *this;
}

// Receives the indexes and returns a vector with all the neighbours
template <class T> std::vector<T> Matrix<T>::check_surroundings(int i, int j, int distance)
{
  std::vector<T> neighbours;

  for(int l = i-1; l <= distance + i; l++)
    for(int y = j-1; y <= distance + j; y++)
      if(!(l == i && y == j) &&       // Not add the central
          (l >= 0 && l < _rows) &&    // Check if l is within bounds
          (y >= 0 && y < _cols))      // Check if y is within bounds
        neighbours.push_back(_matrix[l][y]);
  return neighbours;
}


// Represents a time-step on the board
template<> void Matrix<Cell>::update() {
  short count = 0;

  // Inform each cell how many neighbours are alive
  for (int i = 0; i < getRows(); i++)
    for (int j = 0; j < getCols(); j++)
    {
      count = 0;
      for (auto c : check_surroundings(i,j,1)) if (c.isAlive()) count++;
      _matrix[i][j].inform_neighbours(count);
    }

  // Update each cell at the matrix
  for(auto& row : _matrix)
    for(auto& cell : row)
      cell.update();
}


template<> void Matrix<Cell>::generate_life(int prob) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<int> dist(0,100);

  for(auto& row : _matrix)
    for(auto& cell : row)
    {
      int num = dist(mt);
      if(num < prob) cell.force_born();
    }
}


// For printing and showing the matrix
std::ostream& operator<<(std::ostream& os, const Matrix<int>& m)
{
  auto matrix = m.getPoin();
  for (auto const& row : matrix)
  {
    for (auto cell : row) os << " " << cell;
    os << std::endl;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix<bool>& m)
{
  auto matrix = m.getPoin();
  for (auto const& row : matrix)
  {
    for (auto cell : row) os << " " << cell;
    os << std::endl;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix<Cell>& m)
{
  auto matrix = m.getPoin();
  for (auto const& row : matrix)
  {
    for (auto cell : row)
    {
      os << " ";
      cell.isAlive() ? os << "\u2588" : os << "\u253c";
    }
    os << std::endl;
  }
  return os;
}

template class Matrix<int>;
template class Matrix<Cell>;

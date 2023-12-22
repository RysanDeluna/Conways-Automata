//
// Created by rysan on 21/12/23.
//

#include "Matrix.h"
#include <vector>
#include <random>

/* ALLOC FUNCTION */

// This creates a new matrix based on the needed space
template <class T>
void Matrix<T>::allocSpace()
{
  // First creates the rows
  p = new T*[_rows];
  // For each space, creates another vector to represent the columns
  for(int i = 0; i < _rows; i++)
    p[i] = new T[_cols];
}

/* PUBLIC MEMBER FUNCTIONS */


// CONSTRUCTORS
template<class T>
Matrix<T>::Matrix(int rows, int cols, T e) : _rows(rows), _cols(cols)
{
  allocSpace();
  for(int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++)
      p[i][j] = e;
}

template<class T>
Matrix<T>::Matrix(int rows, int cols, T** a) : _rows(rows), _cols(cols)
{
  allocSpace();
  for(int i = 0; i < _rows; ++i)
    for(int j = 0; j < cols; ++j)
      p[i][j] = a[i][j];
}

template<class T>
Matrix<T>::Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols)
{
  allocSpace();
  for(int i = 0; i < _rows; i++)
    for(int j = 0; j < _cols; j++)
      p[i][j] = m.p[i][j];
}

template<class T>
Matrix<T>& Matrix<T>::operator=(const Matrix& m)
{
  if(this == &m) return *this;

  // Destroy the matrix if their shape is different
  if(_rows != m._rows || _cols != m._cols)
  {
    for (int i = 0; i < _rows; i++) delete[] p[i];
    delete[] p;

    // Construct a new one exactly the same as the other
    _rows = m._rows;
    _cols = m._cols;
    allocSpace();
  }

  // Populates it with the elements of tbe other matrix
  for (int i = 0; i < _rows; i++)
    for (int j = 0; j < _cols; j++)
      p[i][j] = m.p[i][j];

  return *this;
}

// receives the indexes and returns a vector with all the neighbours
template <class T> std::vector<T> Matrix<T>::check_surroundings(int i, int j, int distance)
{
  std::vector<T> neighbours;
  // Case it has less than 8 neighbours (borders)

  for(int l = i-1; l < distance + i; l++)
  {
    for(int y = j-1; y < distance + j; y++)
    {
      if(!(l == i && y == j) &&       // Not add the central
          (l >= 0 && l < _rows) &&    // Check if l is within bounds
          (y >= 0 && y < _cols))      // Check if y is within bounds
        neighbours.push_back(p[l][y]);
    }
  }
  return neighbours;
}

template<> void Matrix<Cell>::update() {
  short count = 0;
  for (int i = 0; i < getRows(); i++)
  {
    for (int j = 0; j < getCols(); j++)
    {
      for (auto c : check_surroundings(i,j,1)) if (c.isAlive()) count++;
      p[i][j].inform_neighbours(count);
    }
  }

  for (int i = 0; i < getRows(); i++)
    for (int j = 0; j < getCols(); j++)
      p[i][j].update();
}



template<> void Matrix<Cell>::generate_life(int prob) {
  srand(time(NULL));
  for(int i = 0; i < getRows(); i++)
    for(int j = 0; j < getCols(); j++)
    {
      int num = rand() % 100;
      if(num < prob) p[i][j].force_born();
    }
}


// For printing and showing the matrix
std::ostream& operator<<(std::ostream& os, const Matrix<int>& m)
{
  for (int i = 0; i < m.getRows(); i++)
  {
    os << m.getPoin()[i][0];
    for (int j = 1; j < m.getCols(); j++) os << " " << m.getPoin()[i][j];
    os << std::endl;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix<bool>& m)
{
  for (int i = 0; i < m.getRows(); i++)
  {
    os << m.getPoin()[i][0];
    for (int j = 1; j < m.getCols(); j++) os << " " << m.getPoin()[i][j];
    os << std::endl;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Matrix<Cell>& m)
{
  for (int i = 0; i < m.getRows(); i++)
  {
    // First column
    m.getPoin()[i][0].isAlive() ? os << "\u2588" : os << "\u253c";
    for (int j = 1; j < m.getCols(); j++) // Second and so on...
    {
      os << " ";
      m.getPoin()[i][j].isAlive() ? os << "\u2588" : os << "\u253c";
    }
    os << std::endl;
  }
  return os;
}

template class Matrix<int>;
template class Matrix<bool>;
template class Matrix<Cell>;

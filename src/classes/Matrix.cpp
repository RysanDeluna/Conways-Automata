//
// Created by rysan on 21/12/23.
//

#include "Matrix.h"

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

template<class T>
void Matrix<T>::update() { // TODO
  // Check the type of elements

  // For Cells:
    // check its neighbours

    // Alters the neighbours quantities in all the cells objects

    // Update each Cell

  // Repeat for every element

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

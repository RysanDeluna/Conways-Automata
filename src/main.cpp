//
// Created by rysan on 21/12/23.
//
#include <iostream>
#include <cstdlib>
#include "classes/Matrix.h"

void clear() { std::cout << "\x1B[2J\x1B[H"; }

int main()
{
  Matrix<int> a (24,32,0);

  std::cout<<a;
  clear();
  std::cout<<a;
  return 0;
}
//
// Created by rysan on 21/12/23.
//
#include <iostream>
#include "classes/Matrix.h"
#include <random>

void clear() { std::cout << "\x1B[2J\x1B[H"; }

int main()
{
  Matrix<Cell> a (10,10,Cell());
  std::string coisa;

  a.generate_life(30);
  std::cout << a;
  std::cin >> coisa;

  a.update();

  std::cout << a;
  return 0;
}
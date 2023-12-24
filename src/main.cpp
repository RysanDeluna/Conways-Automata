//
// Created by rysan on 21/12/23.
//
#include <iostream>
#include "classes/Matrix.h"

void clear() { std::cout << "\x1B[2J\x1B[H"; }

int main()
{
  Matrix<Cell> Tabuleiro(16,16,Cell());
  Tabuleiro.generate_life(30);
  char input;

  // Loop of inputs
  do {
    std::cin >> input;
    system("cls");
    Tabuleiro.update();
    std::cout << Tabuleiro;
  } while(input != 'q');

  return 0;
}
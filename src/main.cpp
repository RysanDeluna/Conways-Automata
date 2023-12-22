//
// Created by rysan on 21/12/23.
//
#include <iostream>
#include <cstdlib>
#include "classes/Matrix.h"
#include <SFML/Graphics.hpp>

void clear() { std::cout << "\x1B[2J\x1B[H"; }

int main()
{
  Matrix<Cell> a (24,32,Cell());

  while(true)
  {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && timer < 0)
    {
      Matrix.update();
    }
  }

  std::cout << a;
  return 0;
}
//
// Created by rysan on 21/12/23.
//

#include "cell.h"

Cell::Cell() : _state(DEAD) {}

bool Cell::isAlive() { return _state==ALIVE; }

void Cell::born() { _state = ALIVE; }
void Cell::die()  { _state = DEAD;  }

void Cell::update(short neighbours_alive)
{
  switch (_state)
  {
    case ALIVE: if (neighbours_alive < 2 || neighbours_alive > 3) die(); break;
    case DEAD : if (neighbours_alive == 3) born(); break;
    default   : break;
  }
}
//
// Created by rysan on 21/12/23.
//

#include "cell.h"

Cell::Cell() : _state(DEAD), _neighbours(0) {}

bool Cell::isAlive() { return _state==ALIVE; }

void Cell::born() { _state = ALIVE; }
void Cell::die()  { _state = DEAD;  }

void Cell::update()
{
  switch (_state)
  {
    case ALIVE: if (_neighbours < 2 || _neighbours > 3) die(); break;
    case DEAD : if (_neighbours == 3) born(); break;
    default   : break;
  }
}

void Cell::inform_neighbours(short neighbours) { _neighbours = neighbours; }

void Cell::alternate()
{
  if(_state == ALIVE) die();
  else born();
}
//
// Created by rysan on 21/12/23.
//
#pragma once
#include <vector>
#include <memory>

class Cell {
private:
    enum state { ALIVE,
                 DEAD };

    short _neighbours;
    state _state;
    void born();
    void die();
public:
    Cell();
    bool isAlive();
    void update();
    void inform_neighbours(short);
};



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
    state _state;
    short _neighbours;
public:
    bool isAlive();
    void born();
    void die();
    void update();
};



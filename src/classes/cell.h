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

    // Necessary only for this application!
    void inform_neighbours(short);
    void force_born() { _state = ALIVE; }
    void force_die() { _state = DEAD; }
    void alternate();
};

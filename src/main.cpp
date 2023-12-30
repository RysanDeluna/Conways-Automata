//
// Created by rysan on 21/12/23.
//
#include <iostream>
#include <engine.h>
#include "scenes/scene_simulation.h"

SceneSimulation simulaton;


int main()
{
  Engine::Start(1280, 720, "game debug mode", &simulaton);
  return 0;
}
//
// Created by rysan on 21/12/23.
//
#include <iostream>
#include <engine.h>
#include "scenes/scene_simulation.h"

// TODO: An editor;

SceneSimulation test;


int main()
{
  Engine::Start(1280, 720, "game debug mode", &test);
  return 0;
}
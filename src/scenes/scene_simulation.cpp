//
// Created by rysan on 28/12/23.
//

#include "scene_simulation.h"
#include "sys_renderer.h"

static std::shared_ptr<Matrix<Cell>> M;
static Matrix<Cell> old_M;
static double timer;

// Constructs the vector of graphic cells with the information of each one
// ** This should run only once
std::vector<graphic_cell_t> logical_to_graphical(const Matrix<Cell>* m)
{
  std::vector<graphic_cell_t> gm;
  timer = 0;
  sf::Vector2u window_size = Engine::GetWindowSize();
  sf::Vector2f tile_dimensions(float(window_size.x)/float(m->getRows()), float(window_size.y)/float(m->getCols()));

  for(int i = 0; i < m->getRows(); i++)
  {
    for(int j = 0; j < m->getCols(); j++)
    {
      // Constructs the GC
      graphic_cell_t gc;
      gc.m_pos.x = i; gc.m_pos.y = j;
      gc.alive = m->getPoin()[i][j].isAlive();
      // Screen Position configuration
      gc.s_pos.x = tile_dimensions.x * float(gc.m_pos.x); gc.s_pos.y = tile_dimensions.y * float(gc.m_pos.y);
      // Appearance configuration
      gc.setShape<sf::RectangleShape>(tile_dimensions);
      gc.shape->setFillColor(sf::Color::Transparent);
      gc.shape->setOutlineColor(sf::Color(10,10,10));
      gc.shape->setOutlineThickness(1.f);
      gc.shape->setPosition(gc.s_pos);
      // Insert it in the vector
      gm.push_back(gc);
    }
  }
  return gm;
}

void SceneSimulation::Load() {
  // First, the matrix is configured
  M = std::make_shared<Matrix<Cell>>(64,36,Cell());
  M->generate_life(30);

  old_M = *M;

  // Translate it from logical to graphical
  list_cells = logical_to_graphical(M.get());
  std::cout << *M << std::endl;
  setLoaded(true);
}

void SceneSimulation::UnLoad() {
  M.reset();
  list_cells.clear();
  Scene::UnLoad();
}

// TODO 1:  |Check if the application can continue without crashing
// TODO 2:  |Add other commands:
// TODO 2.1:|N
// TODO 2.2:|R
void SceneSimulation::Update(const double &dt) {
  timer += dt;

  // Update the cells
  for(auto& cell : list_cells)
    cell.alive ? cell.shape->setFillColor(sf::Color::White) : cell.shape->setFillColor(sf::Color::Transparent);

  // Keyboard Commands --------------
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) && timer >= 0.1)
  {
    old_M = *M; // Save the state of M before updating it
    M->update();
    for (auto& cell : list_cells) cell.alive = M->getPoin()[cell.m_pos.x][cell.m_pos.y].isAlive();
    timer = 0;
  }
  // Regenerate the board
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::N))
  {
    UnLoad();
    Load();
  }
  // Go back one time-step
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && timer >= 0.1)
  {
    *M = old_M;
    for (auto& cell : list_cells) cell.alive = M->getPoin()[cell.m_pos.x][cell.m_pos.y].isAlive();
  }
}

void SceneSimulation::Render() {
  for (auto const& cell : list_cells)
    Renderer::queue(cell.shape.get());
}

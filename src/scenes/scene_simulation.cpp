//
// Created by rysan on 28/12/23.
//

#include "scene_simulation.h"
#include "sys_renderer.h"

static std::shared_ptr<Matrix<Cell>> M;
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
      gc.cell_ptr = std::make_shared<Cell>(m->getPoin()[i][j]);
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
  M = std::make_shared<Matrix<Cell>>(16,16,Cell());
  M->generate_life(10);

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

// TODO: Fix the graphical update!
void SceneSimulation::Update(const double &dt) {
  timer += dt;

  // Update the cells
  for(auto& cell : list_cells)
    cell.cell_ptr->isAlive() ? cell.shape->setFillColor(sf::Color::White) : cell.shape->setFillColor(sf::Color::Transparent);

  // Keyboard Commands
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timer >= 0.5)
  {
    M->update(); std::cout << *M << std::endl;
    timer = 0;
  }
}

void SceneSimulation::Render() {
  for (auto const& cell : list_cells)
    Renderer::queue(cell.shape.get());
}

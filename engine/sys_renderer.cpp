//
// Created by rysan on 24/12/23.
//

#include "sys_renderer.h"
#include <queue>
#include <memory>

static std::queue<sf::Drawable*> sprites;
static std::unique_ptr<sf::RenderWindow> rw;

// Assign a window to the renderer
void Renderer::initialize(sf::RenderWindow& r) { rw.reset(&r); }

// Simply empty the queue
void Renderer::shutdown() { while(!sprites.empty()) sprites.pop(); }

// Draw every sprite in the queue until its empty
void Renderer::render()
{
  if(rw == nullptr) throw std::invalid_argument("FROM RENDERER:\tException:\t No render window set! ");
  while(!sprites.empty()) { rw->draw(*sprites.front()); sprites.pop(); }
}

void Renderer::queue(sf::Drawable* s) { sprites.push(s); }

void Renderer::update(const double &) {}
//
// Created by rysan on 24/12/23.
//
#include <SFML/Graphics.hpp>
#include <memory>

namespace Renderer {
  void initialize(sf::RenderWindow&);
  void shutdown();
  void update(const double&);
  void queue(std::unique_ptr<sf::Drawable> s);
  void render();
}; // namespace Renderer


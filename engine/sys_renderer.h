//
// Created by rysan on 24/12/23.
//

namespace Renderer {
  void initialize(sf::RenderWindow);
  void shutdown();
  void update(const double&);
  void queue(const sf::Drawable* s);
  void render();
}; // namespace Renderer


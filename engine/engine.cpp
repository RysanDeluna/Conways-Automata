//
// Created by rysan on 24/12/23.
//

#include "engine.h"
#include <iostream>
//#include "system_renderer.h"

std::unique_ptr<Scene> Engine::_activeScene = nullptr;
std::string Engine::_windowName;

static std::unique_ptr<sf::RenderWindow> _window = std::make_unique<sf::RenderWindow>();
static bool loading = false;


/* ---------- ENGINE ---------- */

void Engine::Update()
{
  // Starts the clock
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();

  // Update the scene if it exists
  if (_activeScene != nullptr)
    _activeScene->Update(dt);
} // Update

void Engine::Render(sf::RenderWindow &window)
{
  if (_activeScene != nullptr)
    _activeScene->Render();

  //Renderer::render();
} // Render

void Engine::Start(unsigned int width, unsigned int height,
                   const std::string &wName, Scene* scn)
{
  // Initialize window parameters
  sf::RenderWindow window(sf::VideoMode(width,height), wName);
  _windowName = wName;
  _window.reset(&window);

  // Renderer::initialize()

  // Change for scene...
  ChangeScene(scn);

  // General application loop
  while(window.isOpen()) {
    sf::Event event;

    // Closes window by either pressing the X or
    // the ESC key is pressed
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();


    // The basic SFML loop
    window.clear();
    Update();
    Render(window);
    window.display();
  }

  // Finishes the window and close everything that is needed
  if (_activeScene != nullptr)
  {
    _activeScene->UnLoad();
    _activeScene = nullptr;
  }
  window.close();
} // Start

void Engine::ChangeScene(Scene * s)
{
  std::cout << "FROM ENGINE:\tChanging Scene:\t" << s << std::endl;

  // Unload whatever assets that scene posses
  _activeScene->UnLoad();

  // Change the pointer to the new scene and the previous is lost
  _activeScene.reset(s);
  if(!s->isLoaded())
  {
    std::cout << "FROM ENGINE:\tLOADING SCENE..." << std::endl;
    _activeScene->Load();
    loading = true;
  }
} // Change Scene

sf::Vector2u Engine::GetWindowSize() { return _window->getSize(); }
sf::RenderWindow& Engine::GetWindow() { return *_window; }

/* ---------- SCENE ---------- */

bool Scene::isLoaded() const
{
  {
    {
      std::lock_guard<std::mutex> lck(_loaded_mtx);
      if (_loaded_future.valid() && _loaded_future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
      {
        _loaded_future.get();
        _loaded = true;
      }
    }
    return _loaded;
  }
}

void Scene::UnLoad()
{
  // TODO: clear every element in scene
  setLoaded(false);
}

void Scene::setLoaded(bool loaded) { _loaded = loaded; }

Scene::~Scene() { UnLoad(); }

namespace timing {
    long long now()   { return std::chrono::high_resolution_clock::now().time_since_epoch().count(); }
    long long last()
    {
      auto n = now();
      static auto then = now();
      auto dt = n - then;
      then = n;
      return dt;
    }
}  // namespace timing


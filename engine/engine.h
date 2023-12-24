//
// Created by rysan on 24/12/23.
//
//
#pragma once
#include "SFML/Graphics.hpp"
#include <memory>
#include <future>
#include <mutex>

// Handles elements present within a scene
// This is where all the logic for a specific environment is
class Scene {
public:
    Scene() = default;
    virtual ~Scene();
    virtual void Load() = 0;
    virtual void UnLoad();
    virtual void Update(const double& dt) = 0;
    virtual void Render() = 0;
    bool isLoaded() const;

protected:
    void setLoaded(bool);

private:
    mutable bool _loaded;
    mutable std::future<void> _loaded_future;
    mutable std::mutex _loaded_mtx;
};


//  This module covers the application's general functionalities
//  making sure that the sfml pipeline is done properly
class Engine {
public:
    Engine() = delete;
    static void Start(unsigned int width, unsigned int height,
                      const std::string& wName, Scene* scn);

    static sf::RenderWindow& GetWindow();
    static sf::Vector2u GetWindowSize();
    static void ChangeScene(Scene*);

private:
    static std::unique_ptr<Scene> _activeScene;
    static std::string _windowName;
    static void Update();
    static void Render(sf::RenderWindow& window);
};


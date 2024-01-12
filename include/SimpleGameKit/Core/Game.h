#pragma once

#include <memory>

#include "InputManager.h"
#include "Scene.h"
#include "Utils.h"
#include "../Render/Renderer.h"
#include "raylib-cpp.hpp"


namespace sgk {
class InputManager;

class Game {
public:
  Game() :  m_width(1600), m_height(900) {
      m_renderer = CreatePtr<Renderer>();
        m_window = raylib::Window(m_width, m_height, "SimpleGameKit");
        m_window.SetTargetFPS(60);
  }
  virtual ~Game() = default;

  virtual void settings() {
  }

  virtual void setup() {
    if (m_currentScene) {
      m_currentScene->setup();
    }
  }

  virtual void handleInput() {
    if (m_currentScene) {
      m_currentScene->handleInput();
    }
  }

  virtual void update([[maybe_unused]]const double dt) {
    if (m_currentScene) {
      m_currentScene->update(dt);
    }
  }

  virtual void draw() const {
    if (m_currentScene) {
      m_currentScene->draw();
    }
  }

  virtual void drawGui() const;

  void run();


  /**
  * @brief Get the Window object
  *
  * @return raylib::Window&
  */
  Window& getWindow();

  const Ptr<Renderer>& getRenderer() const {
    return m_renderer;
  }

  void addScene(const std::string& name, const Scene& scene) {
    m_scenes[name] = scene;
  }

  void setCurrentScene(const std::string& name) {
    m_currentScene = &m_scenes[name];
  }



private:
  std::map<std::string, Scene> m_scenes;
  Scene* m_currentScene = nullptr;
  raylib::Window m_window;
  int m_width;
  int m_height;
  Ptr<Renderer> m_renderer;


  // Ptr<InputManager> m_inputManager;
  // Ptr<AssetManager> m_assetManager;
  bool m_isRunning = true;
  double m_t = 0.0;
};
}

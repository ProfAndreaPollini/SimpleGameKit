#pragma once

#include <deque>
#include <memory>

#include "EntityManager.h"
#include "InputManager.h"
#include "Event.h"
#include "EventManager.h"
#include "Scene.h"
#include "Utils.h"
#include "../Render/Renderer.h"
#include "raylib-cpp.hpp"


namespace sgk {

class InputManager;

struct GameSettings {
  int width = 1600;
  int height = 900;
  std::string title = "Prova";
  bool fullscreen = false;
  bool resizable = true;
  bool vsync = true;
  int fps = 60;
};

/**
 * @brief Game class
 *
 *  This class is a singleton and it is used to manage the game loop. It also instantiates the
 *  entity manager. It is also responsible for the creation of the window and the renderer
 */
class Game final  {
  Game()
   : m_entityManager(CreatePtr<EntityManager>()), m_width(1600),m_height(900),
  m_eventManager(CreatePtr<EventManager>()){

  }


public:
  // delete copy and move constructors and assign operators
  Game(Game const&) = delete;
  void operator=(Game const&) = delete;
  Ptr<EntityManager>&  getEntityManager();
  Game(Game&&) = delete;
  Game& operator=(Game&&) = delete;

  virtual ~Game() = default;

  /**
   * @brief Get the Game object
   *
   * @return Game&
   */
  static Game& get() {
    static Game instance;
    return instance;
  }

  void settings(const GameSettings& settings = GameSettings()) {
    m_width = settings.width;
    m_height = settings.height;
    m_window = raylib::Window();
    m_window.Init(m_width, m_height, settings.title);
    m_renderer = CreatePtr<Renderer>();
    m_window.SetTargetFPS(settings.fps);
  }

   void setup() {
    if (m_currentScene) {
      m_currentScene->setup();
    }
  }

   void handleInput() {
    if (m_currentScene) {
      m_currentScene->handleInput();
    }
  }

  void update([[maybe_unused]] const double dt) {
    if (m_currentScene) {
      m_currentScene->update(dt);
    }
  }

   void draw() const {
    if (m_currentScene) {
      m_currentScene->draw();
    }
  }

  void drawGui() const;

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

  template <typename T, typename... Args>
  void addScene(const std::string& name, Args&&... args) {
    m_scenes[name] = sgk::CreateRef<T>(std::forward<Args>(args)...);
  }

  void setCurrentScene(const std::string& name) {
    m_currentScene = m_scenes[name];
  }

private:
  Ptr<EntityManager> m_entityManager;
  std::map<std::string, Ref<Scene>> m_scenes;
  Ref<Scene> m_currentScene = nullptr;
  raylib::Window m_window;
  int m_width;
  int m_height;
  Ptr<Renderer> m_renderer;
  Ptr<EventManager> m_eventManager;



  // Ptr<InputManager> m_inputManager;
  // Ptr<AssetManager> m_assetManager;
  bool m_isRunning = true;
  double m_t = 0.0;
};
}

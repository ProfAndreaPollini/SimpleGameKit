#pragma once

#include <deque>
#include <format>
#include <iostream>
#include <memory>
#include <ranges>

#include "EntityManager.h"
#include "InputManager.h"
#include "Event.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "System.h"
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
class Game final {
  Game()
    : m_entityManager(CreatePtr<EntityManager>()), m_width(1600), m_height(900),
      m_eventManager(CreatePtr<EventManager>()), m_inputManager(CreatePtr<InputManager>()), m_resourceManager(CreatePtr<ResourceManager>()) {
  }

public:
  // delete copy and move constructors and assign operators
  Game(Game const&) = delete;
  void operator=(Game const&) = delete;
  Ptr<EntityManager>& getEntityManager();
  Ptr<EventManager>& getEventManager();
  Ptr<InputManager>& getInputManager();
  Ptr<ResourceManager>& getResourceManager();
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
    // if (m_currentScene) {
    //   m_currentScene->setup();
    // }
  }

  void handleInput() {
    // if (m_currentScene) {
    //   m_currentScene->handleInput();
    // }
    m_inputManager->clear();

    std::vector<KeyEvent> keys;
    // auto key_events = m_eventManager->get<KeyEvent>();
    const auto& keys_filter = m_inputManager->getKeysFilter();
    for (const auto& key : keys_filter) {
      auto is_pressed = IsKeyPressed(key);
      auto is_released = IsKeyReleased(key);

      KeyEvent key_event = {key, KeyEvent::EventType::Released};
      if (is_pressed) {
        std::cout << std::format("keycode = {} pressed \n", key_event.key_code);
        key_event.type = KeyEvent::EventType::Pressed;
      } else if (is_released) {
        key_event.type = KeyEvent::EventType::Released;
        std::cout << std::format("keycode = {} released \n", key_event.key_code);
      } else if (IsKeyDown(key)) {
        key_event.type = KeyEvent::EventType::Repeat;
        std::cout << std::format("keycode = {} repeat \n", key_event.key_code);
      } else {
        continue;
      }
      keys.push_back(key_event);
    }
    for (const auto& key : keys) {
      m_inputManager->add<KeyEvent>(key.key_code, key.type);
    }

  }

  void update([[maybe_unused]] const double dt) {
    // if (m_currentScene) {
    //   m_currentScene->update(dt);
    // }
  }

  void draw() const {
    // if (m_currentScene) {
    //   m_currentScene->draw();
    // }
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
    if (m_currentScene) {
      for (const auto currentSystemsPhases = m_currentScene->getSystems() | std::views::keys; const auto phase :
           currentSystemsPhases) {
        cleanupSystem(phase);
           }
    }
    m_currentScene = m_scenes[name];
    UpdateSystems();

  }

private:
  void cleanupSystem(GameLoopPhase phase) {
    for (auto& system : m_systems[std::to_underlying(phase)]) {
      // remove system from the list of systems
      std::erase_if(m_systems[std::to_underlying(phase)],
                    [&system](const Ref<System>& s) { return s == system; });
    }
  }

  void UpdateSystems() {
    for (auto& [phase, systems] : m_currentScene->getSystems()) {
      for (auto& system : systems) {
        // add system to the list of systems
        m_systems[std::to_underlying(phase)].push_back(system);
      }
    }
  }


  std::array<std::vector<Ref<System>>, 6> m_systems;
  Ptr<EntityManager> m_entityManager;
  std::map<std::string, Ref<Scene>> m_scenes;
  Ref<Scene> m_currentScene = nullptr;
  raylib::Window m_window;
  int m_width;
  int m_height;
  Ptr<Renderer> m_renderer;
  Ptr<EventManager> m_eventManager;


  Ptr<InputManager> m_inputManager;
  Ptr<ResourceManager> m_resourceManager;
  // Ptr<AssetManager> m_assetManager;
  bool m_isRunning = true;
  double m_t = 0.0;
};
}

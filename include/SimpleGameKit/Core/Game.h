#pragma once

#include <memory>

#include "InputManager.h"
#include "Utils.h"
#include "raylib-cpp.hpp"


namespace sgk {
class InputManager;

class Game {
public:
  Game() = default;
  virtual ~Game() = default;

  virtual void settings() {
  }

  virtual void setup() {
  }

  virtual void handleInput() {
  }

  virtual void update(double dt) {
  }

  virtual void draw() const {
  }

  virtual void drawGui() const;

  void run();


  /**
  * @brief Get the Window object
  *
  * @return raylib::Window&
  */
  Window& getWindow();


  /**
   * \brief  Enable the Input Manager object
   */
  void EnableInputManager() {
    m_inputManager = CreatePtr<InputManager>();
  }

private:
  raylib::Window m_window;
  Ptr<InputManager> m_inputManager;
  bool m_isRunning = true;
  double m_t = 0.0;
};
}

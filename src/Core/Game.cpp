#include <imgui.h>
#include <rlImGui.h>

#include "SimpleGameKit/Core/Game.h"

#include <iostream>
#include <chrono>

#include <plog/Log.h> // Step1: include the headers
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>

namespace sgk {
void Game::drawGui() const {
  if (m_currentScene) {
    m_currentScene->drawGui();
  }
  bool open = true;
  ImGui::ShowDemoWindow(&open);
}

void Game::run() {
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::verbose, &consoleAppender);

  // Step3: write log messages using a special macro
  // There are several log macros, use the macro you liked the most

  PLOGD << "Hello log!";             // short macro
  PLOG_DEBUG << "Hello log!";        // long macro
  PLOG(plog::debug) << "Hello log!"; // function-style macro

  // Also you can use LOG_XXX macro but it may clash with other logging libraries
  LOGD << "Hello log!";             // short macro
  LOG_DEBUG << "Hello log!";        // long macro
  LOG(plog::debug) << "Hello log!"; // function-style macro
  settings();
  m_window.Init(m_width, m_height, "SimpleGameKit");
  setup();

  const double dt = 0.01;

  auto current_time = std::chrono::high_resolution_clock::now();
  auto accumulator = 0.0;

  rlImGuiSetup(true);

  while (!m_window.ShouldClose() and m_isRunning) {

      handleInput();


    // if (IsKeyPressed(KEY_F)) {
    //   enableInputManager();
    // }

    auto new_time = std::chrono::high_resolution_clock::now();
    const auto frame_time = std::chrono::duration_cast<std::chrono::duration<double>>(new_time - current_time).count();
    current_time = new_time;

    accumulator += frame_time;

    while (accumulator >= dt) {
      update(dt);
      accumulator -= dt;
      m_t += dt;
    }

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    draw();
    rlImGuiBegin();

    drawGui();
    rlImGuiEnd();
    EndDrawing();
  }

  // De-Initialization
  rlImGuiShutdown();
  m_window.Close();
}

Window& Game::getWindow() {
  return m_window;
}
}

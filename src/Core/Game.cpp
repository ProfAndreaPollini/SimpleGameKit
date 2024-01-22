#include <imgui.h>
#include <rlImGui.h>

#include "SimpleGameKit/Core/Game.h"
#include "SimpleGameKit/Core/Time.h"


#include <chrono>
using namespace std::chrono_literals;

#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>

namespace sgk {
Ptr<EntityManager>& Game::getEntityManager() {
  return m_entityManager;
}

Ptr<EventManager>& Game::getEventManager() {
  return m_eventManager;
}

Ptr<InputManager>& Game::getInputManager() {
  return m_inputManager;
}

Ptr<ResourceManager>& Game::getResourceManager() {
  return m_resourceManager;
}

void Game::drawGui() const {
  // if (m_currentScene) {
  //   m_currentScene->drawGui();
  // }
  bool open = true;
  ImGui::Text("prova");
}

void Game::run() {
  static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
  plog::init(plog::verbose, &consoleAppender);
  m_resourceManager->add<Time>();
  const auto time = m_resourceManager->get<Time>().value();

  // Step3: write log messages using a special macro
  // There are several log macros, use the macro you liked the most

  // PLOGD << "Hello log!";             // short macro
  // PLOG_DEBUG << "Hello log!";        // long macro
  // PLOG(plog::debug) << "Hello log!"; // function-style macro
  //
  // // Also you can use LOG_XXX macro but it may clash with other logging libraries
  // LOGD << "Hello log!";             // short macro
  // LOG_DEBUG << "Hello log!";        // long macro
  // LOG(plog::debug) << "Hello log!"; // function-style macro
  settings();
  // m_window.Init(m_width, m_height, "SimpleGameKit");
  setup();

  m_currentScene->setup();

  for (const auto& system : m_systems[std::to_underlying(GameLoopPhase::STARTUP)]) {
    system->operator()();
  }

  // constexpr auto timestep = std::chrono::duration_cast<std::chrono::duration<double>>
  //     (std::chrono::nanoseconds{16ms}).count();
  //
  // auto current_time = std::chrono::high_resolution_clock::now();
  // auto accumulator = 0.0;
  time->start();

  rlImGuiSetup(true);

  while (!m_window.ShouldClose() and m_isRunning) {
    std::cout << std::format("input events = {}", m_inputManager->get<sgk::KeyEvent>().size()) << std::endl;
    for (const auto& system : m_systems[std::to_underlying(GameLoopPhase::PRE_UPDATE)]) {
      std::cout << std::format("system: {}", typeid(*system).name()) << std::endl;
      system->operator()();
    }
    handleInput();



    // auto new_time = std::chrono::high_resolution_clock::now();
    // const auto frame_time = std::chrono::duration_cast<std::chrono::duration<double>>(new_time - current_time).count();
    // current_time = new_time;
    //
    // accumulator += frame_time;
    time->update();

    while (time->getAccumulator() >= Time::timestep) {
      // update(Time::timestep);
      for (const auto& system : m_systems[std::to_underlying(GameLoopPhase::UPDATE)]) {
        system->operator()();
      }
      //accumulator -= timestep;
      time->accumulator() -= Time::timestep;
      //m_t += timestep;
      time->t() += Time::timestep;
    }
    // std::cout << std::format("frame time = {}\n", time->getFrameTime());
    // std::cout << std::format("t = {}\n", time->t());


    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();
    draw();
    for (const auto& system : m_systems[std::to_underlying(GameLoopPhase::POST_UPDATE)]) {
      system->operator()();
    }

    rlImGuiBegin();
    drawGui();
    for (const auto& system : m_systems[std::to_underlying(GameLoopPhase::IMGUI)]) {
      system->operator()();
    }
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

#pragma once
#include <map>
#include <vector>
#include <ranges>
#include <algorithm>
#include <format>
#include <iostream>

#include "Utils.h"

namespace sgk {
class System;

class Scene {
public:
  Scene() = default;
  virtual ~Scene() = default;

  virtual void setup() {
  }
  //
  // virtual void handleInput() {
  // }
  //
  // virtual void update(double dt) {
  // }
  //
  // virtual void draw() const {
  // }
  //
  // virtual void drawGui() const {
  // }


  template <typename T, typename... Args>
    requires EnsureInheritsFrom<System, T>
  void addSystem(const GameLoopPhase phase, Args&&... args) {
    if (!m_systems.contains(phase)) {
      m_systems[phase] = std::vector<Ref<System>>();
    }
    m_systems[phase].push_back(CreateRef<T>(args...));
    std::cout << std::format("added system: {} [{}]", typeid(T).name(), m_systems[phase].size()) << std::endl;
  }


  auto getSystemsFor(const GameLoopPhase phase) {
    return m_systems[phase] | std::views::transform([](const auto& system) {
      return system;
    });
  }

  auto& getSystems() {
    return m_systems;
  }


  template <typename T>
    requires EnsureInheritsFrom<System, T>
  auto removeSystem(const GameLoopPhase phase) {
    auto& systems = m_systems[phase];
    auto it = std::find_if(systems.begin(), systems.end(), [](const auto& system) {
      return dynamic_cast<T*>(system.get());
    });
    if (it != systems.end()) {
      systems.erase(it);
    }
  }

  auto getSystemsCount() {
    return m_systems | std::views::transform([](const auto& pair) {
      return std::make_pair(pair.first, pair.second.size
                            ());
    });
  }

private:
  std::map<GameLoopPhase, std::vector<Ref<System>>> m_systems;
};
} // namespace sgk

#include "SimpleGameKit/Core/InputManager.h"

#include "raylib-cpp.hpp"

void sgk::InputManager::ProcessInput() {
  for (const auto& mapping : m_mappings) {

    if (auto [key, action] = mapping; IsKeyDown(key) and (
                                        action.action == ActionType::START or action.action == ActionType::ANY)) {
      QueueAction(action.event, ActionType::START);
      // PollInputEvents();
    } else if (IsKeyReleased(key) and (action.action == ActionType::END or action.action == ActionType::ANY)) {
      QueueAction(action.event, ActionType::END);
      // raylib::Pro
    }
  }
  // PollInputEvents();
  for (auto& [action, type] : events) {
    // if exists a callback for this action
    if (callbacks.contains(action) and not callbacks[action].empty()) {
      for (auto& callback : callbacks[action]) {
        callback(std::make_tuple(action, type));
      }
      events.clear();
    }
  }
}

void sgk::InputManager::QueueAction(const std::string& action, ActionType type) {
  events.insert(std::make_tuple(action, type));
}

std::set<sgk::InputEvent>& sgk::InputManager::GetActions() {
  return events;
}

size_t sgk::InputManager::GetActionCount() const { return events.size(); }

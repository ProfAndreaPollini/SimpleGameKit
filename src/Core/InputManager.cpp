

#include "SimpleGameKit/Core/InputManager.h"

void sgk::InputManager::ProcessInput() {
}

void sgk::InputManager::QueueAction(std::string action, ActionType type) {
  actions.insert(std::make_tuple(action, type));
}

std::set<sgk::Action>& sgk::InputManager::GetActions() {
  return actions;
}

size_t sgk::InputManager::GetActionCount() const { return actions.size(); }

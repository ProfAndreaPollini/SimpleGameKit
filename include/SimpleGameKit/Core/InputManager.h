#pragma once
#include <functional>
#include <list>
#include <map>
#include <set>
#include <string>

namespace sgk {
enum class ActionType {
  START,
  END,
  ANY
};

struct KeyMappingInfo {
  std::string event;
  ActionType action;
};

using KeyMapping = std::map<int, KeyMappingInfo>;


inline const char* to_string(ActionType e) {
  switch (e) {
    case ActionType::START:
      return "START";
    case ActionType::END:
      return "END";
    default:
      return "unknown";
  }
}

using Event = std::tuple<std::string, ActionType>;
using EventCallback = std::function<void(const Event&)>;

class InputManager {
  KeyMapping m_mappings = {};
  std::set<Event> events = {};
  std::unordered_map<std::string, std::list<EventCallback>> callbacks = {};

public:
  InputManager() = default;

  void RegisterMapping(const int key, const KeyMappingInfo& event) {
    m_mappings[key] = event;
  }

  void OnEvent(const std::string& event, const EventCallback& callback) {
    callbacks[event].push_back(callback);
  }

  void ProcessInput();
  void QueueAction(const std::string& action, ActionType type);
  std::set<Event>& GetActions();
  size_t GetActionCount() const;
};
}

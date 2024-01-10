#pragma once
#include <map>
#include <set>
#include <string>

namespace sgk {
using KeyMapping = std::map<int, std::string>;


enum class ActionType {
  START,
  END
};

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

using Action = std::tuple<std::string, ActionType>;

class InputManager {
  KeyMapping key_mapping = {};
  std::set<Action> actions = {};

public:
        InputManager() = default;
        void RegisterMapping(int key, std::string action);
        void ProcessInput();
        void QueueAction(std::string action, ActionType type);
        std::set<Action>& GetActions();
        size_t GetActionCount() const;
};


}

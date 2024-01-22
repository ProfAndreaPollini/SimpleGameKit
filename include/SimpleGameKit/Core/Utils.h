#pragma once

#include <Window.hpp>
#include <memory>

namespace sgk {
struct InputEvent;
}

namespace sgk {
struct Event;
template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
constexpr Ref<T> CreateRef() {
  return std::make_shared<T>();
}


template <typename T>
using Ptr = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Ptr<T> CreatePtr(Args&&... args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
constexpr Ptr<T> CreatePtr() {
  return std::make_unique<T>();
}

template <typename BASE, typename T>
concept EnsureInheritsFrom = std::is_base_of_v<BASE, T>;

using Window = raylib::Window;

using KeyCode = int;

template <typename T>
concept IsEventObject = std::is_base_of_v<sgk::Event, T>;

template <typename T>
concept is_input_event = std::is_base_of_v<sgk::InputEvent, T>;

/*
* First: Runs at the very start of the schedule execution cycle, even before the startup stage.
Startup: This is actually a schedule containing sub-stages. Runs only once when the app starts.
Pre-startup: Intended for systems that need to run before other startup systems.
Startup: The main startup stage. Startup systems are added here by default.
Post-startup: Intended for systems that need to run after other startup systems.
Pre-update: Often used by plugins to prepare their internal state before the update stage begins.
Update: Intended for user defined logic. Systems are added here by default.
Post-update: Often used by plugins to finalize their internal state after the world changes that happened during the update stage.
Last: Runs right before the end of the schedule execution cycle.
*/
enum class GameLoopPhase : int{
  FIRST = 0,
  STARTUP = 1,
  PRE_UPDATE=2,
  UPDATE = 3,
  POST_UPDATE = 4,
  IMGUI = 5,
  LAST = 6
};




}  // namespace sgk

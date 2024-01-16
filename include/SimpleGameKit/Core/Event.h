#pragma once
#include "raylib-cpp.hpp"

namespace sgk {
struct Event {
  virtual ~Event() = default;
};

struct KeyEvent : Event {

  ~KeyEvent() override = default;

  enum class EventType {
    Pressed,
    Released,
    Repeat
  };

  enum Keycode {
    A = KEY_A,
  };

  KeyEvent(const Keycode key_code, const EventType type)
    : key_code(key_code), type(type) {
  }

  Keycode key_code;
  EventType type;
};
}

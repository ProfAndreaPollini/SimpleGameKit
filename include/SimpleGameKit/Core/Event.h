#pragma once
#include "raylib-cpp.hpp"

namespace sgk {
struct Event {
  virtual ~Event() = default;
};

struct InputEvent : Event {
  ~InputEvent() override = default;
};

struct MouseEvent : InputEvent {
  ~MouseEvent() override = default;

  enum class EventType {
    Pressed,
    Released,
    DoubleClick,
    WheelUp,
    WheelDown,
    Move,
    Drag
  };

  MouseEvent(const EventType type, const Vector2& position)
    : type(type), position(position) {
  }

  EventType type;
  Vector2 position;
};

struct KeyEvent final : InputEvent {

  ~KeyEvent() override = default;

  enum class EventType {
    Pressed,
    Released,
    Repeat
  };

  using Keycode = int;

  KeyEvent(const Keycode key_code, const EventType type)
    : key_code(key_code), type(type) {
  }

  Keycode key_code;
  EventType type;
};
}

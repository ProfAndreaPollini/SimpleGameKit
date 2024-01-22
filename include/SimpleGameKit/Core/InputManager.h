//
// Created by profa on 21/01/2024.
//

#pragma once
#include <algorithm>

#include <map>
#include <typeindex>
#include <vector>
#include <ranges>

#include "Event.h"
#include "Utils.h"

namespace sgk {
class InputManager {
  std::vector<KeyCode> m_keys_filter{};

  /**
   * \brief
   */
  std::map<std::type_index, std::vector<Ptr<InputEvent>>> m_events{};

public:
  void setKeysFilter(const std::vector<KeyCode>& keys) {
    m_keys_filter = keys;
  }

  const std::vector<KeyCode>& getKeysFilter() const {
    return m_keys_filter;
  }

  bool isKeyPressed(KeyCode key) const {
    return isKey<KeyEvent::EventType::Pressed>(key);
  }

  bool isKeyReleased(KeyCode key) const {
    return isKey<KeyEvent::EventType::Released>(key);
  }

  template <KeyEvent::EventType STATE>
  bool isKey(KeyCode key) const {
    return m_events.contains(std::type_index(typeid(KeyEvent))) &&
           std::ranges::count_if(m_events.at(std::type_index(typeid(KeyEvent))), [key](const Ptr<InputEvent>& evt) {
             const auto* key_event = dynamic_cast<KeyEvent*>(evt.get());
             return key_event->key_code == key && key_event->type == STATE;
           }) > 0;
  }

  template <typename T>
    requires is_input_event<T>
  std::vector<T*> get() {
    std::vector<T*> ret;
    if (!m_events.contains(std::type_index(typeid(T)))) {
      return ret;
    }

    for (auto e : m_events.at(std::type_index(typeid(T))) | std::views::transform(
                               [](const Ptr<InputEvent>& evt) {
                                 return dynamic_cast<T*>(evt.get());
                               })) {
      ret.push_back(e);
    }
    return ret;
  }

  void clear() {
    m_events.clear();
  }

  template <typename T, typename... Args>
    requires is_input_event<T>
  void add(Args&&... args) {
    if (!m_events.contains(std::type_index(typeid(T)))) {
      m_events[std::type_index(typeid(T))] = std::vector<Ptr<InputEvent>>{};
    }
    m_events[std::type_index(typeid(T))].push_back(CreatePtr<T>(std::forward<Args>(args)...));
  }

  size_t size() const {
    return m_events.size();
  }

  template <typename T>
  size_t count() const {
    return m_events.count(std::type_index(typeid(T)));
  }
};
}

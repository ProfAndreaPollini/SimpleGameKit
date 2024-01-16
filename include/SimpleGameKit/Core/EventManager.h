#pragma once
#include <ranges>
#include <vector>

#include "Event.h"

#include <type_traits>
#include <typeindex>
#include <algorithm>

#include "Utils.h"

template <typename T>
concept IsEventObject = std::is_base_of_v<sgk::Event, T>;

namespace sgk {
class EventManager {
  using EventWithInfo = std::tuple<std::type_index, Ref<Event>>;
  std::vector<EventWithInfo> m_events;

public:

  EventManager() = default;

  template<typename  T, typename... Args>
  requires IsEventObject<T>
  void add(Args&&... args) {
    EventWithInfo event = std::make_tuple(std::type_index(typeid(T)),CreateRef<T>(std::forward<Args>(args)...));
    m_events.push_back( event);
  }

  template<typename  T>
  requires IsEventObject<T>
  bool has() const {
    const auto& type = std::type_index(typeid(T));
    return std::ranges::count_if(m_events ,[type](const EventWithInfo& e) {
      return std::get<0>(e) == type;
    }) >0;
  }

  template<typename  T>
  requires IsEventObject<T>
  auto get() {
    return m_events | std::views::filter([type = std::type_index(typeid(T))](const EventWithInfo& e) {
      return std::get<0>(e) == type;
    }) | std::views::transform([](const EventWithInfo& e) {
      auto v = dynamic_cast<T*>(std::get<1>(e).get());
      return v;
    });
  }

  size_t size() const {
    return m_events.size();
  }

  void clear() {
    m_events.clear();
  }


};
}

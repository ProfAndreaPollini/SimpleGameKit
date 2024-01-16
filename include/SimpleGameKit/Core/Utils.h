#pragma once

#include <Window.hpp>
#include <memory>

namespace sgk {
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

using Window = raylib::Window;


}  // namespace sgk

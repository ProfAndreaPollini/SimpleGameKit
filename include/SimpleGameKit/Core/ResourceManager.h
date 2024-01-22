#pragma once
#include <ranges>
#include <map>


#include <type_traits>
#include <typeindex>
#include <algorithm>
#include <expected>



#include "Utils.h"




#include "Utils.h"


namespace sgk {



struct Resource {
  virtual ~Resource() = default;
};

class ResourceManager {
  enum class resource_error {
    resource_not_found
  };

  using ResourceWithInfo = std::tuple<std::type_index, Ref<Resource>>;
  std::map<std::type_index, Ref<Resource>> m_resources{};

public:
  ResourceManager() = default;

  template <typename T, typename... Args>
    requires EnsureInheritsFrom<Resource, T>
  void add(Args&&... args) {
    if (has<T>()) {
      return;
    }
    m_resources[std::type_index(typeid(T))] = CreateRef<T>(std::forward<Args>(args)...);
  }

  template <typename T>
    requires EnsureInheritsFrom<Resource, T>
  bool has() const {
    const auto& type = std::type_index(typeid(T));
    return m_resources.contains(type);
  }

  template <typename T>
    requires EnsureInheritsFrom<Resource, T>
  std::expected<T*,resource_error> get() {
    if (!has<T>()) {
      return std::unexpected(resource_error::resource_not_found);
    }
    auto resource = dynamic_cast<T*>(m_resources[std::type_index(typeid(T))].get());
    return resource;
  }

  size_t size() const {
    return m_resources.size();
  }

  void clear() {
    m_resources.clear();
  }
};
}

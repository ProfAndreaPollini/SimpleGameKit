#pragma once
#include <memory>
#include <expected>
#include <map>
#include <typeindex>
#include <vector>

#include "Utils.h"

namespace sgk {
enum class entity_error {
  component_not_found
};

class Component {
public:
  virtual ~Component() = default;
};



class Entity {
  inline static int s_id = 0;

  static int nextId() {
    return ++s_id;
  }

  int m_id;

  std::map<std::type_index, Ptr<Component>> m_components{};


  template <typename T>
  bool has_one() const {
    return m_components.contains(std::type_index(typeid(T)));
  }

public:

  Entity()
    : m_id(nextId()) {
  }

  int getId() const {
    return m_id;
  }

  // get a component
  template <typename T>
  std::expected<std::reference_wrapper<T>, entity_error> get() {
    if (const auto it = m_components.find(std::type_index(typeid(T))); it != m_components.end()) {
      T* component = dynamic_cast<T*>(it->second.get());
      if (component) {
        return *component;
      }
    }
    return std::unexpected(entity_error::component_not_found);
  }

  /**
   * !brief add a component
   *  T must be the exact type of the component to add
   *
   */
  template <typename T, typename... Args>
  [[maybe_unused]] std::expected<T, entity_error> add(Args&&... args) {
    m_components[std::type_index(typeid(T))] = sgk::CreatePtr<T>(std::forward<Args>(args)...);
    if (const auto it = m_components.find(std::type_index(typeid(T))); it != m_components.end()) {
      T* component = dynamic_cast<T*>(it->second.get());
      if (component) {
        return *component;
      }
    }
      return std::unexpected(entity_error::component_not_found);

  }

  // check if components has a specific set of components

  template <typename... T>
  bool has() const {
    return (has_one<T>() && ...);
  }

  /** remove a component
   *
   * T must be the exact type of the component to remove
   *
   * This function does nothing if the component does not exist
   */
  template <typename T>
  void remove() {
    m_components.erase(std::type_index(typeid(T)));
  }


  static std::shared_ptr<Entity> create() {
    auto entity = std::make_shared<Entity>();
    return entity;
  }
};


struct EntityRelationship final : Component  {
  std::vector<std::shared_ptr<Entity>> children;
  std::shared_ptr<Entity> parent;
};

}

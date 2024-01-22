#pragma once
#include <vector>

#include "Entity.h"
#include "Event.h"

namespace sgk {

class EntityManager {
  std::vector<Ref<Entity>> m_entities{};

public:
  EntityManager() = default;
  ~EntityManager() = default;

  Ref<sgk::Entity>& createEntity() {
    m_entities.emplace_back(CreateRef<sgk::Entity>());
    return m_entities.back();
  }


  //get entities with a specific set of compoenent types
  template <typename... Ts>
  std::vector<Ref<Entity>> get() const {
    std::vector<Ref<Entity>> entities{};
    for (auto& entity : m_entities) {
      if (entity->has<Ts...>()) {
        entities.emplace_back(entity);
      }
    }
    return entities;
  }

  //get entities with a specific set of compoenent types
  template <typename... Ts>
  std::expected<Ref<Entity>,entity_error> getOne() const {
        for (auto& entity : m_entities) {
          if (entity->has<Ts...>()) {
                return entity;
          }
        }
        return std::unexpected(entity_error::component_not_found);
  }
};
}

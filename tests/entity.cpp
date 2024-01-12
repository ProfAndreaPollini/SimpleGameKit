#include <SimpleGameKit/Core/EntityManager.h>
#include <gtest/gtest.h>

#include "SimpleGameKit/SimpleGameKit.h"


struct Position final : sgk::Component {
  float x{}, y{};

  Position() = default;
};

struct Velocity final : sgk::Component {
  float x{}, y{};

  Velocity() = default;
};

TEST(SimpleGameKitTest, EntityClassTests) {
  auto e = sgk::Entity::create();
  const auto pos = e->add<Position>();
  ASSERT_EQ(pos.has_value(), true);
  auto& p = pos.value();
  ASSERT_EQ(p.x, 0);

  ASSERT_TRUE(e->has<Position>());
  e->remove<Position>();
  ASSERT_FALSE(e->has<Position>());
}


TEST(SimpleGameKitTest, EntityManagerTests) {
  sgk::EntityManager em;
  auto e = em.createEntity();
  auto e2 = em.createEntity();
  e->add<Position>();
  e2->add<Position>();
  e2->add<Velocity>();
  // game.run();
  ASSERT_EQ(e->getId(), 1);

  // get entities with a specific component type
  const auto entities = em.get<Position>();
  ASSERT_EQ(entities.size(), 2);
  const auto entities2 = em.get<Position, Velocity>();
  ASSERT_EQ(entities2.size(), 1);
}

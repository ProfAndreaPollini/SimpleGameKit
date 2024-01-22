#include <SimpleGameKit/Core/Entity.h>
#include <SimpleGameKit/Core/Game.h>
#include <gtest/gtest.h>

#include "SimpleGameKit/Core/System.h"

struct TestSystem : sgk::System {
  int value = 0;

  void operator()() override {
    value = 2;
  }

  TestSystem()
    : value(0) {
  }
};

TEST(System, addEntity) {
  TestSystem system;
  ASSERT_EQ(system.value, 0);
  system();
  ASSERT_EQ(system.value, 2);
}

struct BaseScene final : sgk::Scene {
  sgk::Ref<sgk::Entity> e;

  BaseScene() {
    e = sgk::Entity::create();
  }

  ~BaseScene() override= default;
  void setup() override{}
  void handleInput() override{}
  void update(double dt) override{}
  void draw() const override{}
  void drawGui() const override{}
};

TEST(System, GameAdded) {
  TestSystem system;
  BaseScene scene;
  scene.addSystem<TestSystem>(sgk::GameLoopPhase::UPDATE);
  const auto& systems = scene.getSystemsCount();
  // find the systems for a game loop phase
  for (const auto& system : systems) {
    if (system.first == sgk::GameLoopPhase::UPDATE) {
      ASSERT_EQ(system.second, 1);
    } else {
      ASSERT_EQ(system.second, 0);
    }
  }
  scene.removeSystem<TestSystem>(sgk::GameLoopPhase::UPDATE);
  const auto& systems2 = scene.getSystemsCount();
  // find the systems for a game loop phase
  for (const auto& system : systems2) {
    if (system.first == sgk::GameLoopPhase::UPDATE) {
      ASSERT_EQ(system.second, 0);
    } else {
      ASSERT_EQ(system.second, 0);
    }
  }
}

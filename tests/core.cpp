#include <SimpleGameKit/Core/Entity.h>
#include <gtest/gtest.h>

#include "SimpleGameKit/SimpleGameKit.h"

TEST(SimpleGameKitTest, BasicAssertions) {
  ASSERT_EQ(1, 1);
  ASSERT_TRUE(true);
}

class CustomGame final : public sgk::Game {
public:
  void setup() override {
    a = 2;
  }

  void settings() override {
    getWindow().SetTitle("pippo");
  }

  int a = 1;
};

TEST(SimpleGameKitTest, EntityTests) {
  auto e = sgk::Entity::create();
  auto e2 = sgk::Entity::create();
  // game.run();
  ASSERT_EQ(e->getId(), 1);
  ASSERT_EQ(e2->getId(), 2);
}

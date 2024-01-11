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

TEST(SimpleGameKitTest, CustomGameSetup) {
  CustomGame game;
  game.setup();
  // game.run();
  ASSERT_EQ(game.a, 2);
}

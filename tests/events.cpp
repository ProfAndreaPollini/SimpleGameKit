#include <SimpleGameKit/Core/InputManager.h>
#include <gtest/gtest.h>

#include "SimpleGameKit/Core/EventManager.h"
#include "SimpleGameKit/Core/Event.h"

TEST(SimpleGameKitTest, EventManagerTests) {

  sgk::InputManager inputManager;

  ASSERT_EQ(inputManager.size(), 0);
  inputManager.add<sgk::KeyEvent>(65, sgk::KeyEvent::EventType::Pressed);
  ASSERT_EQ(inputManager.size(), 1);

  ASSERT_EQ(inputManager.isKey<sgk::KeyEvent::EventType::Pressed>(65), true);
  ASSERT_EQ(inputManager.isKey<sgk::KeyEvent::EventType::Pressed>(66), false);
  ASSERT_EQ(inputManager.count<sgk::KeyEvent>(), 1);

  const auto events = inputManager.get<sgk::KeyEvent>();
  ASSERT_EQ(events.size(), 1);
  inputManager.clear();
  ASSERT_EQ(inputManager.size(), 0);
}

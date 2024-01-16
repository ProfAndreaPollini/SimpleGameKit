#include <gtest/gtest.h>

#include "SimpleGameKit/Core/EventManager.h"
#include "SimpleGameKit/Core/Event.h"

TEST(SimpleGameKitTest, EventManagerTests) {
  sgk::EventManager em;
  em.add<sgk::KeyEvent>(sgk::KeyEvent::Keycode::A, sgk::KeyEvent::EventType::Pressed);
  ASSERT_EQ(em.size(), 1);

  ASSERT_TRUE(em.has<sgk::KeyEvent>());
  for (auto i = 0; i < 10; ++i) {
    em.add<sgk::KeyEvent>(sgk::KeyEvent::Keycode::A, sgk::KeyEvent::EventType::Pressed);
  }
  em.add<sgk::KeyEvent>(sgk::KeyEvent::Keycode::A, sgk::KeyEvent::EventType::Pressed);
  auto events = em.get<sgk::KeyEvent>();
  auto n_events = std::ranges::distance(events);
  ASSERT_EQ(n_events, 12);

  for (const auto* event : events) {
    ASSERT_EQ(event->key_code, sgk::KeyEvent::Keycode::A);
    ASSERT_EQ(event->type, sgk::KeyEvent::EventType::Pressed);
  }

  em.clear();
  ASSERT_EQ(em.size(), 0);
}

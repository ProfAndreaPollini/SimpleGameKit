#include <gtest/gtest.h>

#include "SimpleGameKit/Core/ResourceManager.h"

// create a test resource
struct TestResource :  sgk::Resource {
  int m_value;

  explicit TestResource(int value) : m_value(value) {}
};

TEST(ResourceManager, loadTexture) {
  sgk::ResourceManager resourceManager;
  ASSERT_EQ(resourceManager.size(), 0);
  resourceManager.add<TestResource>(2);
  ASSERT_EQ(resourceManager.size(), 1);
        auto resource = resourceManager.get<TestResource>();
  ASSERT_EQ(resource.value()->m_value, 2);
}
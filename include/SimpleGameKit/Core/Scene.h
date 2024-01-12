#pragma once

namespace sgk {
class Scene {
public:
  Scene() = default;
  virtual ~Scene() = default;

  virtual void setup() {
  }

  virtual void handleInput() {
  }

  virtual void update(double dt) {
  }

  virtual void draw() const {
  }

  virtual void drawGui() const {
  }
};
} // namespace sgk

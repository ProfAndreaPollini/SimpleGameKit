#pragma once

#include "raylib-cpp.hpp"

namespace sgk {

using Color = raylib::Color;

/**
 * @brief A class that handles the rendering of the game.
 *
 */
class Renderer {
public:
  Renderer() = default;

  static void ClearBackground(const Color& color) {
          ::ClearBackground(color);
}

  void DrawTexture(std::string& name, Vector2& position) const;
};
}  // namespace sgk

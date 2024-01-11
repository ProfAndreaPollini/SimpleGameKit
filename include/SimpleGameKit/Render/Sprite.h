#pragma once

namespace sgk {
class Sprite {
        std::string m_name;
        Texture2D m_texture;
public:
  Sprite() = default;
  Sprite(std::string& name) : m_name(name) {}

  void setName(std::string& name) { m_name = name; }
        std::string& getName() { return m_name; }

        void setTexture(Texture2D& texture) { m_texture = texture; }
            Texture2D& getTexture() { return m_texture; }

  void Draw(Vector2& position) const;
};
}  // namespace sgk

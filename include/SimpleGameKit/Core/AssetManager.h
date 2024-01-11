#pragma once
#include <Font.hpp>

#include <Sound.hpp>
#include <Texture.hpp>


#include <map>

#include "Utils.h"

namespace sgk {
template <typename T>
class AssetManager {
  std::map<std::string, T> m_assets;

public:
  virtual ~AssetManager() = default;
  AssetManager() = default;

  void Load(const std::string& name, const std::string& path) {
    m_assets[name] = LoadAsset(path);
  }

  T& Get(const std::string& name) {
    return m_assets[name];
  }

  const T& Get(const std::string& name) const {
    return m_assets[name];
  }

  void Unload(const std::string& name) {
    m_assets.erase(name);
  }

  void UnloadAll() {
    m_assets.clear();
  }

  size_t GetAssetCount() const {
    return m_assets.size();
  }

  virtual T LoadAsset(const std::string& path) = 0;
};

class TextureManager final : public AssetManager<raylib::Texture2D> {
public:
  raylib::Texture2D LoadAsset(const std::string& path) override {
    return {path};
  }
};

class FontManager final : public AssetManager<raylib::Font> {
public:
  raylib::Font LoadAsset(const std::string& path) override {
    return {path};
  }
};

class SoundManager final : public AssetManager<raylib::Sound> {
public:
  raylib::Sound LoadAsset(const std::string& path) override {
    return {path};
  }
};
} // namespace sgk

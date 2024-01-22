#pragma once

namespace sgk {
class System {
public:
  virtual ~System() = default;
  virtual void operator()() =0;

  bool isEnabled() const {
    return m_enabled;
  }

  void enable() {
    m_enabled = true;
  }

  void disable() {
    m_enabled = false;
  }

private:
  bool m_enabled{true};
};
}

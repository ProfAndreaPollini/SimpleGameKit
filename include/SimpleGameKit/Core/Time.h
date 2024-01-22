#pragma once
#include <chrono>
using namespace std::chrono_literals;

#include "ResourceManager.h"

namespace sgk {
struct Time final : Resource {
  constexpr static double timestep = std::chrono::duration_cast<std::chrono::duration<double>>
       (std::chrono::nanoseconds{16ms}).count();


  auto t() const {
    return m_t;
  }

  void start() {
    m_accumulator = 0.0;
    current_time = std::chrono::high_resolution_clock::now();
  }

  void update() {
    auto new_time = std::chrono::high_resolution_clock::now();
    m_frame_time = std::chrono::duration_cast<std::chrono::duration<double>>(new_time - current_time).count();
    current_time = new_time;

    m_accumulator += m_frame_time;
  }

  double getFrameTime() const {
    return m_frame_time;
  }

  double getAccumulator() const {
    return m_accumulator;
  }


  double& accumulator() {
    return m_accumulator;
  }

  double& frameTime() {
    return m_frame_time;
  }

  double& t() {
    return m_t;
  }

private:


  std::chrono::time_point<std::chrono::system_clock> current_time;
  double m_accumulator = 0.0;
  double m_frame_time = 0.0;
  double m_t = 0.0;
};
}

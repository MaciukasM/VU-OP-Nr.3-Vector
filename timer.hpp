#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer //laikui
{
  using clock = std::chrono::high_resolution_clock;
  using duration = std::chrono::duration<double>;

 private:
  std::chrono::time_point<clock> pradzia;

 public:
  double elapsed() const { return duration(clock::now() - pradzia).count(); }
  void reset() { pradzia = clock::now(); }
};
#endif
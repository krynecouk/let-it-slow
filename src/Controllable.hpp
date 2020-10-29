#pragma once

#include "Event.hpp"

template <typename E = Event> class Controllable {
  virtual void control(const E &event) = 0;
};

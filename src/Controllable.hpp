#pragma once

#include <SDL2/SDL_events.h>

template <typename E> class Controllable {
  virtual void control(E &event) = 0;
};

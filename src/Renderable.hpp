#pragma once

#include <SDL2/SDL_render.h>
#include <memory>

template <typename R> class Renderable {
public:
  virtual void render(float dt, std::shared_ptr<R> renderer) = 0;
};

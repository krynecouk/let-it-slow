#pragma once

#include "Window.hpp"
#include <SDL2/SDL_render.h>
#include <vector>

class Renderer {
  Window *window;
  SDL_Renderer *raw_renderer;
  float last_frame_ticks_ms;

public:
  explicit Renderer(Window *window);
  ~Renderer();
  Renderer(const Renderer &that);
  Renderer(Renderer &&that);
  Renderer &operator=(Renderer that);

  float dt;
  template <typename T> void render(std::vector<T> *components);
};

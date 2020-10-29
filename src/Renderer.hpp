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
  void reset();
  template <typename T> void render(const T &component);
  template <typename T> void render(const std::vector<T> &components);
  void flush();
};

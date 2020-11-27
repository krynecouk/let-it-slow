#include "Renderer.hpp"
#include "Constants.hpp"
#include "InitException.hpp"
#include "Rectangle.hpp"
#include "Snowflake.hpp"
#include <SDL_rect.h>
#include <SDL_timer.h>
#include <utility>

Renderer::Renderer(Window *window)
    : window{window}, raw_renderer{nullptr},
      last_frame_ticks_ms{0.0f}, dt{0.0f} {

  raw_renderer = SDL_CreateRenderer(window->get(), -1, 0);
  if (!(raw_renderer)) {
    throw InitException("SDL Renderer");
  }
  this->reset();
};

Renderer::~Renderer() {
  SDL_DestroyRenderer(raw_renderer);
  // delete window; // TODO kryszczuk: freed by game - fix
}

Renderer::Renderer(const Renderer &that) : Renderer(that.window){};

Renderer::Renderer(Renderer &&that) {
  raw_renderer = std::exchange(that.raw_renderer, nullptr);
  window = std::exchange(that.window, nullptr);
}

Renderer &Renderer::operator=(Renderer that) {
  std::swap(raw_renderer, that.raw_renderer);
  std::swap(window, that.window);
  return *this;
};

void Renderer::reset() {
  SDL_SetRenderDrawColor(raw_renderer, 21, 21, 21, 255);
  SDL_RenderClear(raw_renderer);
}

template <typename T> void Renderer::render(const T &component) {
  SDL_SetRenderDrawColor(raw_renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(raw_renderer, &component);
};

template <typename T> void Renderer::render(const std::vector<T> &components) {
  // TODO kryszczuk: batch rendering preferable
  const T *rects_arr = components.data();
  for (int i = components.size() - 1; i >= 0; i--) {
    render(rects_arr[i]);
  }
};

void Renderer::flush() {
  SDL_Delay(MS_PER_FRAME);
  dt = (SDL_GetTicks() - last_frame_ticks_ms) / 1000.f;
  last_frame_ticks_ms = SDL_GetTicks();
  dt = dt > 0.05f ? 0.05f : dt;
  SDL_RenderPresent(raw_renderer);
}

template void Renderer::render<Rectangle>(const Rectangle &component);

template void Renderer::render<Snowflake>(const Snowflake &component);

template void
Renderer::render<Snowflake>(const std::vector<Snowflake> &components);

#pragma once

#include "Renderer.hpp"
#include "Constants.hpp"
#include "InitException.hpp"
#include "Projectile.hpp"
#include "Rectangle.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <utility>

Renderer::Renderer(Window *window)
    : window{window}, raw_renderer{nullptr},
      last_frame_ticks_ms{0.0f}, dt{0.0f} {

  raw_renderer = SDL_CreateRenderer(window->get(), -1, 0);
  if (!(raw_renderer)) {
    throw InitException("SDL Renderer");
  }
};

Renderer::~Renderer() {
  SDL_DestroyRenderer(raw_renderer);
  delete window;
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

template <typename T> void Renderer::render(std::vector<T> *components) {
  SDL_Delay(MS_PER_FRAME);

  dt = (SDL_GetTicks() - last_frame_ticks_ms) / 1000.f;
  last_frame_ticks_ms = SDL_GetTicks();
  dt = dt > 0.05f ? 0.05f : dt;

  SDL_SetRenderDrawColor(raw_renderer, 21, 21, 21, 255);
  SDL_RenderClear(raw_renderer);

  SDL_SetRenderDrawColor(raw_renderer, 255, 255, 255, 255);

  // TODO kryszczuk: batch rendering preferable
  T *rects_arr = components->data();
  for (int i = components->size() - 1; i >= 0; i--) {
    std::cout << "arr_" << i << ":(" << rects_arr[i].x << "," << rects_arr[i].y
              << ")\n";
    SDL_RenderFillRect(raw_renderer, &rects_arr[i]);
  }

  SDL_RenderPresent(raw_renderer);
};

template void Renderer::render<Projectile>(std::vector<Projectile> *components);

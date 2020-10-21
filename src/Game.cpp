#include "Game.hpp"
#include "Constants.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <algorithm>
#include <iostream>
#include <memory>

Game::Game(int width, int height)
    : is_running{false}, last_frame_ticks_ms{0.0f}, components{} {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    throw "error initializing SDL";
  }

  SDL_Window *window = SDL_CreateWindow(
      "2d game engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width,
      height, SDL_WINDOW_BORDERLESS);

  if (!(window)) {
    throw "error creating SDL window";
  }

  SDL_Renderer *raw_ren = SDL_CreateRenderer(window, -1, 0);

  renderer = std::shared_ptr<SDL_Renderer>(
      raw_ren, [](SDL_Renderer *renderer) { SDL_DestroyRenderer(renderer); });

  if (!(renderer)) {
    throw "error creating SDL renderer";
  }

  is_running = true;
}

Game::Game() : Game(WINDOW_WIDTH, WINDOW_HEIGHT){};

Game::~Game() {
  SDL_DestroyWindow(window);
  std::cout << "Game destructed!" << std::endl;
}

void Game::add_component(Component *component) {
  components.push_back(component);
}

void Game::control(SDL_Event &event) {
  switch (event.type) {
  case SDL_QUIT:
    is_running = false;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      is_running = false;
      break;
    }
  default:
    break;
  }
}

void Game::render() {
  SDL_Delay(MS_PER_FRAME);

  float delta_time_s = (SDL_GetTicks() - last_frame_ticks_ms) / 1000.f;
  last_frame_ticks_ms = SDL_GetTicks();

  delta_time_s = delta_time_s > 0.05f ? 0.05f : delta_time_s;

  SDL_SetRenderDrawColor(renderer.get(), 21, 21, 21, 255);
  SDL_RenderClear(renderer.get());
  for (auto &component : components) {
    component->render(delta_time_s, renderer);
  }
  SDL_RenderPresent(renderer.get());
  SDL_RenderClear(renderer.get());
}

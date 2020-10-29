#pragma once

#include "Game.hpp"
#include "Constants.hpp"
#include "InitException.hpp"
#include "Window.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <utility>

Game::Game(int w, int h)
    : window{nullptr}, renderer{nullptr}, projectiles{},
      last_frame_ticks_ms(0.0f), is_running{false} {

  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    throw InitException("SDL");
  }

  window = new Window("oo game engine", w, h);
  renderer = new Renderer(window);

  int j{10};
  for (int i{10}; i; --i) {
    int randNum = rand() % w;
    projectiles.push_back(Projectile{{j += 10, 20}, {10, 10}});
  }

  is_running = true;
}

Game::Game() : Game(WINDOW_WIDTH, WINDOW_HEIGHT){};

Game::~Game() {
  delete renderer;
  delete window;
}

Game::Game(const Game &that) : Game(that.window->w, that.window->h) {}

Game &Game::operator=(const Game &that) { return *this = Game(that); }

Game::Game(Game &&that) noexcept {
  window = std::exchange(that.window, nullptr);
  renderer = std::exchange(that.renderer, nullptr);
  projectiles.swap(that.projectiles);
}

Game &Game::operator=(Game &&that) {
  std::swap(window, that.window);
  std::swap(renderer, that.renderer);
  projectiles.swap(that.projectiles);
  return *this;
}

static bool is_terminated(const Event &event) {
  switch (event.type) {
  case SDL_QUIT:
    return true;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      return true;
    }
  default:
    return false;
  }
}

void Game::update(const Event &event) {
  is_running = !is_terminated(event);
  for (auto &projectile : projectiles) {
    projectile.control(event);
    projectile.transform(renderer->dt);
    projectile.move({0, 170}, renderer->dt);
  }
  renderer->render<Projectile>(&projectiles);
}

#pragma once

#include "Game.hpp"
#include "Constants.hpp"
#include "InitException.hpp"
#include "Rectangle.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_rect.h>
#include <cstdlib>
#include <iostream>
#include <utility>

Game::Game(const int w, const int h)
    : window{nullptr}, renderer{nullptr}, snowflakes{},
      ground({0, WINDOW_HEIGHT}, {WINDOW_WIDTH, 0}), contacts{0},
      last_frame_ticks_ms(0.0f), is_running{false} {

  contacts = 0;
  if (SDL_Init(SDL_INIT_EVERYTHING)) {
    throw InitException("SDL");
  }

  window = new Window("oo game engine", w, h);
  renderer = new Renderer(window);

  for (int i{100'000}; i; --i) {
    int rand_x = rand() % w;
    int rand_y = rand() % 800 + 100;
    int rand_vel_y = rand() % 200 + 150;
    snowflakes.push_back(Snowflake{{rand_x, -rand_y}, {2, 2}, {0, rand_vel_y}});
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

Game::Game(Game &&that)
    : window{std::exchange(that.window, nullptr)}, renderer{std::exchange(
                                                       that.renderer, nullptr)},
      ground(that.ground), snowflakes{} {
  snowflakes.swap(that.snowflakes);
}

Game &Game::operator=(Game &&that) {
  std::swap(window, that.window);
  std::swap(renderer, that.renderer);
  snowflakes.swap(that.snowflakes);
  std::swap(ground, that.ground);
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
  renderer->reset();
  is_running = !is_terminated(event);

  for (auto &snowflake : snowflakes) {
    if (snowflake.y >= ground.y) {
      contacts++;
      snowflake.y = -10;
      snowflake.landed = true;
      if (!(contacts % 1000)) {
        ground.transform(renderer->dt);
        ground.move(renderer->dt);
      }
      continue;
    }

    if (!snowflake.landed) {
      snowflake.control(event);
      snowflake.transform(renderer->dt);
      snowflake.move(renderer->dt);
      renderer->render<Snowflake>(snowflake);
    }
  }

  renderer->render<Rectangle>(ground);
  renderer->flush();
}

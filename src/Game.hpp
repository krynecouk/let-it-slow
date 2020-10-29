#pragma once

#include "Projectile.hpp"
#include "Renderer.hpp"
#include "Window.hpp"

class Game {
  Window *window;
  Renderer *renderer;
  std::vector<Projectile> projectiles;
  float last_frame_ticks_ms;

public:
  Game();
  Game(int width, int height);
  ~Game();
  Game(const Game &that);
  Game &operator=(const Game &that);
  Game(Game &&that) noexcept;
  Game &operator=(Game &&that);

  bool is_running;
  virtual void update(const Event &event);
};

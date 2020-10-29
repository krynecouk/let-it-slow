#pragma once

#include "Ground.hpp"
#include "Renderer.hpp"
#include "Snowflake.hpp"
#include "Window.hpp"

class Game {
  Window *window;
  Renderer *renderer;
  std::vector<Snowflake> snowflakes;
  Ground ground;
  int contacts;
  float last_frame_ticks_ms;

public:
  Game();
  Game(const int width, const int height);
  ~Game();
  Game(const Game &that);
  Game &operator=(const Game &that);
  Game(Game &&that);
  Game &operator=(Game &&that);

  bool is_running;
  virtual void update(const Event &event);
};

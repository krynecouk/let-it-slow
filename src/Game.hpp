#pragma once

#include "../lib/glm/glm.hpp"
#include "Component.hpp"
#include "Controllable.hpp"
#include "Renderable.hpp"
#include "SDL2/SDL.h"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <memory>
#include <vector>

class Game : public Controllable<SDL_Event> {
  SDL_Window *window;
  float last_frame_ticks_ms;
  std::vector<Component *> components;

public:
  Game();
  Game(int width, int height);
  ~Game();
  bool is_running;
  std::shared_ptr<SDL_Renderer> renderer;
  void control(SDL_Event &event) override;
  void add_component(Component *component);
  void render();
};

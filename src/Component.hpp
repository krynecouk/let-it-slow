#pragma once

#include "Renderable.hpp"
#include <SDL2/SDL_render.h>

class Component : public Renderable<SDL_Renderer> {
public:
  virtual ~Component(){};
};

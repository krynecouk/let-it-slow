#pragma once

#include "Projectile.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <iostream>
#include <memory>

void Projectile::move(float dt) {
  x += vel_x * dt;
  y += vel_y * dt;
}

void Projectile::transform(float dt) {
  // do nothing now
}

void Projectile::control(SDL_Event &event) {
  // do nothing now
}

void Projectile::render(float dt, std::shared_ptr<SDL_Renderer> renderer) {
  move(dt);
  transform(dt);
  SDL_Rect projectile{static_cast<int>(x), static_cast<int>(y), width, height};
  SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
  SDL_RenderFillRect(renderer.get(), &projectile);
}

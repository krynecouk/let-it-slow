#pragma once

#include "Projectile.hpp"
#include "Rectangle.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <SDL2/SDL_keycode.h>

Projectile::Projectile(const Vec2<> position, const Vec2<> size)
    : Rectangle{position.x, position.y, size.x, size.y}, Movable(),
      Transformable() {}

void Projectile::move(const Vec2<> velocity, const float dt) {
  x += velocity.x * dt;
  y += velocity.y * dt;
}

void Projectile::transform(const float dt) {
  // do nothing now
}

void Projectile::control(const SDL_Event &event) {
  // do nothing now
}

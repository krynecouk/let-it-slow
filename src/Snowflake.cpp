#pragma once

#include "Snowflake.hpp"
#include "Rectangle.hpp"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include <SDL2/SDL_keycode.h>

Snowflake::Snowflake(const Vec2<> position, const Vec2<> size,
                     const Vec2<> velocity)
    : velocity{velocity}, Rectangle{position.x, position.y, size.x, size.y},
      Movable(), landed{false}, Transformable() {}

void Snowflake::move(const float dt) {
  x += velocity.x * dt;
  y += velocity.y * dt;
}

void Snowflake::transform(const float dt) {
  // do nothing now
}

void Snowflake::control(const SDL_Event &event) {
  // do nothing now
}

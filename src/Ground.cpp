#pragma once

#include "Ground.hpp"

Ground::Ground(const Vec2<> position, const Vec2<> size)
    : Rectangle{position.x, position.y, size.x, size.y}, Movable(),
      Transformable() {}

void Ground::move(const float dt) { y -= 1; }

void Ground::transform(const float dt) { h += 1; }

#pragma once

#include "Vec2.hpp"

class Movable {
public:
  virtual void move(const Vec2<> velocity, const float dt) = 0;
};

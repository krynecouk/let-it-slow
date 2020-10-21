#pragma once

#include "../lib/glm/vec2.hpp"

class Movable {
public:
  float x;
  float y;
  float vel_x;
  float vel_y;
  virtual void move(float dt) = 0;
  Movable(float x, float y, float vel_x, float vel_y)
      : x{x}, y{y}, vel_x{vel_x}, vel_y{vel_y} {};
  Movable(glm::vec2 position, glm::vec2 velocity)
      : Movable(position.x, position.y, velocity.x, velocity.y){};
};

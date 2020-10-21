#pragma once

#include "../lib/glm/vec2.hpp"

class Transformable {
public:
  int width;
  int height;
  virtual void transform(float dt) = 0;
  Transformable(int width, int height) : width{width}, height{height} {};
  Transformable(glm::vec2 size) : Transformable(size.x, size.y){};
};

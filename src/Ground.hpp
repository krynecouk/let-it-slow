#pragma once

#include "Movable.hpp"
#include "Rectangle.hpp"
#include "Transformable.hpp"
#include "Vec2.hpp"

class Ground : public Rectangle, public Transformable, public Movable {
public:
  explicit Ground(const Vec2<> position, const Vec2<> size);
  void move(const float dt) override;
  void transform(const float dt) override;
};

#pragma once

#include "Controllable.hpp"
#include "Movable.hpp"
#include "Rectangle.hpp"
#include "Transformable.hpp"
#include "Vec2.hpp"

class Projectile : public Rectangle,
                   public Controllable<>,
                   public Movable,
                   public Transformable {
public:
  explicit Projectile(const Vec2<> position, const Vec2<> size);
  void control(const Event &event) override;
  void move(const Vec2<> velocity, const float dt) override;
  void transform(const float dt) override;
};

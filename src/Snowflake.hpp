#pragma once

#include "Controllable.hpp"
#include "Movable.hpp"
#include "Rectangle.hpp"
#include "Transformable.hpp"
#include "Vec2.hpp"

class Snowflake : public Rectangle,
                  public Controllable<>,
                  public Movable,
                  public Transformable {
  Vec2<> velocity;

public:
  explicit Snowflake(const Vec2<> position, const Vec2<> size,
                     const Vec2<> velocity);
  void control(const Event &event) override;
  void move(const float dt) override;
  void transform(const float dt) override;
  bool landed;
};

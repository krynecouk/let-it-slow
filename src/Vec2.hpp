#pragma once

template <typename T = int> class Vec2 {

public:
  T x, y;
  Vec2(T x, T y) : x(x), y(y) {}

  Vec2 operator+(const Vec2 &v) { return Vec2(x + v.x, y + v.y); }

  Vec2 operator+=(const Vec2 &v) {
    x += v.x;
    y += v.y;

    return *this;
  }

  Vec2 operator-(const Vec2 &v) { return Vec2(x - v.x, y - v.y); }

  Vec2 operator-=(const Vec2 &v) {
    x -= v.x;
    y -= v.y;

    return *this;
  }
};

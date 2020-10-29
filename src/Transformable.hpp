#pragma once

#include <iostream>

class Transformable {
public:
  virtual void transform(float dt) = 0;
};

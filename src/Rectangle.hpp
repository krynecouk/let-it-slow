#pragma once

#include <SDL_rect.h>

class Rectangle : public SDL_Rect {
public:
  Rectangle(const int x, const int y, const int w, const int h)
      : SDL_Rect{x, y, w, h} {};
};

#pragma once

#include <SDL_video.h>
#include <string>

class Window {
  std::string name;
  SDL_Window *raw_window;

public:
  explicit Window(std::string name, const unsigned int w, const unsigned int h);
  ~Window();
  Window(const Window &that);
  Window(Window &&that);
  Window &operator=(Window that);

  unsigned int w;
  unsigned int h;
  SDL_Window *get();
};

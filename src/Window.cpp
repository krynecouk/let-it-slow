#include "Window.hpp"
#include "InitException.hpp"
#include <iostream>
#include <type_traits>
#include <utility>

Window::Window(std::string name, const unsigned int w, const unsigned int h)
    : name{name}, w{w}, h{h}, raw_window(nullptr) {

  raw_window =
      SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_BORDERLESS);

  if (!(raw_window)) {
    throw InitException("SDL Window");
  }
}

Window::~Window() { SDL_DestroyWindow(raw_window); }

Window::Window(const Window &that) : Window(that.name, that.w, that.h) {}

Window::Window(Window &&that) {
  std::swap(name, that.name);
  std::swap(w, that.w);
  std::swap(h, that.h);
  raw_window = std::exchange(that.raw_window, nullptr);
}

Window &Window::operator=(Window that) {
  return *this = Window(std::move(that));
}

SDL_Window *Window::get() { return raw_window; }

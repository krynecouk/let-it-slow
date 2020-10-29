#include "Game.hpp"

int main() {
  Game game{};

  for (int i{30}; i; --i) {
    if (!game.is_running) {
      break;
    }

    SDL_Event event;
    SDL_PollEvent(&event);
    game.update(event);
  }
  return 0;
}

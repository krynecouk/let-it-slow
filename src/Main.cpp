#include "Constants.hpp"
#include "Game.hpp"
#include "Projectile.hpp"
#include <iostream>
#include <memory>

int main() {
  Game game{};
  Projectile projectile{};
  game.add_component(&projectile);
  int i{100};
  while (i) {
    if (!game.is_running) {
      break;
    }
    SDL_Event event;
    SDL_PollEvent(&event);
    game.control(event);
    game.render();
    i--;
  }
  return 0;
}

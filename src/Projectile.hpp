#pragma once

#include "../lib/glm/vec2.hpp"
#include "Component.hpp"
#include "Controllable.hpp"
#include "Movable.hpp"
#include "Transformable.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <memory>

class Projectile : public Component,
                   public Controllable<SDL_Event>,
                   public Movable,
                   public Transformable {

public:
  Projectile(glm::vec2 position = {10.0f, 10.0f},
             glm::vec2 velocity = {40.0f, 40.0f}, glm::vec2 size = {10, 10})
      : Movable(position, velocity), Transformable(size){};

  ~Projectile(){};
  void render(float dt, std::shared_ptr<SDL_Renderer> renderer) override;
  void control(SDL_Event &event) override;
  void move(float dt) override;
  void transform(float dt) override;
};

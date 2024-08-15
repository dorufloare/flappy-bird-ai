#pragma once
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "textures.hpp"

class Bird {
public:
  Bird();
  void update();
  void jump();
  const sf::Sprite getSprite() const;
  sf::Sprite& getSprite();
  bool isAlive();
  void die();
  float getPositionY();
  bool outOfScreen();
private:
  sf::Sprite sprite;
  sf::Vector2f velocity;
  bool alive;
};

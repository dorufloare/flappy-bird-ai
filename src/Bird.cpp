#include "Bird.hpp"

Bird::Bird() {
  sprite.setTexture(BIRD_TEXTURE);
  sprite.setPosition(BIRD_POSITION_X, BIRD_POSITION_Y);
  velocity.y = 0;
  alive = true;

  float scaleX = BIRD_WIDTH / BIRD_TEXTURE.getSize().x;
  float scaleY = BIRD_HEIGHT / BIRD_TEXTURE.getSize().y;

  sprite.setScale(scaleX, scaleY);
}

void Bird::update() {
  if (!isAlive())
    return;

  velocity.y += GRAVITY;
  sprite.move(0, velocity.y);
}

bool Bird::outOfScreen() {
  return (sprite.getPosition().y < 0 || sprite.getPosition().y + BIRD_HEIGHT >= SCREEN_HEIGHT) ;
}

void Bird::jump() {
  velocity.y = JUMP_FORCE;
}

const sf::Sprite Bird::getSprite() const {
  return sprite;
}

sf::Sprite& Bird::getSprite() {
  return sprite;
}

bool Bird::isAlive() {
  return alive;
}

void Bird::die() {
  alive = false;
}

float Bird::getPositionY() {
  return sprite.getPosition().y;
}

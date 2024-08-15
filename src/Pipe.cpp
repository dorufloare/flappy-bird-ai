#include "Pipe.hpp"
#include "textures.hpp"
#include "constants.hpp"
#include <iostream>

Pipe::Pipe(float x) {
  
  float gap = PIPE_GAP;
  pipeHeight = std::rand() % (int)(SCREEN_HEIGHT - gap);
  upperSprite.setTexture(PIPE_TEXTURE);
  upperSprite.setPosition(x, 0);
  upperSprite.setTextureRect(sf::IntRect(0, 0, PIPE_WIDTH, pipeHeight));
  lowerSprite.setTexture(PIPE_TEXTURE);
  lowerSprite.setTextureRect(sf::IntRect(0, pipeHeight + gap, PIPE_WIDTH, SCREEN_HEIGHT - pipeHeight - gap));
  lowerSprite.setPosition(x, pipeHeight + gap);
}

void Pipe::update() {
  lowerSprite.move(-PIPE_SPEED, 0);
  upperSprite.move(-PIPE_SPEED, 0);
} 

const sf::Sprite Pipe::getLowerSprite() const {
  return lowerSprite;
}

const sf::Sprite Pipe::getUpperSprite() const {
  return upperSprite;
}

sf::Sprite& Pipe::getLowerSprite() {
  return lowerSprite;
}

sf::Sprite& Pipe::getUpperSprite() {
  return upperSprite;
}

bool Pipe::isOffScreen() const {
  return lowerSprite.getPosition().x + PIPE_WIDTH < 0;
}

float Pipe::getPositionX() const {
  return lowerSprite.getPosition().x;
}

std::pair<float,float> Pipe::getGap() {
  return std::make_pair(upperSprite.getPosition().y + pipeHeight, lowerSprite.getPosition().y);
}
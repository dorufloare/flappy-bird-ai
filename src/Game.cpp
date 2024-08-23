#include "Game.hpp"
#include "textures.hpp"
#include <iostream>

Game::Game() {
  pipeSpawnTimer = 0;
  score = 0;
  gameOver = false;
  nearestPipeIndex = -1;

  pipes.clear();
  bird = Bird();
}

void Game::update() {
  if (gameOver)
    return;

  bird.update();
  checkForNewPipes();
  removeOldPipes();
  updateScore();
  nearestPipeIndex = getNearestPipeIndex();
  checkForCollisions();
}

void Game::updateScore() {
  if (nearestPipeIndex == -1)
    return;

  if (pipes[nearestPipeIndex].getRightside() < BIRD_POSITION_X)
    ++score;
}

void Game::removeOldPipes() {
  for (auto it = pipes.begin(); it != pipes.end(); ) {
    it->update();
    if (it->isOffScreen()) {
      it = pipes.erase(it);
    } else {
      ++it;
    }
  }
}

void Game::checkForNewPipes() {
  sf::Time dt = clock.restart();
  pipeSpawnTimer += dt.asSeconds();

  if (pipeSpawnTimer > PIPE_SPAWN_INTERVAL) {
    pipeSpawnTimer = 0;
    addNewPipe();
  }
}

void Game::flapBird() {
  bird.jump();
}

void Game::addNewPipe() {
  pipes.emplace_back(SCREEN_WIDTH);
}

void Game::draw(sf::RenderWindow& window) {
  drawTextures(window, bird, pipes);
}

void Game::checkForCollisions() {
  if (bird.outOfScreen()) {
    endGame();
    return;
  }

  if (nearestPipeIndex == -1)
    return;

  if (collisionWithPipe(pipes[nearestPipeIndex])) {
    endGame();
  }
}

bool Game::collisionWithPipe(Pipe& pipe) {
  //we havent reached the pipe yet
  if (BIRD_POSITION_X + BIRD_WIDTH < pipe.getPositionX())
    return false;

  float birdTop = bird.getPositionY();
  float birdBottom = birdTop + BIRD_HEIGHT;

  std::pair<float,float> pipeGap = pipe.getGap();

  //we are inside the gap
  if (pipeGap.first < birdTop && birdBottom < pipeGap.second) {
    return false;
  }

  return true;
}

//first pipe with the rightside after the birds back
int Game::getNearestPipeIndex() {
  if (pipes.empty()) 
    return -1;
  
  float birdPosition = BIRD_POSITION_X;

  //the pipes are sorted from left to right
  for (int i = 0; i < (int)pipes.size(); ++i) {
    float pipeRightPosition = pipes[i].getRightside();

    if (birdPosition <= pipeRightPosition)
      return i;
  }
  return -1;
}

void Game::endGame() {
  gameOver = true;
  std::cout << "GAME OVER" << std::endl;
  bird.die();
}

float Game::getVerticalDistance() {
  if (nearestPipeIndex == -1)   //pipes havent spawned yet
    return 0;

  std::pair<float,float> nextGap = pipes[nearestPipeIndex].getGap();
  int nextGapMidpoint = (nextGap.first + nextGap.second) / 2;

  return bird.getPositionY() - nextGapMidpoint;
}

float Game::getHorizontalDistance() {
  if (nearestPipeIndex == -1)  //pipes havent spawned yet
    return SCREEN_WIDTH;

  int nextPipeRightside = pipes[nearestPipeIndex].getRightside();

  return nextPipeRightside - BIRD_POSITION_X;
}

float Game::getBirdPosition() {
  return bird.getPositionY();
}

bool Game::isGameOver() {
  return gameOver;
}

int Game::getScore() {
  return score;
}
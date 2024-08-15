#include "Game.hpp"
#include "textures.hpp"
#include <iostream>

Game::Game() {
  pipeSpawnTimer = 0;
  pipes.clear();
  gameOver = false;
  bird = Bird();
}

void Game::update() {
  if (gameOver)
    return;

  bird.update();
  checkForNewPipes();
  removeOldPipes();
  checkForCollisions();
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

  int nearestPipe = getNearestPipeIndex();
  if (nearestPipe == -1)
    return;

  if (collisionWithPipe(pipes[nearestPipe])) {
    endGame();
  }
}

bool Game::collisionWithPipe(Pipe& pipe) {
  //we havent reached the pipe yet
  if (BIRD_POSITION_X + BIRD_WIDTH < pipe.getPositionX())
    return false;

  //we are in the gap
  float birdTop = bird.getPositionY();
  float birdBottom = birdTop + BIRD_HEIGHT;

  std::pair<float,float> pipeGap = pipe.getGap();

  if (pipeGap.first < birdTop && birdBottom < pipeGap.second)
    return false;

  std::cout << "Collision with pipe: " << pipeGap.first << ' ' << pipeGap.second 
            << " and bird " << birdTop << ' ' << birdBottom << std::endl;

  return true;
}

//first pipe with the rightside after the birds back
int Game::getNearestPipeIndex() {
  if (pipes.empty()) 
    return -1;
  
  float birdPosition = BIRD_POSITION_X;

  //the pipes are sorted from left to right
  for (int i = 0; i < (int)pipes.size(); ++i) {
    float pipeRightPosition = pipes[i].getPositionX() + PIPE_WIDTH;

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
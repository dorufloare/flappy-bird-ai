#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include "Bird.hpp"
#include "Pipe.hpp"
#include "constants.hpp"
#include "textures.hpp"
#include "Game.hpp"
#include "QLearningAI.hpp"

bool isBenchmark(int value) {
  auto it = std::find(std::begin(benchmarks), std::end(benchmarks), value);
  return it != std::end(benchmarks); 
}

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
  window.setFramerateLimit(60);

  loadAssets();

  Game game;
  QLearningAI ai;
  sf::Clock aiTimer;
  sf::Text scoreText;

  scoreText.setFont(ARIAL_FONT);
  scoreText.setCharacterSize(24);
  scoreText.setFillColor(sf::Color::Black);
  scoreText.setPosition(50, 50);

  int maxScore = 0;
  std::ofstream fout("scores.txt");

  //if you want to resume activity
  //ai.loadFromFile("");  

  for (int episode = 0; episode < NR_EPISODES; ++episode) {
    game = Game();

    float reward = 0;
    int steps = 0;
    int lastScore = 0;
    bool done = false;

    while (!done && steps++ < MAX_STEPS) {
      sf::Event event;
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
          window.close();
          return 0; 
        } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
          window.close();
          return 0; 
        }
      }

      if (aiTimer.getElapsedTime().asSeconds() < AI_DECISION_INTERVAL) {
        game.draw(window);
        window.draw(scoreText);
        game.update();
        window.display();
        continue;
      }

      aiTimer.restart();

      int verticalDistance = game.getVerticalDistance() / PIXEL_VERTICAL_GROUP;
      int horizontalDistance = game.getHorizontalDistance()  / PIXEL_HORIZONTAL_GROUP;

      int action = ai.chooseAction(verticalDistance, horizontalDistance);
      
      //a little assist | dont go out of the screen
      if (action == 1 && game.getBirdPosition() > SCREEN_BORDER)
        game.flapBird();
      if (game.getBirdPosition() > SCREEN_HEIGHT - SCREEN_BORDER)
        game.flapBird();

      game.update();
      maxScore = std::max(maxScore, game.getScore());
      scoreText.setString(
        "generation: " + std::to_string(episode) + "\n" + 
        "current score: " + std::to_string(game.getScore()) + "\n" + 
        "highscore: " + std::to_string(maxScore));
      done = game.isGameOver();

      if (done)
        reward += DEATH_REWARD;
      else {
        reward += ALIVE_REWARD;
        if (game.getScore() != lastScore) {
          lastScore = game.getScore();
          reward += PASSED_PIPE_REWARD;
        }
      }

      int nextVerticalDistance = game.getVerticalDistance() / PIXEL_VERTICAL_GROUP;
      int nextHorizontalDistance = game.getHorizontalDistance() / PIXEL_HORIZONTAL_GROUP;

      ai.updateQValue(
        verticalDistance, 
        horizontalDistance, 
        action, 
        reward, 
        nextVerticalDistance, 
        nextHorizontalDistance
      );

      game.draw(window);
      window.draw(scoreText);
      window.display();
    }
    ai.epsilon = std::max(ai.epsilon * DECAY_RATE, 0.01f);

    std::cout << "Episode " << episode << " completed with score: " << game.getScore() << ' ' << std::endl;

    if (isBenchmark(episode)) {
      std::string filename = "episode" + std::to_string(episode) + "highscore" + std::to_string(maxScore) + ".txt";
      ai.saveInFile(filename);
    }
    fout << episode << " : " << lastScore << '\n';
  }

  fout.close();

  return 0;
}

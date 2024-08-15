#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Bird.hpp"
#include "Pipe.hpp"
#include "constants.hpp"
#include "textures.hpp"
#include "Game.hpp"

int main() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));
  
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Flappy Bird");
  window.setFramerateLimit(60);

  loadTextures();

  Game game;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        game.flapBird();
      }
    }

    game.update();
    game.draw(window);
  }

  return 0;
}

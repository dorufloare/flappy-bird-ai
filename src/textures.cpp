#include "textures.hpp"
#include "Bird.hpp"
#include "Pipe.hpp"

sf::Texture PIPE_TEXTURE;
sf::Texture BIRD_TEXTURE;
sf::Font ARIAL_FONT;

void loadAssets() {
  PIPE_TEXTURE.loadFromFile("./assets/images/pipe.png");
  BIRD_TEXTURE.loadFromFile("./assets/images/bird.png");
  ARIAL_FONT.loadFromFile("./assets/fonts/arial.ttf");
}

void drawTextures(sf::RenderWindow& window, const Bird& bird, const std::vector<Pipe>& pipes) {
  window.clear(sf::Color::Cyan);

  window.draw(bird.getSprite());

  for (const auto& pipe : pipes) {
    window.draw(pipe.getLowerSprite());
    window.draw(pipe.getUpperSprite());
  }
}

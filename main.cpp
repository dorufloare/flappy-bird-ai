#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

const float GRAVITY = 0.5f;
const float JUMP_FORCE = -10.0f;
const float PIPE_SPEED = 3.0f;
const float PIPE_SPACING = 300.0f;
const float PIPE_WIDTH = 80.0f;
const float PIPE_HEIGHT = 600.0f;

class Bird {
public:
  Bird() {
    texture.loadFromFile("./assets/images/bird.png");
    sprite.setTexture(texture);
    sprite.setPosition(100, 300);
    velocity.y = 0;
  }

  void update() {
    velocity.y += GRAVITY;
    sprite.move(0, velocity.y);
    if (sprite.getPosition().y > 600 - sprite.getGlobalBounds().height) {
      sprite.setPosition(sprite.getPosition().x, 600 - sprite.getGlobalBounds().height);
      velocity.y = 0;
    }
  }

  void jump() {
    velocity.y = JUMP_FORCE;
  }

  sf::Sprite& getSprite() {
    return sprite;
  }

private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Vector2f velocity;
};

class Pipe {
public:
  Pipe(float x) {
    texture.loadFromFile("./assets/images/pipe.png");
    sprite.setTexture(texture);
    sprite.setPosition(x, 0);
    float gap = 200.0f;
    float pipeHeight = std::rand() % (int)(600 - gap);
    sprite.setTextureRect(sf::IntRect(0, 0, PIPE_WIDTH, pipeHeight));
    upperSprite.setTexture(texture);
    upperSprite.setTextureRect(sf::IntRect(0, pipeHeight + gap, PIPE_WIDTH, PIPE_HEIGHT - pipeHeight - gap));
    upperSprite.setPosition(x, pipeHeight + gap);
  }

  void update() {
    sprite.move(-PIPE_SPEED, 0);
    upperSprite.move(-PIPE_SPEED, 0);
  }

  sf::Sprite& getSprite() {
    return sprite;
  }

  sf::Sprite& getUpperSprite() {
    return upperSprite;
  }

  bool isOffScreen() const {
    return sprite.getPosition().x + PIPE_WIDTH < 0;
  }

private:
  sf::Texture texture;
  sf::Sprite sprite;
  sf::Sprite upperSprite;
};

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Bird");
  window.setFramerateLimit(60);

  Bird bird;
  std::vector<Pipe> pipes;

  std::srand(static_cast<unsigned>(std::time(nullptr)));
  float pipeSpawnTimer = 0;
  const float pipeSpawnInterval = 2.0f;
  sf::Clock clock;

  while (window.isOpen()) {
    sf::Time dt = clock.restart();
    pipeSpawnTimer += dt.asSeconds();

    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
        bird.jump();
      }
    }

    bird.update();

    if (pipeSpawnTimer > pipeSpawnInterval) {
      pipeSpawnTimer = 0;
      pipes.emplace_back(800);
    }

    for (auto it = pipes.begin(); it != pipes.end(); ) {
      it->update();
      if (it->isOffScreen()) {
        it = pipes.erase(it);
      } else {
        ++it;
      }
    }

    window.clear(sf::Color::Cyan);

    window.draw(bird.getSprite());
    for (auto pipe : pipes) {
      window.draw(pipe.getSprite());
      window.draw(pipe.getUpperSprite());
    }

    window.display();
  }

  return 0;
}

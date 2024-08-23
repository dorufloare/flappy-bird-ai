#include <SFML/Graphics.hpp>

#include "Bird.hpp"
#include "Pipe.hpp"

class Game {
  public:
    Game();
    void update();
    void flapBird();
    void draw(sf::RenderWindow &window);
    void endGame();
    int getScore();
    bool isGameOver();
    void updateScore();

    //bird-pipe distance
    float getVerticalDistance();
    float getHorizontalDistance();
    float getBirdPosition();

  private:
    void checkForNewPipes();
    void addNewPipe();
    void removeOldPipes();
    void checkForCollisions();
    int getNearestPipeIndex();
    bool collisionWithPipe(Pipe& pipe);

    Bird bird;
    std::vector<Pipe> pipes;
    sf::Clock clock;
    float pipeSpawnTimer;
    bool gameOver;
    int score;
    int nearestPipeIndex;
};
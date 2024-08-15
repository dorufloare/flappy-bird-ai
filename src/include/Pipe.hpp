#pragma once
#include <SFML/Graphics.hpp>
#include "constants.hpp"
#include "textures.hpp"

class Pipe {
public:
    Pipe(float x);
    void update();
    const sf::Sprite getLowerSprite() const;
    const sf::Sprite getUpperSprite() const;
    sf::Sprite& getLowerSprite();
    sf::Sprite& getUpperSprite();
    bool isOffScreen() const;
    float getPositionX() const;
    std::pair<float,float> getGap();
private:
    sf::Sprite lowerSprite;
    sf::Sprite upperSprite;
    int pipeHeight = 0;
};

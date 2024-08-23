#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

// Forward declarations 
class Bird;
class Pipe;

extern sf::Texture PIPE_TEXTURE;
extern sf::Texture BIRD_TEXTURE;

extern sf::Font ARIAL_FONT;

void loadAssets();
void drawTextures(sf::RenderWindow& window, const Bird& bird, const std::vector<Pipe>& pipes);

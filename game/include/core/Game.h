#pragma once

#include <SFML/Graphics.hpp>

#include "entities/Player.h"
#include "world/Level.h"

class Game {
private:
    sf::RenderWindow window;
    sf::View camera;

    Player player;
    Level level;

    sf::Font font;
    sf::Text coinText;
    int coinCount;

    void processEvents();
    void update(float dt);
    void render();

public:
    Game();

    void run();
};
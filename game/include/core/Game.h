#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Player.h"

class Game {
private:
    sf::RenderWindow window;
    Player player;

    void processEvents();
    void update(float dt);
    void render();

public:
    Game();

    void run();
};
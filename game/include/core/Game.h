#pragma once

#include <SFML/Graphics.hpp>
#include "entities/Player.h"
#include "world/Level.h"

class Game {
private:
    sf::RenderWindow window;
    Player player;
    Level level;

    void processEvents();
    void update(float dt);
    void render();

public:
    Game();

    void run();
};
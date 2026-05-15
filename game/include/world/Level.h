#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Level {
private:
    std::vector<std::string> map;

    const int tileSize = 32;

public:
    Level();

    void loadFromFile(const std::string& path);

    void draw(sf::RenderWindow& window);
};

#endif //GAME_LEVEL_H
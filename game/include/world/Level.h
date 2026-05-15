#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#pragma once

#include <SFML/Graphics.hpp>
#include "../entities/Coin.h"

#include <vector>
#include <string>

class Level {
private:
    std::vector<std::string> map;
    std::vector<Coin> coins;

    const int tileSize = 32;

public:
    Level();

    void loadFromFile(const std::string& path);

    void draw(sf::RenderWindow& window);

    std::vector<sf::FloatRect> getSolidBlocks() const;
    std::vector<Coin>& getCoins();
};
#endif //GAME_LEVEL_H
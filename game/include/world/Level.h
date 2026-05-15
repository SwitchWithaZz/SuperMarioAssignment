#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "../entities/Coin.h"

class Level {
private:
    std::vector<std::string> map;

    std::vector<Coin> coins;

    const int tileSize = 50;

public:
    Level();

    void loadFromFile(const std::string& path);

    void draw(sf::RenderWindow& window);

    std::vector<sf::FloatRect> getSolidBlocks() const;

    std::vector<Coin>& getCoins();
};
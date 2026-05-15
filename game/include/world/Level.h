#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "../entities/Coin.h"
#include "../entities/Mushroom.h"

class Level {
private:
    std::vector<std::string> map;

    std::vector<Coin> coins;
    std::vector<Mushroom> mushrooms;

    const int tileSize = 50;

public:
    Level();

    void loadFromFile(const std::string& path);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    std::vector<sf::FloatRect> getSolidBlocks() const;

    void hitBlockAbove(const sf::FloatRect& playerBounds);

    std::vector<Coin>& getCoins();
};
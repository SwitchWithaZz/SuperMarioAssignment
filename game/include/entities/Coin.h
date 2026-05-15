#ifndef GAME_COIN_HPP
#define GAME_COIN_HPP

#pragma once

#include <SFML/Graphics.hpp>

class Coin {
private:
    sf::RectangleShape shape;

    bool collected = false;

public:
    Coin(float x, float y);

    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;

    bool isCollected() const;

    void collect();
};

#endif //GAME_COIN_HPP
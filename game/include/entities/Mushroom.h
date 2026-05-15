#ifndef GAME_MUSHROOM_HPP
#define GAME_MUSHROOM_HPP

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Mushroom {
private:
    sf::RectangleShape body;
    sf::Vector2f velocity;

    float moveSpeed;
    float gravity;

public:
    Mushroom(float x, float y);

    void update(float dt, const std::vector<sf::FloatRect>& solidBlocks);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};

#endif //GAME_MUSHROOM_HPP
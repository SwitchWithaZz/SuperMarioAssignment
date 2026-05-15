#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Player {
private:
    sf::RectangleShape body;
    sf::Vector2f velocity;

    float moveSpeed;
    float jumpStrength;
    float gravity;

    bool isGrounded;

public:
    Player();

    void handleInput();
    void update(float dt, const std::vector<sf::FloatRect>& solidBlocks);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
};
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
    const sf::Texture marioTexture("../assets/textures/Mario/ClassicNES SMB Small Mario Sprite.png");
    inline sf::Sprite mario(marioTexture);

class Player {
private:


    sf::RectangleShape body;
    sf::Vector2f velocity;

    float moveSpeed;
    float jumpStrength;
    float gravity;

    bool isGrounded;
    bool hitHead;

    int frameX = 0;
    float animTimer = 0.f;

    void updateAnimation(float dt);

public:
    Player();

    void handleInput();
    void update(float dt, const std::vector<sf::FloatRect>& solidBlocks);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool didHitHead() const;

    void makeBig();
};
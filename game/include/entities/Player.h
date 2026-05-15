#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

class Player {
private:
    sf::RectangleShape body;
    sf::Vector2f velocity;

    sf::Texture smallMarioIdleTexture;
    sf::Texture bigMarioIdleTexture;

    std::array<sf::Texture, 3> smallMarioWalkRightTextures;
    std::array<sf::Texture, 3> smallMarioWalkLeftTextures;
    std::array<sf::Texture, 3> bigMarioWalkRightTextures;
    std::array<sf::Texture, 3> bigMarioWalkLeftTextures;

    sf::Texture smallMarioJumpRightTexture;
    sf::Texture smallMarioJumpLeftTexture;
    sf::Texture bigMarioJumpRightTexture;
    sf::Texture bigMarioJumpLeftTexture;

    sf::Sprite mario;

    float moveSpeed;
    float jumpStrength;
    float gravity;

    bool isGrounded;
    bool hitHead;
    bool isBig;
    bool facingRight;

    float animationTimer;
    int animationFrame;

    void updateSpriteSizeAndPosition();
    void updatePlayerTexture(float dt);
    void scaleSpriteToBody();
    void loadTexture(sf::Texture& texture, const std::string& path);

public:
    Player();

    void handleInput();
    void update(float dt, const std::vector<sf::FloatRect>& solidBlocks);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    bool didHitHead() const;

    void makeBig();
};
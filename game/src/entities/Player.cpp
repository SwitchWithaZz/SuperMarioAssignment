#include "entities/Player.h"
#include "core/InputManager.h"
#include "world/worldSize.h"

#include <cmath>
#include <iostream>
#include <string>

namespace {
    const float ANIMATION_SPEED = 0.12f;
}

Player::Player()
    : velocity(0.f, 0.f),
      smallMarioIdleTexture(),
      bigMarioIdleTexture(),
      smallMarioWalkRightTextures(),
      smallMarioWalkLeftTextures(),
      bigMarioWalkRightTextures(),
      bigMarioWalkLeftTextures(),
      smallMarioJumpRightTexture(),
      smallMarioJumpLeftTexture(),
      bigMarioJumpRightTexture(),
      bigMarioJumpLeftTexture(),
      mario(smallMarioIdleTexture),
      moveSpeed(450.f),
      jumpStrength(-950.f),
      gravity(2000.f),
      isGrounded(false),
      hitHead(false),
      isBig(false),
      facingRight(true),
      animationTimer(0.f),
      animationFrame(0) {

    loadTexture(smallMarioIdleTexture, "../assets/textures/Mario/ClassicNES SMB Small Mario Sprite.png");
    loadTexture(bigMarioIdleTexture, "../assets/textures/Mario/ClassicNES SMB Super Mario Sprite.png");

    loadTexture(smallMarioWalkRightTextures[0], "../assets/textures/Mario/smallWalkRight/smallRight1.png");
    loadTexture(smallMarioWalkRightTextures[1], "../assets/textures/Mario/smallWalkRight/smallRight2.png");
    loadTexture(smallMarioWalkRightTextures[2], "../assets/textures/Mario/smallWalkRight/smallRight3.png");

    loadTexture(smallMarioWalkLeftTextures[0], "../assets/textures/Mario/smallWalkLeft/smallLeft1.png");
    loadTexture(smallMarioWalkLeftTextures[1], "../assets/textures/Mario/smallWalkLeft/smallLeft2.png");
    loadTexture(smallMarioWalkLeftTextures[2], "../assets/textures/Mario/smallWalkLeft/SmallLeft3.png");

    loadTexture(bigMarioWalkRightTextures[0], "../assets/textures/Mario/bigMariowalkRight/bigRight1.png");
    loadTexture(bigMarioWalkRightTextures[1], "../assets/textures/Mario/bigMariowalkRight/bigRight2.png");
    loadTexture(bigMarioWalkRightTextures[2], "../assets/textures/Mario/bigMariowalkRight/bigRight3.png");

    loadTexture(bigMarioWalkLeftTextures[0], "../assets/textures/Mario/bigMariowalkLeft/bigLeft1.png");
    loadTexture(bigMarioWalkLeftTextures[1], "../assets/textures/Mario/bigMariowalkLeft/bigLeft2.png");
    loadTexture(bigMarioWalkLeftTextures[2], "../assets/textures/Mario/bigMariowalkLeft/bigLeft3.png");

    loadTexture(smallMarioJumpRightTexture, "../assets/textures/Mario/SmallMarioJmp.png");
    loadTexture(smallMarioJumpLeftTexture, "../assets/textures/Mario/SmallMarioJmpLeft.png");
    loadTexture(bigMarioJumpRightTexture, "../assets/textures/Mario/BigMarioJump.png");
    loadTexture(bigMarioJumpLeftTexture, "../assets/textures/Mario/BigMarioJumpLeft.png");

    body.setSize(sf::Vector2f(48.f, 64.f));
    body.setPosition(sf::Vector2f(100.f, 300.f));
    body.setFillColor(sf::Color::Transparent);

    mario.setTexture(smallMarioIdleTexture, true);

    scaleSpriteToBody();
    updateSpriteSizeAndPosition();
}

void Player::handleInput() {
    float movement = InputManager::getHorizontalMovement();
    velocity.x = movement * moveSpeed;

    if (movement > 0.f) {
        facingRight = true;
    }
    else if (movement < 0.f) {
        facingRight = false;
    }

    if (InputManager::isJumpPressed() && isGrounded) {
        velocity.y = jumpStrength;
        isGrounded = false;
    }
}

void Player::update(float dt, const std::vector<sf::FloatRect>& solidBlocks) {
    hitHead = false;

    body.move(sf::Vector2f(velocity.x * dt, 0.f));

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.x > 0.f) {
                body.setPosition(sf::Vector2f(
                    blockBounds.position.x - body.getSize().x,
                    body.getPosition().y
                ));
            }

            if (velocity.x < 0.f) {
                body.setPosition(sf::Vector2f(
                    blockBounds.position.x + blockBounds.size.x,
                    body.getPosition().y
                ));
            }

            velocity.x = 0.f;
        }
    }

    if (body.getPosition().x < 0.f) {
        body.setPosition(sf::Vector2f(0.f, body.getPosition().y));
    }

    if (body.getPosition().x + body.getSize().x > worldSize) {
        body.setPosition(sf::Vector2f(
            worldSize - body.getSize().x,
            body.getPosition().y
        ));
    }

    velocity.y += gravity * dt;

    body.move(sf::Vector2f(0.f, velocity.y * dt));

    isGrounded = false;

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.y > 0.f) {
                body.setPosition(sf::Vector2f(
                    body.getPosition().x,
                    blockBounds.position.y - body.getSize().y
                ));

                isGrounded = true;
            }

            if (velocity.y < 0.f) {
                body.setPosition(sf::Vector2f(
                    body.getPosition().x,
                    blockBounds.position.y + blockBounds.size.y
                ));

                hitHead = true;
            }

            velocity.y = 0.f;
        }
    }

    updatePlayerTexture(dt);
    updateSpriteSizeAndPosition();
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(mario);
}

sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}

bool Player::didHitHead() const {
    return hitHead;
}

void Player::makeBig() {
    if (isBig) {
        return;
    }

    sf::Vector2f oldPosition = body.getPosition();
    sf::Vector2f oldSize = body.getSize();

    body.setSize(sf::Vector2f(48.f, 96.f));

    body.setPosition(sf::Vector2f(
        oldPosition.x,
        oldPosition.y - (body.getSize().y - oldSize.y)
    ));

    isBig = true;
    animationTimer = 0.f;
    animationFrame = 0;

    updatePlayerTexture(0.f);
    updateSpriteSizeAndPosition();
}

void Player::updatePlayerTexture(float dt) {
    bool moving = std::abs(velocity.x) > 1.f;
    bool jumping = !isGrounded;

    if (jumping) {
        animationTimer = 0.f;
        animationFrame = 0;

        if (!isBig) {
            if (facingRight) {
                mario.setTexture(smallMarioJumpRightTexture, true);
            }
            else {
                mario.setTexture(smallMarioJumpLeftTexture, true);
            }
        }
        else {
            if (facingRight) {
                mario.setTexture(bigMarioJumpRightTexture, true);
            }
            else {
                mario.setTexture(bigMarioJumpLeftTexture, true);
            }
        }

        scaleSpriteToBody();
        return;
    }

    if (moving) {
        animationTimer += dt;

        if (animationTimer >= ANIMATION_SPEED) {
            animationTimer = 0.f;
            animationFrame++;

            if (animationFrame > 2) {
                animationFrame = 0;
            }
        }

        if (!isBig) {
            if (facingRight) {
                mario.setTexture(smallMarioWalkRightTextures[animationFrame], true);
            }
            else {
                mario.setTexture(smallMarioWalkLeftTextures[animationFrame], true);
            }
        }
        else {
            if (facingRight) {
                mario.setTexture(bigMarioWalkRightTextures[animationFrame], true);
            }
            else {
                mario.setTexture(bigMarioWalkLeftTextures[animationFrame], true);
            }
        }

        scaleSpriteToBody();
        return;
    }

    animationTimer = 0.f;
    animationFrame = 0;

    if (!isBig) {
        mario.setTexture(smallMarioIdleTexture, true);
    }
    else {
        mario.setTexture(bigMarioIdleTexture, true);
    }

    scaleSpriteToBody();
}

void Player::scaleSpriteToBody() {
    sf::Vector2u textureSize = mario.getTexture().getSize();

    if (textureSize.x > 0 && textureSize.y > 0) {
        mario.setScale(sf::Vector2f(
            body.getSize().x / static_cast<float>(textureSize.x),
            body.getSize().y / static_cast<float>(textureSize.y)
        ));
    }
}

void Player::updateSpriteSizeAndPosition() {
    mario.setPosition(sf::Vector2f(
        body.getPosition().x,
        body.getPosition().y
    ));
}

void Player::loadTexture(sf::Texture& texture, const std::string& path) {
    if (!texture.loadFromFile(path)) {
        std::cout << "Failed to load texture: " << path << "\n";
    }
}
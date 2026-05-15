#include "entities/Player.h"
#include "core/InputManager.h"
#include "world/worldSize.h"

Player::Player()
    : velocity(0.f, 0.f),
      moveSpeed(450.f),
      jumpStrength(-950.f),
      gravity(2000.f),
      isGrounded(false),

      hitHead(false) {

    mario.setTextureRect(sf::IntRect({0, 0}, {1, 1}));
    mario.setScale({4.f, 4.f});

    body.setSize({48.f, 64.f});
    //body.setFillColor(sf::Color::Red);
    body.setPosition({100.f, 300.f});
}

void Player::handleInput() {
    float movement = InputManager::getHorizontalMovement();
    velocity.x = movement * moveSpeed;

    if (InputManager::isJumpPressed() && isGrounded) {
        velocity.y = jumpStrength;
        isGrounded = false;
    }

    if (velocity.x < 0)
        mario.setScale({-4.f, 4.f});
    else if (velocity.x > 0)
        mario.setScale({4.f, 4.f});
}

void Player::update(float dt, const std::vector<sf::FloatRect>& solidBlocks) {
    hitHead = false;

    // Horizontal movement
    body.move({velocity.x * dt, 0.f});
    mario.move({velocity.x * dt, 0.f});

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = mario.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.x > 0.f) {
                body.setPosition({
                    blockBounds.position.x - body.getSize().x,
                    body.getPosition().y
                });
                mario.setPosition({
                    blockBounds.position.x - body.getSize().x,
                    body.getPosition().y
                });
            }

            if (velocity.x < 0.f) {
                body.setPosition({
                    blockBounds.position.x + blockBounds.size.x,
                    body.getPosition().y
                });
                mario.setPosition({
                    blockBounds.position.x + blockBounds.size.x,
                    body.getPosition().y
                });
            }

            velocity.x = 0.f;
        }
        updateAnimation(dt);
    }

    // Screen boundaries
    if (body.getPosition().x < 0.f) {
        body.setPosition({0.f, body.getPosition().y});
        mario.setPosition({0.f, body.getPosition().y});
    }

    if (body.getPosition().x + body.getSize().x > worldSize) {
        body.setPosition({worldSize - body.getSize().x, body.getPosition().y});
        mario.setPosition({worldSize - body.getSize().x, body.getPosition().y});
    }

    // Vertical movement
    velocity.y += gravity * dt;
    body.move({0.f, velocity.y * dt});
    mario.move({0.f, velocity.y * dt});

    isGrounded = false;

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.y > 0.f) {
                body.setPosition({
                    body.getPosition().x,
                    blockBounds.position.y - body.getSize().y
                });
                mario.setPosition({
                    body.getPosition().x,
                    blockBounds.position.y - body.getSize().y
                });

                isGrounded = true;
            }

            if (velocity.y < 0.f) {
                body.setPosition({
                    body.getPosition().x,
                    blockBounds.position.y + blockBounds.size.y
                });
                mario.setPosition({
                    body.getPosition().x,
                    blockBounds.position.y + blockBounds.size.y
                });

                hitHead = true;
            }

            velocity.y = 0.f;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(mario);
}

sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}

bool Player::didHitHead() const {
    return hitHead;
}

void Player::makeBig() {
    sf::Vector2f oldSize = body.getSize();
    body.setSize(sf::Vector2f(48.f, 96.f));
}

void Player::updateAnimation(float dt) {

    animTimer += dt;

    if (!isGrounded) {
        // jump frame (row 2)
        mario.setTextureRect(sf::IntRect({0, 64}, {32, 32}));
        return;
    }

    if (velocity.x != 0.f) {

        // running animation (row 1)
        if (animTimer > 0.1f) {
            frameX = (frameX + 1) % 3;
            animTimer = 0.f;
        }

        mario.setTextureRect(sf::IntRect({frameX * 32, 32}, {32, 32}));
    }
    else {
        // idle (row 0)
        mario.setTextureRect(sf::IntRect({0, 0}, {32, 32}));
    }
}
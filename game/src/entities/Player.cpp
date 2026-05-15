#include "entities/Player.h"
#include "core/InputManager.h"

Player::Player()
    : velocity(0.f, 0.f),
      moveSpeed(300.f),
      jumpStrength(-700.f),
      gravity(1500.f),
      isGrounded(false),
      hitHead(false) {

    body.setSize({50.f, 50.f});
    body.setFillColor(sf::Color::Red);
    body.setPosition({100.f, 300.f});
}

void Player::handleInput() {
    float movement = InputManager::getHorizontalMovement();
    velocity.x = movement * moveSpeed;

    if (InputManager::isJumpPressed() && isGrounded) {
        velocity.y = jumpStrength;
        isGrounded = false;
    }
}

void Player::update(float dt, const std::vector<sf::FloatRect>& solidBlocks) {
    hitHead = false;

    // Horizontal movement first
    body.move({velocity.x * dt, 0.f});

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.x > 0.f) {
                body.setPosition({
                    blockBounds.position.x - body.getSize().x,
                    body.getPosition().y
                });
            }

            if (velocity.x < 0.f) {
                body.setPosition({
                    blockBounds.position.x + blockBounds.size.x,
                    body.getPosition().y
                });
            }

            velocity.x = 0.f;
        }
    }

    // Screen boundaries
    if (body.getPosition().x < 0.f) {
        body.setPosition({0.f, body.getPosition().y});
    }

    if (body.getPosition().x + body.getSize().x > 1000.f) {
        body.setPosition({1000.f - body.getSize().x, body.getPosition().y});
    }

    // Vertical movement second
    velocity.y += gravity * dt;
    body.move({0.f, velocity.y * dt});

    isGrounded = false;

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.y > 0.f) {
                body.setPosition({
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

                hitHead = true;
            }

            velocity.y = 0.f;
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
}

sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}

bool Player::didHitHead() const {
    return hitHead;
}
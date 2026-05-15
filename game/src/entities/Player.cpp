#include "entities/Player.h"
#include "core/InputManager.h"

Player::Player()
    : velocity(0.f, 0.f),
      moveSpeed(300.f),
      jumpStrength(-700.f),
      gravity(1500.f),
      isGrounded(false) {

    body.setSize({50.f, 70.f});
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
    velocity.y += gravity * dt;

    body.move(velocity * dt);

    if (body.getPosition().x < 0.f) {
        body.setPosition({
            0.f,
            body.getPosition().y
        });
    }

    if (body.getPosition().x + body.getSize().x > 1000.f) {
        body.setPosition({
            1000.f - body.getSize().x,
            body.getPosition().y
        });
    }

    isGrounded = false;

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            sf::FloatRect playerBounds = body.getGlobalBounds();

            if (velocity.y > 0.f) {
                body.setPosition({
                    body.getPosition().x,
                    blockBounds.position.y - playerBounds.size.y
                });

                velocity.y = 0.f;
                isGrounded = true;
            }
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
}

sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}
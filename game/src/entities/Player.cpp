#include "entities/Player.h"

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
    velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        velocity.x = -moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        velocity.x = moveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && isGrounded) {
        velocity.y = jumpStrength;
        isGrounded = false;
    }
}

void Player::update(float dt) {
    velocity.y += gravity * dt;

    body.move(velocity * dt);

    // LEFT WALL
    if (body.getPosition().x < 0.f) {
        body.setPosition({
            0.f,
            body.getPosition().y
        });
    }

    // RIGHT WALL
    if (body.getPosition().x + body.getSize().x > 1000.f) {
        body.setPosition({
            1000.f - body.getSize().x,
            body.getPosition().y
        });
    }

    // FLOOR
    const float floorY = 500.f;

    if (body.getPosition().y + body.getSize().y >= floorY) {
        body.setPosition({
            body.getPosition().x,
            floorY - body.getSize().y
        });

        velocity.y = 0.f;
        isGrounded = true;
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
}

sf::FloatRect Player::getBounds() const {
    return body.getGlobalBounds();
}
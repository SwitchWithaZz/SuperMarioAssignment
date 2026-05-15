#include "../../include/entities/Mushroom.h"
#include <cstdlib>

Mushroom::Mushroom(float x, float y)
    : velocity(0.f, 0.f),
      moveSpeed(120.f),
      gravity(1500.f) {

    body.setSize(sf::Vector2f(50.f, 50.f));
    body.setFillColor(sf::Color::Magenta);
    body.setPosition(sf::Vector2f(x, y));

    if (std::rand() % 2 == 0) {
        velocity.x = -moveSpeed;
    }
    else {
        velocity.x = moveSpeed;
    }
}

void Mushroom::update(float dt, const std::vector<sf::FloatRect>& solidBlocks) {

    body.move(sf::Vector2f(velocity.x * dt, 0.f));

    if (body.getPosition().x < 0.f) {
        body.setPosition(sf::Vector2f(
            0.f,
            body.getPosition().y
        ));

        velocity.x = moveSpeed;
    }

    if (body.getPosition().x + body.getSize().x > 3100.f) {
        body.setPosition(sf::Vector2f(
            3100.f - body.getSize().x,
            body.getPosition().y
        ));

        velocity.x = -moveSpeed;
    }

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.x > 0.f) {
                body.setPosition(sf::Vector2f(
                    blockBounds.position.x - body.getSize().x,
                    body.getPosition().y
                ));
            }
            else if (velocity.x < 0.f) {
                body.setPosition(sf::Vector2f(
                    blockBounds.position.x + blockBounds.size.x,
                    body.getPosition().y
                ));
            }

            velocity.x = -velocity.x;
        }
    }

    velocity.y += gravity * dt;
    body.move(sf::Vector2f(0.f, velocity.y * dt));

    for (const auto& blockBounds : solidBlocks) {
        auto intersection = body.getGlobalBounds().findIntersection(blockBounds);

        if (intersection.has_value()) {
            if (velocity.y > 0.f) {
                body.setPosition(sf::Vector2f(
                    body.getPosition().x,
                    blockBounds.position.y - body.getSize().y
                ));
            }
            else if (velocity.y < 0.f) {
                body.setPosition(sf::Vector2f(
                    body.getPosition().x,
                    blockBounds.position.y + blockBounds.size.y
                ));
            }

            velocity.y = 0.f;
        }
    }
}

void Mushroom::draw(sf::RenderWindow& window) {
    window.draw(body);
}

sf::FloatRect Mushroom::getBounds() const {
    return body.getGlobalBounds();
}
#include "../../include/entities/Coin.h"

Coin::Coin(float x, float y) {

    shape.setSize(sf::Vector2f(50.f, 50.f));

    shape.setFillColor(sf::Color::Yellow);

    shape.setPosition(sf::Vector2f(x, y));
}

void Coin::draw(sf::RenderWindow& window) {

    if (!collected) {
        window.draw(shape);
    }
}

sf::FloatRect Coin::getBounds() const {
    return shape.getGlobalBounds();
}

bool Coin::isCollected() const {
    return collected;
}

void Coin::collect() {
    collected = true;
}
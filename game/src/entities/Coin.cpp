#include "../../include/entities/Coin.h"

#include <iostream>

Coin::Coin(float x, float y) {
    static sf::Texture coinTexture;
    static bool textureLoaded = false;

    if (!textureLoaded) {
        if (!coinTexture.loadFromFile("../assets/textures/Blocks/SMB_Sprite_Coin.png")) {
            std::cout << "Failed to load coin texture\n";
        }

        textureLoaded = true;
    }

    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setTexture(&coinTexture);
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
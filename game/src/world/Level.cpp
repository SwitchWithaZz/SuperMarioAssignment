#include "../../include/world/Level.hpp"

#include <fstream>
#include <iostream>

Level::Level() {
}

void Level::loadFromFile(const std::string& path) {

    map.clear();

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Failed to open level file\n";
        return;
    }

    std::string line;

    while (std::getline(file, line)) {
        map.push_back(line);
    }

    file.close();
}

void Level::draw(sf::RenderWindow& window) {

    sf::RectangleShape tile(
        sf::Vector2f(
            static_cast<float>(tileSize),
            static_cast<float>(tileSize)
        )
    );

    for (int row = 0; row < map.size(); row++) {

        for (int col = 0; col < map[row].size(); col++) {

            char currentTile = map[row][col];

            if (currentTile == '#') {

                tile.setPosition(
                    sf::Vector2f(
                        static_cast<float>(col * tileSize),
                        static_cast<float>(row * tileSize)
                    )
                );

                tile.setFillColor(sf::Color::Green);

                window.draw(tile);
            }
        }
    }
}
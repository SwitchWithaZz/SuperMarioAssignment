#include "../../include/world/Level.h"

#include <fstream>
#include <iostream>

Level::Level() {}

void Level::loadFromFile(const std::string& path) {

    map.clear();
    coins.clear();

    std::ifstream file(path);

    if (!file.is_open()) {
        std::cout << "Failed to open level file\n";
        return;
    }

    std::string line;
    int row = 0;

    while (std::getline(file, line)) {

        map.push_back(line);

        for (int col = 0; col < line.size(); col++) {

            char tile = line[col];

            if (tile == 'C') {
                coins.emplace_back(
                    col * tileSize + 6.f,
                    row * tileSize + 6.f
                );
            }
        }

        row++;
    }

    file.close();
}

void Level::draw(sf::RenderWindow& window) {

    sf::RectangleShape tile(
        sf::Vector2f((float)tileSize, (float)tileSize)
    );

    for (int row = 0; row < map.size(); row++) {

        for (int col = 0; col < map[row].size(); col++) {

            char tileChar = map[row][col];

            if (tileChar == '#') {
                tile.setFillColor(sf::Color::Green);
            }
            else if (tileChar == 'B') {
                tile.setFillColor(sf::Color(139, 69, 19)); // brown
            }
            else if (tileChar == '?') {
                tile.setFillColor(sf::Color::Yellow);
            }
            else {
                continue;
            }

            tile.setPosition(
                sf::Vector2f(
                    col * tileSize,
                    row * tileSize
                )
            );

            window.draw(tile);
        }
    }

    for (Coin& coin : coins) {
        coin.draw(window);
    }
}

std::vector<sf::FloatRect> Level::getSolidBlocks() const {

    std::vector<sf::FloatRect> solids;

    for (int row = 0; row < map.size(); row++) {

        for (int col = 0; col < map[row].size(); col++) {

            char tile = map[row][col];

            if (tile == '#' || tile == 'B' || tile == '?') {

                solids.emplace_back(
                    sf::Vector2f(col * tileSize, row * tileSize),
                    sf::Vector2f(tileSize, tileSize)
                );
            }
        }
    }

    return solids;
}

std::vector<Coin>& Level::getCoins() {
    return coins;
}
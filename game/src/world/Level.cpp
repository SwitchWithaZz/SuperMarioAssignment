#include "../../include/world/Level.h"

#include <fstream>
#include <iostream>

Level::Level() {
    loadFromFile("../assets/levels/level1.txt");
}

void Level::loadFromFile(const std::string& path) {

    map.clear();

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

            if (line[col] == 'C') {

                coins.emplace_back(
                    static_cast<float>(col * tileSize),
                    static_cast<float>(row * tileSize)
                );
            }
        }

        row++;
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

            if (currentTile == '#' || currentTile == 'B' || currentTile == '?') {

                if (currentTile == '#') {
                    tile.setSize(sf::Vector2f(50.f, 70.f));
                }
                else {
                    tile.setSize(sf::Vector2f(
                        static_cast<float>(tileSize),
                        static_cast<float>(tileSize)
                    ));
                }

                tile.setPosition(
                    sf::Vector2f(
                        static_cast<float>(col * tileSize),
                        static_cast<float>(row * tileSize)
                    )
                );

                if (currentTile == '#') {
                    tile.setFillColor(sf::Color(0, 168, 0));
                }
                else if (currentTile == 'B') {
                    tile.setFillColor(sf::Color(200, 76, 12));
                }
                else if (currentTile == '?') {
                    tile.setFillColor(sf::Color(252, 152, 56));
                }

                window.draw(tile);
            }
        }
    }

    for (Coin& coin : coins) {
        coin.draw(window);
    }
}

std::vector<sf::FloatRect> Level::getSolidBlocks() const {

    std::vector<sf::FloatRect> solidBlocks;

    for (int row = 0; row < map.size(); row++) {

        for (int col = 0; col < map[row].size(); col++) {

            char currentTile = map[row][col];

            if (currentTile == '#' || currentTile == 'B' || currentTile == '?') {

                sf::Vector2f blockSize(
                    static_cast<float>(tileSize),
                    static_cast<float>(tileSize)
                );

                if (currentTile == '#') {
                    blockSize = sf::Vector2f(50.f, 70.f);
                }

                solidBlocks.push_back(
                    sf::FloatRect(
                        sf::Vector2f(
                            static_cast<float>(col * tileSize),
                            static_cast<float>(row * tileSize)
                        ),
                        blockSize
                    )
                );
            }
        }
    }

    return solidBlocks;
}

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

void Level::update(float dt) {
    std::vector<sf::FloatRect> solidBlocks = getSolidBlocks();

    for (Mushroom& mushroom : mushrooms) {
        mushroom.update(dt, solidBlocks);
    }
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

            // ... existing code ...

            char currentTile = map[row][col];

            if (currentTile == '#' || currentTile == 'B' || currentTile == '?' || currentTile == 'U') {

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
                else if (currentTile == 'U') {
                    tile.setFillColor(sf::Color(180, 76, 12));
                }

                window.draw(tile);
            }
        }
    }

    for (Coin& coin : coins) {
        coin.draw(window);
    }

    for (Mushroom& mushroom : mushrooms) {
        mushroom.draw(window);
    }
}

std::vector<sf::FloatRect> Level::getSolidBlocks() const {

    std::vector<sf::FloatRect> solidBlocks;

    for (int row = 0; row < map.size(); row++) {

        for (int col = 0; col < map[row].size(); col++) {

            char currentTile = map[row][col];

            if (currentTile == '#' || currentTile == 'B' || currentTile == '?' || currentTile == 'U') {

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

void Level::hitBlockAbove(const sf::FloatRect& playerBounds) {

    sf::FloatRect headCheckArea(
        sf::Vector2f(
            playerBounds.position.x,
            playerBounds.position.y - 10.f
        ),
        sf::Vector2f(
            playerBounds.size.x,
            20.f
        )
    );

    for (int row = 0; row < map.size(); row++) {

        for (int col = 0; col < map[row].size(); col++) {

            if (map[row][col] == 'B' || map[row][col] == '?') {

                sf::FloatRect blockBounds(
                    sf::Vector2f(
                        static_cast<float>(col * tileSize),
                        static_cast<float>(row * tileSize)
                    ),
                    sf::Vector2f(
                        static_cast<float>(tileSize),
                        static_cast<float>(tileSize)
                    )
                );

                if (headCheckArea.findIntersection(blockBounds).has_value()) {

                    if (map[row][col] == 'B') {
                        map[row][col] = '.';
                    }
                    else if (map[row][col] == '?') {
                        mushrooms.emplace_back(
                            static_cast<float>(col * tileSize),
                            static_cast<float>((row - 1) * tileSize)
                        );

                        map[row][col] = 'U';
                    }

                    return;
                }
            }
        }
    }
}

std::vector<Coin>& Level::getCoins() {
    return coins;
}
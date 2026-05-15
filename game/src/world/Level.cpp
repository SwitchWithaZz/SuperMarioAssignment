#include "../../include/world/Level.h"

#include <fstream>
#include <iostream>

Level::Level() {
    loadTexture(groundTexture, "../assets/textures/Blocks/SMB_Ground.png");
    loadTexture(brickTexture, "../assets/textures/Blocks/SMB_Brick_Block_Sprite.png");
    loadTexture(questionBlockTexture, "../assets/textures/Blocks/SMB_Qblock.png");
    loadTexture(emptyBlockTexture, "../assets/textures/Blocks/SMB1_Empty_Block.png");

    loadFromFile("../assets/levels/level1.txt");
}

void Level::loadTexture(sf::Texture& texture, const std::string& path) {
    if (!texture.loadFromFile(path)) {
        std::cout << "Failed to load texture: " << path << "\n";
    }
}

void Level::loadFromFile(const std::string& path) {

    map.clear();
    coins.clear();
    mushrooms.clear();

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

            char currentTile = map[row][col];

            if (currentTile == '#' ||
                currentTile == 'B' ||
                currentTile == '?' ||
                currentTile == '!' ||
                currentTile == 'U' ||
                currentTile == 'F') {

                tile.setSize(sf::Vector2f(
                    static_cast<float>(tileSize),
                    static_cast<float>(tileSize)
                ));

                tile.setPosition(
                    sf::Vector2f(
                        static_cast<float>(col * tileSize),
                        static_cast<float>(row * tileSize)
                    )
                );

                if (currentTile == '#') {
                    tile.setSize(sf::Vector2f(50.f, 70.f));
                    tile.setTexture(&groundTexture);
                    window.draw(tile);
                }
                else if (currentTile == 'B') {
                    tile.setTexture(&brickTexture);
                    window.draw(tile);
                }
                else if (currentTile == '?' || currentTile == '!') {
                    tile.setTexture(&questionBlockTexture);
                    window.draw(tile);
                }
                else if (currentTile == 'U') {
                    tile.setTexture(&emptyBlockTexture);
                    window.draw(tile);
                }
                else if (currentTile == 'F') {
                    tile.setTexture(nullptr);

                    sf::RectangleShape pole(
                        sf::Vector2f(10.f, 150.f)
                    );

                    pole.setFillColor(sf::Color::White);
                    pole.setPosition(sf::Vector2f(
                        static_cast<float>(col * tileSize + 20),
                        static_cast<float>(row * tileSize - 100)
                    ));

                    sf::RectangleShape flag(
                        sf::Vector2f(60.f, 40.f)
                    );

                    flag.setFillColor(sf::Color::Red);
                    flag.setPosition(sf::Vector2f(
                        static_cast<float>(col * tileSize + 30),
                        static_cast<float>(row * tileSize - 100)
                    ));

                    window.draw(pole);
                    window.draw(flag);
                }

                tile.setTexture(nullptr);
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

            if (currentTile == '#' ||
                currentTile == 'B' ||
                currentTile == '?' ||
                currentTile == '!' ||
                currentTile == 'U') {

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

std::vector<sf::FloatRect> Level::getFlagBlocks() const {

    std::vector<sf::FloatRect> flagBlocks;

    for (int row = 0; row < map.size(); row++) {

        for (int col = 0; col < map[row].size(); col++) {

            if (map[row][col] == 'F') {

                flagBlocks.push_back(
                    sf::FloatRect(
                        sf::Vector2f(
                            static_cast<float>(col * tileSize),
                            static_cast<float>(row * tileSize - 100)
                        ),
                        sf::Vector2f(
                            90.f,
                            150.f
                        )
                    )
                );
            }
        }
    }

    return flagBlocks;
}

bool Level::hitBlockAbove(const sf::FloatRect& playerBounds) {

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

            if (map[row][col] == 'B' ||
                map[row][col] == '?' ||
                map[row][col] == '!') {

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
                    else if (map[row][col] == '!') {
                        coins.emplace_back(
                            static_cast<float>(col * tileSize),
                            static_cast<float>((row - 1) * tileSize)
                        );

                        map[row][col] = 'U';
                    }

                    return true;
                }
            }
        }
    }

    return false;
}

std::vector<Coin>& Level::getCoins() {
    return coins;
}

std::vector<Mushroom>& Level::getMushrooms() {
    return mushrooms;
}
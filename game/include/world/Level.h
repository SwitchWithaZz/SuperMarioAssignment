#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "../entities/Coin.h"
#include "../entities/Mushroom.h"

const sf::Texture groundTexture("../assets/textures/Blocks/SMB_ground.png");
inline sf::Sprite ground(groundTexture);

const sf::Texture brickTexture("../assets/textures/Blocks/SMB_Brick_block_Sprite.png");
inline sf::Sprite brick(brickTexture);

const sf::Texture qBTexture("../assets/textures/Blocks/SMB_Qblock.png");
inline sf::Sprite qB(qBTexture);

const sf::Texture emptyBrickTexture("../assets/textures/Blocks/SMB1_Empty_block.png");
inline sf::Sprite emptyBrick(emptyBrickTexture);

const sf::Texture coinTexture("../assets/textures/Blocks/SMB_Sprite_Coin.png");
inline sf::Sprite coin(coinTexture);

class Level {
private:
    std::vector<std::string> map;

    std::vector<Coin> coins;
    std::vector<Mushroom> mushrooms;

    sf::Texture groundTexture;
    sf::Texture brickTexture;
    sf::Texture questionBlockTexture;
    sf::Texture emptyBlockTexture;

    const int tileSize = 50;

    void loadTexture(sf::Texture& texture, const std::string& path);

public:
    Level();

    void loadFromFile(const std::string& path);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    std::vector<sf::FloatRect> getSolidBlocks() const;
    std::vector<sf::FloatRect> getFlagBlocks() const;

    bool hitBlockAbove(const sf::FloatRect& playerBounds);

    std::vector<Coin>& getCoins();
    std::vector<Mushroom>& getMushrooms();
};
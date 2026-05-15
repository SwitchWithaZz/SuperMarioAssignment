#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "entities/Player.h"
#include "world/Level.h"

class Game {
private:
    sf::RenderWindow window;
    sf::View camera;

    Player player;
    Level level;

    sf::Font font;
    sf::Text coinText;
    sf::Text victoryText;
    sf::Text finalScoreText;

    sf::SoundBuffer hitSoundBuffer;
    sf::Sound hitSound;

    sf::SoundBuffer pickupCoinSoundBuffer;
    sf::Sound pickupCoinSound;

    sf::SoundBuffer powerUpSoundBuffer;
    sf::Sound powerUpSound;

    sf::Music music;

    int coinCount;
    bool victory;

    void processEvents();
    void update(float dt);
    void render();

public:
    Game();

    void run();
};
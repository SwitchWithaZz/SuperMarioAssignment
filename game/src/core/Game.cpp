#include "core/Game.h"

#include <optional>
#include <iostream>
#include <string>

Game::Game()
    : window(sf::VideoMode({1500, 900}), "Mario Assignment"),
      camera(sf::FloatRect(
          sf::Vector2f(0.f, 0.f),
          sf::Vector2f(1500.f, 900.f)
      )),
      player(),
      level(),
      coinText(font),
      victoryText(font),
      finalScoreText(font),
      hitSound(hitSoundBuffer),
      pickupCoinSound(pickupCoinSoundBuffer),
      powerUpSound(powerUpSoundBuffer),
      coinCount(0),
      victory(false) {

    if (!font.openFromFile("../assets/fonts/Mario.ttf")) {
        std::cout << "Failed to load font\n";
    }

    if (!hitSoundBuffer.loadFromFile("../assets/audio/hit.wav")) {
        std::cout << "Failed to load hit sound\n";
    }

    if (!pickupCoinSoundBuffer.loadFromFile("../assets/audio/pickupCoin.wav")) {
        std::cout << "Failed to load pickup coin sound\n";
    }

    if (!powerUpSoundBuffer.loadFromFile("../assets/audio/powerUp.wav")) {
        std::cout << "Failed to load power up sound\n";
    }

    if (!music.openFromFile("../assets/audio/music.mp3")) {
        std::cout << "Failed to load music\n";
    }
    else {
        music.setLooping(true);
        music.setVolume(5.f);
        music.play();
    }

    coinText.setCharacterSize(28);
    coinText.setFillColor(sf::Color::White);
    coinText.setString("Coins: 0");
    coinText.setPosition(sf::Vector2f(1250.f, 20.f));

    victoryText.setCharacterSize(80);
    victoryText.setFillColor(sf::Color::Yellow);
    victoryText.setString("VICTORY");
    victoryText.setPosition(sf::Vector2f(500.f, 300.f));

    finalScoreText.setCharacterSize(40);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setString("Coins collected: 0");
    finalScoreText.setPosition(sf::Vector2f(500.f, 400.f));
}

void Game::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

void Game::update(float dt) {
    if (!victory) {
        player.handleInput();
        player.update(dt, level.getSolidBlocks());
        level.update(dt);

        if (player.didHitHead()) {
            bool specialBlockWasHit = level.hitBlockAbove(player.getBounds());

            if (specialBlockWasHit) {
                hitSound.play();
            }
        }

        for (Coin& coin : level.getCoins()) {
            if (!coin.isCollected() &&
                player.getBounds().findIntersection(coin.getBounds()).has_value()) {

                coin.collect();
                coinCount++;

                pickupCoinSound.play();

                coinText.setString("Coins: " + std::to_string(coinCount));
            }
        }

        for (Mushroom& mushroom : level.getMushrooms()) {
            if (!mushroom.isCollected() &&
                player.getBounds().findIntersection(mushroom.getBounds()).has_value()) {

                mushroom.collect();
                player.makeBig();

                powerUpSound.play();
            }
        }

        for (const sf::FloatRect& flagBounds : level.getFlagBlocks()) {
            if (player.getBounds().findIntersection(flagBounds).has_value()) {
                victory = true;
                finalScoreText.setString("Coins collected: " + std::to_string(coinCount));
            }
        }

        sf::FloatRect playerBounds = player.getBounds();

        float cameraX = playerBounds.position.x + playerBounds.size.x / 2.f;

        if (cameraX < 750.f) {
            cameraX = 750.f;
        }

        camera.setCenter(sf::Vector2f(cameraX, 450.f));
    }
}

void Game::render() {
    window.clear(sf::Color(92, 148, 252));

    window.setView(camera);

    level.draw(window);
    player.draw(window);

    window.setView(window.getDefaultView());

    window.draw(coinText);

    if (victory) {
        window.draw(victoryText);
        window.draw(finalScoreText);
    }

    window.display();
}
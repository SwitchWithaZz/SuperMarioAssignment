#include "core/Game.h"

#include <optional>
#include <iostream>
#include <string>

Game::Game()
    : window(sf::VideoMode({1500, 900}), "Mario Assignment"),
      player(),
      level(),
      coinText(font),
      coinCount(0) {

    if (!font.openFromFile("../assets/fonts/Mario.ttf")) {
        std::cout << "Failed to load font\n";
    }

    coinText.setCharacterSize(28);
    coinText.setFillColor(sf::Color::White);
    coinText.setString("Coins: 0");
    coinText.setPosition(sf::Vector2f(1250.f, 20.f));
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
    player.handleInput();
    player.update(dt, level.getSolidBlocks());

    if (player.didHitHead()) {
        level.breakBlockAbove(player.getBounds());
    }

    for (Coin& coin : level.getCoins()) {
        if (!coin.isCollected() &&
            player.getBounds().findIntersection(coin.getBounds()).has_value()) {

            coin.collect();
            coinCount++;

            coinText.setString("Coins: " + std::to_string(coinCount));
            }
    }
}

void Game::render() {
    window.clear(sf::Color(92, 148, 252));

    level.draw(window);
    player.draw(window);
    window.draw(coinText);

    window.display();
}
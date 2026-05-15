#include "core/Game.h"

#include <optional>

Game::Game()
    : window(sf::VideoMode({1000, 600}), "Mario Assignment"),
      player() {
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
    player.update(dt);
}

void Game::render() {
    window.clear(sf::Color::Black);

    player.draw(window);

    window.display();
}
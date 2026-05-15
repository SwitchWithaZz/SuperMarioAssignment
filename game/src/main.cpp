#include <SFML/Graphics.hpp>
#include <optional>
int main() {
    sf::RenderWindow window(sf::VideoMode({1000, 600}), "Mario Assignment");

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
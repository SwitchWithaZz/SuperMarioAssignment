#include "core/InputManager.h"

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <cmath>

float InputManager::getHorizontalMovement() {
    float movement = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        movement -= 1.f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        movement += 1.f;
    }

    if (sf::Joystick::isConnected(0)) {
        float axisX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);

        if (std::abs(axisX) > 20.f) {
            movement = axisX / 100.f;
        }
    }

    return movement;
}

bool InputManager::isJumpPressed() {
    bool keyboardJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    bool controllerJump = false;

    if (sf::Joystick::isConnected(0)) {
        controllerJump =
            sf::Joystick::isButtonPressed(0, 0) ||
            sf::Joystick::isButtonPressed(0, 1);
    }

    return keyboardJump || controllerJump;
}
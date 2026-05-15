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
        float leftStickX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
        float dpadX = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);

        if (std::abs(leftStickX) > 20.f) {
            movement = leftStickX / 100.f;
        }

        if (dpadX < -50.f) {
            movement = -1.f;
        }
        else if (dpadX > 50.f) {
            movement = 1.f;
        }
    }

    return movement;
}

bool InputManager::isJumpPressed() {
    bool keyboardJump = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    bool controllerJump = false;

    if (sf::Joystick::isConnected(0)) {
        bool button0 = sf::Joystick::isButtonPressed(0, 0);
        bool button1 = sf::Joystick::isButtonPressed(0, 1);
        bool button2 = sf::Joystick::isButtonPressed(0, 2);
        bool button3 = sf::Joystick::isButtonPressed(0, 3);

        float dpadY = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY);

        controllerJump =
            button0 ||
            button1 ||
            button2 ||
            button3 ||
            dpadY > 50.f;
    }

    return keyboardJump || controllerJump;
}
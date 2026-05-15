cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(game
        src/main.cpp
        src/core/Game.cpp
        src/entities/Player.cpp
        src/core/Game.cpp
        src/entities/Player.cpp
        include/world/Level.h
        src/world/Level.cpp
        include/entities/Block.h
        src/entities/block.cpp
        include/entities/Coin.h
        src/entities/coin.cpp
        include/entities/Mushroom.h
        src/entities/mushroom.cpp
        include/core/InputManager.h
        src/core/InputManager.cpp
)

target_include_directories(game PRIVATE include)

target_link_libraries(game PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)
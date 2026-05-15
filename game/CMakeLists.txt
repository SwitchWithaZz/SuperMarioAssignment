cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS Graphics Window System Audio REQUIRED)

add_executable(game
        src/main.cpp
)

target_include_directories(game PRIVATE include)

target_link_libraries(game PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio
)
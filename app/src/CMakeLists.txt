cmake_minimum_required(VERSION 3.1)

project(src LANGUAGES CXX)

add_library(src
        snake.cpp menu.cpp Game.cpp fruit.cpp functional.cpp)


target_link_libraries (src sfml-graphics sfml-window sfml-system)

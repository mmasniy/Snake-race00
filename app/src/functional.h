#pragma once

#include <SFML/Window.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "fruit.h"

sf::Vector2<int> RandomFruitGenerate(sf::Vector2<unsigned int> size_screen);

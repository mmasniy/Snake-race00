#include "fruit.h"
#include <iostream>
#define Fruit_SIZE 40

Fruit::Fruit(sf::RenderWindow *window, sf::Vector2<int> direction, long long score_Fruit) {
    score = score_Fruit;
    screen = window;
    color = sf::Color::Green;
    location = direction;
    food.setSize(sf::Vector2f(Fruit_SIZE, Fruit_SIZE));
    food.setPosition(direction.x, direction.y);
    food.setOutlineThickness(4);
    food.setFillColor(color);
}

sf::Vector2<int> Fruit::GetPositionFruit() {
    return location;
}

sf::RectangleShape& Fruit::GetFruitBody() {
    return food;
}

void Fruit::DrawFruit() {
    screen->draw(food);
}

void Fruit::SetPosition(sf::Vector2<int> direction) {
    location = direction;
    food.setPosition(sf::Vector2f(direction.x, direction.y));
}
long long Fruit::GetScore() {
    return score;
}


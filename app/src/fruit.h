#pragma once
#include "functional.h"


class Fruit {
    public:
    Fruit(sf::RenderWindow *window, sf::Vector2<int> direction, long long score_Fruit);
    sf::Vector2<int> GetPositionFruit();
    void DrawFruit();
    void SetPosition(sf::Vector2<int> direction);
    sf::RectangleShape& GetFruitBody();
    long long GetScore();

    private:
    long long score;
    sf::Color color;
    sf::Vector2<int> location;
    sf::RectangleShape food;
    sf::RenderWindow *screen;
};

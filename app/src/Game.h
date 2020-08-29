#pragma once
#include <random>
#include <list>
#include "snake.h"
#include "menu.h"

class Game {
    int seconds;
    double delay;
    void LoopIvent();
    void LoadResources();
    Snake snake;
    sf::RenderWindow *screen;
    Player& player;
    sf::Clock chrono;
    sf::Clock chrono_delete_snake;

    public:
    Game(sf::RenderWindow *w,
         sf::Color colorHead,
         sf::Color colorBody,
         Player &player_, Fruit& fruit);
    void Start();
    void MoveSnakeOnMap(sf::Event &event, sf::Vector2<int> &direction);
    bool WorkWithChrono(double& delay, sf::Clock& chrono, Snake& snake, sf::Vector2<int> direction);
    void Game_Chrono(sf::Clock& chrono_delete_snake, int& seconds, Snake& snake);
    void WorkWithKey(sf::Event &event, Snake& snake, sf::Vector2<int> direction, double& delay, Player& player);
};

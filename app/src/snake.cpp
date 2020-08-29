#include "snake.h"
#include <cstdlib>
#include <random>
#include <chrono>


Block::Block(sf::Vector2<int> new_pos, sf::Color color) {
    box.setSize(sf::Vector2f(BOX_SIZE, BOX_SIZE));
    box.setPosition(new_pos.x, new_pos.y);
    box.setOutlineThickness(4);
    position.x = new_pos.x;
    position.y = new_pos.y;
    box.setFillColor(color);
}

sf::RectangleShape Block::GetBox() {
    return box;
}

sf::Vector2<int> Block::GetPosition() {
    return position;
}

sf::Vector2<int> Snake::GetNextLocationForFood() {
    srand(time(0));
    bool food = true;
    int x = 0, y = 0;
    while (food) {
        x = 1 + rand() % (screen->getSize().x - 1);
        y =  1 + rand() % (screen->getSize().y - 1);
        food = true;
        for (auto& b : body) {
            if (b.GetPosition().x == x && b.GetPosition().y == y) {
                food = false;
            }
            if (food) {
                return {x, y};
            }
        }
    }
    return {20, 20};
}

Snake::Snake(sf::RenderWindow *window,
             sf::Color colorH,
             sf::Color colorB,
             Fruit &fruit_) : fruit(fruit_) {
    snake_length = 4;
    movementScale = 40;
    screen = window;
    colorBody = colorB;
    colorHead = colorH;

    int x = static_cast<int>(screen->getSize().x / 2);
    int y = static_cast<int>(screen->getSize().y / 2);
    for (int i = 0; i < 4; ++i) {
        if (i != 3) {
            body.push_back({{x + BOX_SIZE * (i + 1), y}, colorBody});
        } else {
            auto head = body.begin()->GetBox();
            head.setFillColor(colorB);
            sf::Vector2<int> position = {x + BOX_SIZE * (i + 1), y};
            body.push_front({position, colorH});
        }
    }
}

void Snake::DrawSnake() {
    for (auto &b : body) {
        screen->draw(b.GetBox());
    }
}

bool Snake::DiedSnake() {
    auto head = body.front();
    int count = count_if(body.begin() + 1, body.end(), [&head](Block &box) {
        return (box.GetPosition().x == head.GetPosition().x
            && box.GetPosition().y == head.GetPosition().y);
    });
    return !(count != 0 || (screen->getSize().x
        <= static_cast<unsigned int>(head.GetPosition().x)
        || head.GetPosition().x < 0 || screen->getSize().y
        <= static_cast<unsigned int>(head.GetPosition().y))
        || head.GetPosition().y < 0);
}

bool Snake::MoveSnake(sf::Vector2<int> direction) {
    auto head = body.front();
    if (DiedSnake()) {
        Block box({head.GetPosition().x + BOX_SIZE * direction.x,
                   head.GetPosition().y + BOX_SIZE * direction.y}, colorHead);
        body.push_front(box);
        body.pop_back();
        return false;
    }
    return true;
}

void Snake::AddBoxToTail(sf::Vector2<int> direction) {
    body.push_back({{direction.x - 5000, direction.y - 5000}, colorBody});
}

bool Snake::AteFood() {
    if (fruit.GetFruitBody().getGlobalBounds().intersects(body.front().GetBox().getGlobalBounds())) {
        AddBoxToTail(body.back().GetPosition());
        return true;
    }
    return false;
}
int Snake::GetSnakeSize() {
    return body.size();
}
void Snake::DeleteBox() {
    body.pop_back();
}
void Snake::DrawFruit(Player& player) {
    if (AteFood()) {
        player.score += GetFruit().GetScore();
        fruit.SetPosition(GetNextLocationForFood());
    }
    fruit.DrawFruit();
}
Fruit &Snake::GetFruit() {
    return fruit;
}

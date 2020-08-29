#include <iostream>

#include "src/functional.h"
#include "src/snake.h"
#include "src/Game.h"
#include "src/menu.h"
#include "src/fruit.h"
#include <string>

#define USAGE "usage: ./race00 [width] [height]"

void game_start (sf::RenderWindow* window, Player& player) {
    Fruit fruit(window, RandomFruitGenerate(window->getSize()), (1 + std::rand() % 50));
    fruit.SetPosition(RandomFruitGenerate(window->getSize()));
    fruit.DrawFruit();
    Game game
        (window, sf::Color::Magenta, sf::Color::Cyan, player, fruit);
    game.Start();
}

void show_Show_LeaderBoard(sf::RenderWindow* window, Menu& main) {
    sf::Event event;

    while (!window->pollEvent(event)) {
        window->clear();
        sf::Text text;
        sf::Font font;
        if (!font.loadFromFile("ArialBold.ttf")) { }
        text.setFont(font);
        text.setCharacterSize(30);
        sf::Color font_color(255, 140, 0, 255);
        text.setColor(font_color);

        auto it = main.score_table.rbegin();
        for (int i = 0; i < 10 && it != main.score_table.rend(); ++i, ++it) {
            std::string temp = std::to_string(it->first);
            text.setString(temp + " : " + it->second);
            text.setPosition(100 , 100 * i + 100);
            window->draw(text);
        }
        window->display();
        if (event.key.code == sf::Keyboard::Escape) {
            break;
        }
    }
}

int main(int argc, char** argv) {

    if (argc != 3) {
        std::cerr << USAGE << std::endl;
        return EXIT_FAILURE;
    }
    int width;
    int height;

    try {
       width = (std::stoi(argv[1])) % 4;
       height = (std::stoi(argv[2]))% 4;
       if ((width < 1024 || width > 2840) && (height < 1024 || height > 5840)) {
           width = 2840;
           height = 1800;
       }
    } catch (std::out_of_range& ex) {
        std::cerr << "error input parameters, use dedaults\n" ;
        width = 2840;
        height = 1800;
    };


    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "snake-line",
                                              sf::Style::Titlebar);

    Menu main(window, window->getSize().x, window->getSize().y);
    window->setTitle("SNAKE");
    window->setMouseCursorVisible(false);
    std::string new_player_name;

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        main.MoveUp();
                        break;
                    case sf::Keyboard::Down:
                        main.MoveDown();
                        break;

                    case sf::Keyboard::Return: //enter
                        switch (main.GetPressedItem()) {
                            case 0:
                                std::cout << "Play button has been pressed" << std::endl;
                                game_start(window, main.GetPlayer());
                                main.Add_player_score();
                                main.Save_result_to_file();
                            case 1:
                                std::cout << "LeaderBoard" << std::endl;
                                show_Show_LeaderBoard(window, main);

                            case 2:
                                std::cout << "Options" << std::endl;
                                break;
                            case 3:
                                window->close();
                        }
                        break;
                    default:
                        ;
                }
            }
            if (sf::Event::TextEntered) {
                while (window->pollEvent(event)) {
                    std::cout << "else if  sf::Event::TextEntered\n" << std::endl;
                    window->clear();
                    if (new_player_name.size() > 8 && event.text.unicode != '\b') {
                        break;
                    }
                    if (event.text.unicode == '\b' && new_player_name.size() > 1) {
                        if (event.text.unicode != '\n') {
                            std::cout << "event.text.unicod\n" << std::endl;
                            new_player_name.pop_back();
                            main.Set_player_name(new_player_name);
                        } else {
                            break;
                        }
                    } else {
                        new_player_name += event.text.unicode;
                        main.Set_player_name(new_player_name);

                    }

                }
            }
            if (sf::Event::Closed) {
                window->close();
                break;
            }
        }
        window->clear();
        main.start(*window);
        window->display();
    }
    delete window;
    return 0;
}


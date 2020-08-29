#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include <fstream>
#include "menu.h"

Menu ::Menu(sf::RenderWindow *_window, int _width, int _height) {
    window = _window;
    width =  _width;
    height = _height;

    if (!font.loadFromFile("ArialBold.ttf")) { }
    int font_size = std::min(width, height) / 25;

    sf::Color font_color(255, 140, 0, 255);
    menu[0].setFont(font);
    menu[0].setCharacterSize(font_size);

    menu[0].setColor(font_color);
    menu[0].setString("New game for " + current_player.name);
    menu[0].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    menu[1].setFont(font);
    menu[1].setCharacterSize(font_size);

    menu[1].setColor(sf::Color::White);
    menu[1].setString("LeaderBoard");
    menu[1].setPosition(sf::Vector2f(width / 2 - 100 , height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    menu[2].setFont(font);
    menu[2].setCharacterSize(font_size);

    menu[2].setColor(sf::Color::White);
    menu[2].setString("Options");
    menu[2].setPosition(sf::Vector2f(width / 2 - 100,  height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    menu[3].setFont(font);
    menu[3].setCharacterSize(font_size);

    menu[3].setColor(sf::Color::White);
    menu[3].setString("Exit");
    menu[3].setPosition(sf::Vector2f(width / 2 - 100, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));
    selectedItemIndex = 0;
    Update_result_from_file();
}

Menu::~Menu() { }


void Menu::MoveUp() {
    sf::Color color(255, 140, 0, 255);
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex--;
        menu[selectedItemIndex].setColor(color);
    }
}

void Menu::MoveDown() {
    sf::Color color(255, 140, 0, 255);
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex].setColor(sf::Color::White);
        selectedItemIndex++;
        menu[selectedItemIndex].setColor(color);
    }
}

void Menu::start(sf::RenderWindow &window) {
    sf::Texture menuBackground;  //background image
//    menuBackground.loadFromFile("unsplash.jpg");
//    sf::Sprite menu_bg(menuBackground);
//    window.draw(menu_bg);

    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        window.draw(menu[i]);
    }
}

int Menu :: GetPressedItem() {
    return selectedItemIndex;
}

void Menu::Set_player_name(const std::string& new_name) {

    if (new_name[0] == ' ') {
        current_player.name = "player";
    }
    current_player.name = new_name;
    menu[0].setString("New Game for " + current_player.name);

}
Player& Menu::GetPlayer() {
    return current_player;
}

void Menu::Add_player_score() {
    score_table.insert(make_pair(current_player.score, current_player.name));
    std::cout << "score_table = " << score_table.size() << std::endl;
    for (auto el : score_table) {
        std::cout << el.first << " : " << el.second << std::endl;
    }
}

void Menu::Save_result_to_file() {
    std::ofstream out;
    std::cout << "Save_result_to_file" << std::endl;

    out.open("score.txt");
    if (out.is_open()) {
        int i = 0;
        for (auto it = score_table.begin(); it != score_table.end() && i < 10; ++it, ++i) {
            out << it->first << "  " << it->second << std::endl;
        }
        std::cout << "save to file " << std::endl;
    }
    out.close();
}


int Menu::Get_width() {
    return width;
}

int Menu::Get_hight() {
    return height;
}

void Menu::Update_result_from_file() {
    std::cout << "function Update_result_from_file\n";

    std::ifstream in;
    in.open("score.txt");
    if (in.is_open()) {
        std::string line;
        while(getline(in, line)) {
            int score;
            std::string name;
            if (line.empty()) {
                continue;
            }
            in >> score >> name;
            score_table.insert(make_pair(score, name));
        }
    }
    in.close();

}

//delete *****************
//void Menu::Show_LeaderBoard() {
//    sf::Text text;
//    text.setString("Hello world");
//}

//void Menu::show_score_table() {
//    sf::Font font;
//
//    if (!font.loadFromFile("ArialBold.ttf")) {
//        //err
//    }
//    auto it = score_table.begin();
//    for (int i = 0; i < 10 && it != score_table.end(); ++i) {
//        LeaderBoard[i].setColor(sf::Color::White);
//        LeaderBoard[i].setFont(font);
//        LeaderBoard[i].setCharacterSize(25);
//        LeaderBoard[i].setString(it->first + " : " + it->second);
//        LeaderBoard[i].setPosition(sf::Vector2f(width + 100, height / (i + 1) * i));
//    }
//    for (int i = 0; i < 10; ++i) {
//        window->draw(LeaderBoard[i]);
//    }
//}


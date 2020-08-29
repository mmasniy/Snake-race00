#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#define MAX_NUMBER_OF_ITEMS 4

class Player {
public:
    Player() {
        score = 0;
        name = "player";
    }
    long long score;
    std::string name;
};

class Menu {
public:

    Menu(sf::RenderWindow *_window, int _width, int _height);
    ~Menu();
    void start(sf::RenderWindow &w);
    void MoveUp();
    void MoveDown();
    int GetPressedItem();
//    void Show_LeaderBoard();
    void Set_player_name(const std::string& new_name);
    Player& GetPlayer();
    void Add_player_score();
    void Save_result_to_file();
    void Update_result_from_file();
//    void show_score_table();
    int Get_width();
    int Get_hight();

    std::multimap<int, std::string> score_table;
private:
    sf::Text LeaderBoard[10];
    sf::Text menu[MAX_NUMBER_OF_ITEMS];
    int width;
    int height;
    Player current_player;
    sf::RenderWindow *window;
    sf::Font font;
    int selectedItemIndex;
};

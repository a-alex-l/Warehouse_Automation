#include "../include/game.h"
#include "../include/script_parser.h"

game::game(const std::string &file_name) {
    parse(file_name, map, robots, tasks, path_planner);
}

void game::start() {
    loop();
}

void game::loop() {
    show();

    if (!tasks.empty())
        loop();
}

void game::show() {
    static sf::Sprite board, robot;
    if (window == nullptr) { // ***** init of static sprites *****
        window = new sf::RenderWindow(
                sf::VideoMode(1 + 30 * map[0].size(),
                              1 + 30 * map.size()),
                "Warehouse");
        sf::Image image_board;
        image_board.create(1 + 30 * map[0].size(), 1 + 30 * map.size(), sf::Color(255, 255, 255));
        for (int i = 0; i < 1 + 30 * map[0].size(); i += 30)
            for (int j = 0; j < 1 + 30 * map.size(); j += 1)
                image_board.setPixel(i, j, sf::Color(100, 100, 100));
        for (int i = 0; i < 1 + 30 * map[0].size(); i += 1)
            for (int j = 0; j < 1 + 30 * map.size(); j += 30)
                image_board.setPixel(i, j, sf::Color(100, 100, 100));
        for (int i = 0; i < map[0].size(); i++)
            for (int j = 0; j < map.size(); j++)
                if (map[j][i])
                    for (int coord1 = 1 + 30 * i; coord1 < 30 * (i + 1); coord1++)
                        for (int coord2 = 1 + 30 * j; coord2 < 30 * (j + 1); coord2++)
                            image_board.setPixel(coord1, coord2, sf::Color(150, 150, 150));
        sf::Texture texture_board;
        texture_board.loadFromImage(image_board);
        board.setTexture(texture_board);
    }
    window->draw(board);
    window->display();
}



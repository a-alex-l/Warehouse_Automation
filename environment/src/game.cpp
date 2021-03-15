#include "../include/game.h"
#include "../include/script_parser.h"

game::game(const std::string &file_name) {
    parse(file_name, map, robots, tasks, path_planner);
}

void game::start() {
    loop();
}

void game::loop() {


    if (!tasks.empty())
        loop();
}

void game::show() {
    if (window == nullptr)
        window = new sf::RenderWindow(
                sf::VideoMode(1 + 30 * map[0].size(),
                              1 + 30 * map.size()),
                "Warehouse");

}



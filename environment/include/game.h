#ifndef WAREHOUSE_AUTOMATIZATION_GAME_H
#define WAREHOUSE_AUTOMATIZATION_GAME_H

#include "robot.h"
#include "task.h"
#include "../../competitors/include/path_finder.h"
#include <vector>
#include <string>

class game {
private:
    std::vector<std::vector<bool>> map;
    std::vector<robot> robots;
    std::vector<task> tasks;
    path_finder* path_planner;
    bool is_mode_show = true;
    sf::RenderWindow* window = nullptr;
    void show();
    void loop();

public:
    game(const std::string &file_name);
    void start();
};

#endif //WAREHOUSE_AUTOMATIZATION_GAME_H

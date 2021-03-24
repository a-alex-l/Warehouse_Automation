#ifndef WAREHOUSE_AUTOMATION_GAME_H
#define WAREHOUSE_AUTOMATION_GAME_H

#include "robot.h"
#include "task.h"
#include "../../competitors/include/path_finder.h"
#include <vector>
#include <list>
#include <string>

class game {
private:
    std::vector<std::vector<bool>> map;
    std::vector<robot> robots;
    std::list<task> tasks;
    path_finder *path_planner;
    bool is_mode_show = true;
    void loop();
    void move_robots();
    void remove_done_tasks();

public:
    game(const std::string &file_name, path_finder *path_maker);
    void start();
};

#endif //WAREHOUSE_AUTOMATION_GAME_H

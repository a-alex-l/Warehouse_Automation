#ifndef WAREHOUSE_AUTOMATION_GAME_H
#define WAREHOUSE_AUTOMATION_GAME_H

#include "robot.h"
#include "task.h"
#include "../../competitors/include/path_finder.h"
#include <vector>
#include <string>

class game {
private:
    std::vector<std::string> map; // '.' - nothing, '#' - wall, 's' - storage, '_' - unloading place.
    std::vector<robot> robots;
    std::vector<task> tasks;
    path_finder *path_planner = nullptr;
    std::string file_name;
    bool is_mode_show = true;
    void loop();
    void write_synopsis(int steps_count);
    void move_robots();
    void update_tasks();

public:
    game() = default;
    game(const std::string &file_name, path_finder *path_maker);
    void start();
};

#endif //WAREHOUSE_AUTOMATION_GAME_H

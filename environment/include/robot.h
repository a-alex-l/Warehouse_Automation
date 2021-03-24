#ifndef WAREHOUSE_AUTOMATION_ROBOT_H
#define WAREHOUSE_AUTOMATION_ROBOT_H

#include <SFML/Graphics.hpp>
#include "task.h"
#include <list>

struct robot {
    int coord1, coord2;
    std::list<task>::iterator job;
    bool is_carrying_cargo = false;
    int move_coord1 = 0, move_coord2 = 0;
};

#endif //WAREHOUSE_AUTOMATION_ROBOT_H

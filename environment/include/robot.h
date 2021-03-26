#ifndef WAREHOUSE_AUTOMATION_ROBOT_H
#define WAREHOUSE_AUTOMATION_ROBOT_H

#include <SFML/Graphics.hpp>
#include "task.h"

struct robot {
    int coord1, coord2;
    task *job = nullptr;
    int move_coord1 = 0, move_coord2 = 0;
};

#endif //WAREHOUSE_AUTOMATION_ROBOT_H

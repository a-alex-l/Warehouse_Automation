#ifndef WAREHOUSE_AUTOMATIZATION_TASK_H
#define WAREHOUSE_AUTOMATIZATION_TASK_H

#include <SFML/Graphics.hpp>

struct task {
    int from_coord1, from_coord2;
    int to_coord1, to_coord2;
    int robot_index;
};


#endif //WAREHOUSE_AUTOMATIZATION_TASK_H

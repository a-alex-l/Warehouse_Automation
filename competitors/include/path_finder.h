#ifndef WAREHOUSE_AUTOMATIZATION_PATH_FINDER_H
#define WAREHOUSE_AUTOMATIZATION_PATH_FINDER_H

#include "../../environment/include/robot.h"
#include <vector>

class path_finder {
public:
    virtual int get_move(int robot_index, std::vector<robot> &robots) = 0;
};

#endif //WAREHOUSE_AUTOMATIZATION_PATH_FINDER_H

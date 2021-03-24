#ifndef WAREHOUSE_AUTOMATION_PATH_FINDER_H
#define WAREHOUSE_AUTOMATION_PATH_FINDER_H

#include "../../environment/include/robot.h"
#include <vector>

class path_finder {  // accuracy = ???
public:

    // time = ???
    virtual void init_plans(const std::vector<robot> &robots,
                            const std::list<task> &tasks,
                            const std::vector<std::vector<bool>> &map) {};

    // time = ???
    virtual void get_moves(std::vector<robot> &robots,
                           const std::list<task> &tasks,
                           const std::vector<std::vector<bool>> &map) = 0;

    // time = ???
    virtual void get_tasks_to_robots(std::vector<robot> &robots,
                                     const std::list<task> &tasks,
                                     const std::vector<std::vector<bool>> &map) = 0;
};

#endif //WAREHOUSE_AUTOMATION_PATH_FINDER_H

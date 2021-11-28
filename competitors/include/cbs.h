#ifndef WAREHOUSE_AUTOMATION_CBS_H
#define WAREHOUSE_AUTOMATION_CBS_H

#include "path_finder.h"

class cbs_path_finder : public path_finder {

    // time = 0
    void init_plans(const std::vector<robot> &robots,
                    const std::vector<task> &tasks,
                    const std::vector<std::string> &map) override;

    // time = ???
    void get_moves(std::vector<robot> &robots,
                   const std::vector<task> &tasks,
                   const std::vector<std::string> &map) override;

    // time = ???
    void get_tasks_to_robots(std::vector<robot> &robots,
                             std::vector<task> &tasks,
                             const std::vector<std::string> &map) override;
};

#endif //WAREHOUSE_AUTOMATION_CBS_H

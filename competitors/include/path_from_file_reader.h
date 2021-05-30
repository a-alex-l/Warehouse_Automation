#ifndef WAREHOUSE_AUTOMATION_PATH_READER_H
#define WAREHOUSE_AUTOMATION_PATH_READER_H

#include "path_finder.h"
#include <queue>

class path_from_file_reader : public path_finder {
private:
    std::vector <std::deque<std::pair<int, int>>> path_plans;
    std::vector <std::deque<int>> task_plans;

public:

    path_from_file_reader(const std::string &file_name);

    // time = (2 ^ tasks.size) * (map.area ^ robots.size) * (5 ^ robots.size)
    void init_plans(const std::vector<robot> &robots,
                    const std::vector<task> &tasks,
                    const std::vector<std::vector<bool>> &map) override;

    // time = robots.size
    void get_moves(std::vector<robot> &robots,
                   const std::vector<task> &tasks,
                   const std::vector<std::vector<bool>> &map) override;

    // time = robots.size
    void get_tasks_to_robots(std::vector<robot> &robots,
                             std::vector<task> &tasks,
                             const std::vector<std::vector<bool>> &map) override;

};

#endif //WAREHOUSE_AUTOMATION_PATH_READER_H

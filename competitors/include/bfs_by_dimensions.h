#ifndef WAREHOUSE_AUTOMATION_BFS_BY_DIMENSIONS_H
#define WAREHOUSE_AUTOMATION_BFS_BY_DIMENSIONS_H

#include "path_finder.h"
#include <queue>

class bfs_path_finder : public path_finder {
private:
    std::vector<std::deque<std::pair<int, int>>> path_plans;
    std::vector<std::deque<int>> task_plans;

    void set_path_plans(const std::map<std::vector<int>, std::vector<int>> &parent,
                        std::vector<int> now,
                        const std::vector<robot> &robots,
                        const std::vector<task> &tasks);
    void set_task_plans(const std::map<std::vector<int>, std::vector<int>> &parent,
                        const std::vector<int> &finish,
                        const std::vector<robot> &robots,
                        const std::vector<task> &tasks);
public:

    // time = (2 ^ tasks.size) * (map.area ^ robots.size) * (5 ^ robots.size)
    void init_plans(const std::vector<robot> &robots,
                    const std::vector<task> &tasks,
                    const std::vector<std::string> &map) override;

    // time = robots.size
    void get_moves(std::vector<robot> &robots,
                   const std::vector<task> &tasks,
                   const std::vector<std::string> &map) override;

    // time = robots.size
    void get_tasks_to_robots(std::vector<robot> &robots,
                             std::vector<task> &tasks,
                             const std::vector<std::string> &map) override;
};

#endif //WAREHOUSE_AUTOMATION_BFS_BY_DIMENSIONS_H

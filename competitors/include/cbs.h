#ifndef WAREHOUSE_AUTOMATION_CBS_H
#define WAREHOUSE_AUTOMATION_CBS_H

#include "path_finder.h"
#include "base_mapf.h"
#include "cbs_node.h"

#include <memory>
#include <vector>
#include <set>

 
class cbs_path_finder : public path_finder {
private:
    std::set<CBSNode> nodes;
    std::vector<int> which_robots_task;
    int step = 0;

    CBSNode get_CBSNode(const std::set<Constraint> &constraints,
                        const std::set<EdgeConstraint> &edge_constraints,
                        const std::vector<robot> &robots,
                        const std::vector<task> &tasks,
                        const std::vector<std::string> &map);

public:
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

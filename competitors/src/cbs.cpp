#include "../include/cbs.h"
#include "../include/a_star.h"
#include "../../constants.h"


CBSNode cbs_path_finder::get_CBSNode(const std::set<Constraint> &constraints,
                                     const std::set<EdgeConstraint> &edge_constraints,
                                     const std::vector<robot> &robots,
                                     const std::vector<task> &tasks,
                                     const std::vector<std::string> &map) {
    std::vector<Path> paths(robots.size());
    unsigned cost = 0;
    for (int i = 0; i < robots.size(); i++) paths[i].locations.emplace_back(robots[i].coord1, robots[i].coord2);
    for (int i = 0; i < tasks.size(); i++) {
        Path path_from = a_star(which_robots_task[i], paths[which_robots_task[i]].locations.back(),
                                Location(tasks[i].from_coord1, tasks[i].from_coord2),
                                paths[i].locations.size() - 1, constraints, edge_constraints, map);
        paths[which_robots_task[i]].add(path_from);
        Path path_to = a_star(which_robots_task[i], Location(tasks[i].from_coord1, tasks[i].from_coord2),
                              Location(tasks[i].to_coord1, tasks[i].to_coord2),
                              paths[i].locations.size() - 1, constraints, edge_constraints, map);
        paths[which_robots_task[i]].add(path_to);
        cost = cost > paths[which_robots_task[i]].locations.size() - 1
                ? cost : paths[which_robots_task[i]].locations.size() - 1;
    }
    for (int i = 0; i < robots.size(); i++) {
        for (int k = int(cost) - paths[which_robots_task[i]].locations.size() + 1; k >= 0; k--) {
            Path path_from = a_star(i, paths[which_robots_task[i]].locations.back(),
                                    paths[which_robots_task[i]].locations.back(),
                                    paths[i].locations.size() - 1, constraints, edge_constraints, map);
            paths[i].add(path_from);
        }
    }
    return {constraints, edge_constraints, paths, cost};
}


static std::pair<std::vector<Constraint>, std::vector<EdgeConstraint>> validate_paths(std::vector<Path> paths) {
    size_t max_len = 0;
    for (auto & path : paths)
        max_len = std::max(max_len, path.locations.size());
    for (int i = 0; i < max_len; i++) {
        std::map<Location, std::vector<int>> locations;
        for (int j = 0; j < paths.size(); j++) {
            locations[paths[i].locations[j]].push_back(j);
        }
        if (locations.size() != paths.size()) {
            for (std::pair<Location, std::vector<int>> j : locations) {
                if (j.second.size() != 1) {
                    std::vector<Constraint> constraints;
                    for (int k : j.second)
                        constraints.emplace_back(k, j.first, i);
                    return {constraints, {}};
                }
            }
        }
    }
    for (int i = 1; i < max_len; i++) {
        std::map<std::pair<Location, Location>, std::vector<int>> locations;
        unsigned right_size = 0;
        for (int j = 0; j < paths.size(); j++) {
            if (paths[j].locations.size() < i) {
                right_size++;
                locations[paths[i].locations[j]].push_back(j);
            }
        }
        if (locations.size() != right_size) {
            for (std::pair<Location, std::vector<int>> j : locations) {
                if (j.second.size() != 1) {
                    std::vector<Constraint> constraints;
                    for (int k : j.second)
                        constraints.emplace_back(k, j.first, i);
                    return {constraints, {}};
                }
            }
        }
    }
    return {};
}


void cbs_path_finder::init_plans(const std::vector<robot> &robots,
                                 const std::vector<task> &tasks,
                                 const std::vector<std::string> &map) {
    if (which_robots_task.empty()) {
        which_robots_task.resize(tasks.size());
        for (unsigned i = 0; i < tasks.size(); i++)
            which_robots_task[i] = int(i % robots.size());
        nodes.insert(get_CBSNode(std::set<Constraint>(), std::set<EdgeConstraint>(), robots, tasks, map));
    }
    while (true) {
        CBSNode node = *nodes.begin();
        nodes.erase(nodes.begin());


    }
}

void cbs_path_finder::get_moves(std::vector<robot> &robots,
                                const std::vector<task> &tasks,
                                const std::vector<std::string> &map) {
    if (step % RECULC_PERIOD == 0)
        init_plans(robots, tasks, map);
    const CBSNode *best_node = &*nodes.begin();
    for (int i = 0; i < robots.size() ;i++) {
        if (!best_node->paths[i].empty()) {
            robots[i].move_coord1 = best_node->paths[i].locations[step + 1].x - best_node->paths[i].locations[step].x;
            robots[i].move_coord2 = best_node->paths[i].locations[step + 1].y - best_node->paths[i].locations[step].y;
        }
    }
    step++;
}

void cbs_path_finder::get_tasks_to_robots(std::vector<robot> &robots,
                                          std::vector<task> &tasks,
                                          const std::vector<std::string> &map) {

}
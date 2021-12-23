#include "../include/ca_star.h"
#include "../include/a_star.h"
#include "../../constants.h"

#include <iostream>
#include <stdexcept>


CBSNode ca_star_path_finder::get_CBSNode(const std::set<Constraint> &constraints,
                                     const std::set<EdgeConstraint> &edge_constraints,
                                     const std::vector<robot> &robots,
                                     const std::vector<task> &tasks,
                                     const std::vector<std::string> &map) {
    bool is_valid = true;
    std::vector<Path> paths(robots.size());
    unsigned cost = 0;
    for (int i = 0; i < robots.size(); i++) {
        paths[i].agent_id = i;
        paths[i].locations.emplace_back(robots[i].coord1, robots[i].coord2);
    }
    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].status == -1) {
            Path path_from = a_star(which_robots_task[i], paths[which_robots_task[i]].locations.back(),
                                    Location(tasks[i].from_coord1, tasks[i].from_coord2),
                                    paths[which_robots_task[i]].locations.size() - 1, constraints, edge_constraints,
                                    map);
            paths[which_robots_task[i]].add(path_from);
            if (path_from.locations.empty())
                is_valid = false;
        }
        if (tasks[i].status != 1) {
            Location start = Location(tasks[i].from_coord1, tasks[i].from_coord2);
            if (tasks[i].status == 0)
                start = Location(robots[which_robots_task[i]].coord1, robots[which_robots_task[i]].coord2);
            Path path_to = a_star(which_robots_task[i], start,
                                  Location(tasks[i].to_coord1, tasks[i].to_coord2),
                                  paths[which_robots_task[i]].locations.size() - 1, constraints, edge_constraints, map);
            paths[which_robots_task[i]].add(path_to);
            if (path_to.locations.empty())
                is_valid = false;
        }
        cost = cost > paths[which_robots_task[i]].locations.size() - 1
               ? cost : paths[which_robots_task[i]].locations.size() - 1;

    }
    for (int i = 0; i < robots.size(); i++) {
        while (cost >= paths[i].locations.size()) {
            Path path_avoid = avoiding_step(i, paths[i].locations.back(), paths[i].locations.size() - 1,
                                            constraints, edge_constraints, map);
            paths[i].add(path_avoid);
            if (path_avoid.locations.empty()) {
                is_valid = false;
                break;
            }
        }
        paths[i].locations.resize(cost + 1);
    }
    return {is_valid, constraints, edge_constraints, paths, cost};
}


static std::pair<std::vector<Constraint>, std::vector<EdgeConstraint>> validate_paths(
        std::vector<Path> paths, unsigned step, std::vector<int> priorities) {
    size_t max_len = std::min(step + HORIZON, unsigned(paths[0].locations.size()));
    for (auto & path : paths)
        max_len = std::max(max_len, path.locations.size());

    for (unsigned i = step; i < max_len; i++) {
        std::map<Location, std::vector<int>> locations;
        for (int j = 0; j < paths.size(); j++) {
            locations[paths[j].locations[i]].push_back(j);
        }
        if (locations.size() != paths.size()) {
            for (std::pair<Location, std::vector<int>> j : locations) {
                if (j.second.size() != 1) {
                    std::vector<Constraint> constraints;
                    int max_prior = -1;
                    int max_prior_agent;
                    for (auto k: j.second) {
                        if (priorities[k] > max_prior) {
                            max_prior = priorities[k];
                            max_prior_agent = k;
                        }
                    }
                    constraints.emplace_back(max_prior_agent, j.first, i);
                    return {constraints, {}};
                }
            }
        }
    }
    for (unsigned i = step + 1; i < max_len; i++) {
        std::map<std::pair<Location, Location>, std::vector<int>> locations;
        for (unsigned j = 0; j < paths.size(); j++) {
            Location first_location = paths[j].locations[i - 1];
            Location second_location = paths[j].locations[i];
            if (second_location < first_location) std::swap(first_location, second_location);
            locations[std::make_pair(first_location, second_location)].push_back(j);
        }
        if (locations.size() != paths.size()) {
            for (std::pair<std::pair<Location, Location>, std::vector<int>> j : locations) {
                if (j.second.size() != 1) {
                    std::vector<EdgeConstraint> edge_constraints;
                    int max_prior = -1;
                    int max_prior_agent;
                    for (auto k: j.second) {
                        if (priorities[k] > max_prior) {
                            max_prior = priorities[k];
                            max_prior_agent = k;
                        }
                    }
                    edge_constraints.emplace_back(
                            max_prior_agent,
                            paths[max_prior_agent].locations[i - 1],
                            paths[max_prior_agent].locations[i],
                            i);
                    return {{}, edge_constraints};
                }
            }
        }
    }
    return {};
}


void ca_star_path_finder::init_plans(const std::vector<robot> &robots,
                                 const std::vector<task> &tasks,
                                 const std::vector<std::string> &map) {
    if (which_robots_task.empty()) {
        which_robots_task.resize(tasks.size());
        task_plans.resize(robots.size());
        priorities.resize(robots.size());
        for (unsigned i = 0; i < tasks.size(); i++) {
            which_robots_task[i] = int(i % robots.size());
            task_plans[int(i % robots.size())].push_back(i);
            priorities[i] = i;
        }
    }
    nodes.clear();
    nodes.insert(get_CBSNode(std::set<Constraint>(), std::set<EdgeConstraint>(),
                             robots, tasks, map));
    while (!nodes.empty()) {
        CBSNode node = *nodes.begin();
        std::cout << node;
        auto constrs = validate_paths(node.paths, step, priorities);
        if (!constrs.first.empty()) {
            nodes.erase(nodes.begin());
            for (auto constr: constrs.first) {
                std::set<Constraint> new_constraints = node.constraints;
                new_constraints.insert(constr);
                CBSNode new_node = get_CBSNode(new_constraints, node.edge_constraints,
                                               robots, tasks, map);
                if (new_node.is_valid)
                    nodes.insert(new_node);
            }
        } else if (!constrs.second.empty()) {
            nodes.erase(nodes.begin());
            for (auto constr: constrs.second) {
                std::set<EdgeConstraint> new_edge_constraints = node.edge_constraints;
                new_edge_constraints.insert(constr);
                CBSNode new_node = get_CBSNode(node.constraints, new_edge_constraints,
                                               robots, tasks, map);
                if (new_node.is_valid)
                    nodes.insert(new_node);
            }
        } else break;
    }
    if (nodes.empty())
        throw std::runtime_error("Error: No solution found!");
}

void ca_star_path_finder::get_moves(std::vector<robot> &robots,
                                const std::vector<task> &tasks,
                                const std::vector<std::string> &map) {
    if (step % RECULC_PERIOD == RECULC_PERIOD - 1)
        init_plans(robots, tasks, map);
    const CBSNode *best_node = &*nodes.begin();
    for (int i = 0; i < robots.size(); i++) {
        if (!best_node->paths[i].empty()) {
            robots[i].move_coord1 = best_node->paths[i].locations[step + 1].x - best_node->paths[i].locations[step].x;
            robots[i].move_coord2 = best_node->paths[i].locations[step + 1].y - best_node->paths[i].locations[step].y;
        }
    }
    step++;
}

void ca_star_path_finder::get_tasks_to_robots(std::vector<robot> &robots,
                                          std::vector<task> &tasks,
                                          const std::vector<std::string> &map) {
    for (int i = 0; i < robots.size(); i++) {
        if (robots[i].job == nullptr && !task_plans[i].empty()) {
            if (!task_plans[i].empty()) {
                robots[i].job = &tasks[task_plans[i].front()];
                task_plans[i].pop_front();
            }
        }
    }
}

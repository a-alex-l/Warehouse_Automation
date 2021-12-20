#include "../include/single_agent_solver.h"


double SingleAgentSolver::compute_h_value(
        const BasicGraph& graph,
        const int current_goal_num,
        int goal_id,
        const std::vector<Location>& goals) const {
    double h = graph.heuristics.at(goals[goal_id])[current_goal_num];
    goal_id++;
    while (goal_id < (int) goals.size()) {
        h += graph.heuristics.at(
                goals[goal_id]
                )[
            goals[goal_id - 1]
                ];
        goal_id++;
    }
    return h;
}

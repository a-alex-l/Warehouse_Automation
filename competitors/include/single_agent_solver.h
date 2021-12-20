#include <cstdint>
#include "basic_graph.h"

class SingleAgentSolver {
    public:
        double suboptimal_bound;
        uint64_t num_expanded;
        uint64_t num_generated;

        double path_cost;
        double min_f_value;

        double compute_h_value(
                const BasicGraph& graph,
                const int current_goal_num,
                const int goal_id,
                const std::vector<Location>& goals) const;

        virtual Path run(
                const BasicGraph& graph,
                const State& start,
                const std::vector<Location> goals) = 0;

        SingleAgentSolver(): suboptimal_bound(1), num_expanded(0), num_generated(0), path_cost(0), min_f_value(0) {};
};

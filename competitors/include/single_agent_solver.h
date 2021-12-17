#include <cstdint>
#include "map.h"

class SingleAgentSolver {
    public:
        double suboptimal_bound;
        uint64_t num_expanded;
        uint64_t num_generated;

        double path_cost;
        double min_f_value;

        double compute_h_value(
                const Map& map,
                const State& start,
                const std::vector< std::pair <int, int> > goals) const;

        virtual Path run(
                const Map& map,
                const State& start,
                const std::vector< std::pair <int, int> > goals) = 0;

        SingleAgentSolver(): suboptimal_bound(1), num_expanded(0), num_generated(0), path_cost(0), min_f_value(0) {};
};

#include "single_agent_solver.h"

class MAPFSolver {
    public:
        const Map& map;
        std::vector<State> starts;
        std::vector< std::vector <std::pair <int, int> > > goals;
        int time_limit;

        std::vector<Path*> solution;
        std::vector<Path*> initial_paths;
        std::vector<Constraint> initial_constraints;
        
        SingleAgentSolver& path_planner;
        
        virtual bool run(
                const std::vector<State>& starts,
                const std::vector< std::vector< std::pair <int, int> > >& goals,
                int time_limit) = 0;

        MAPFSolver(const Map& map, SingleAgentSolver& path_planner);
        ~MAPFSolver();
};

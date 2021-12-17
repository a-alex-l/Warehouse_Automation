#ifndef WAREHOUSE_AUTOMATION_CBS_H
#define WAREHOUSE_AUTOMATION_CBS_H

#include <boost/heap/fibonacci_heap.hpp>
#include <boost/unordered_set.hpp>

#include "path_finder.h"
#include "base_mapf.h"
#include "cbs_node.h"

#include <memory>
#include <vector>

 
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


class CBS : public MAPFSolver {
    public:
        bool solution_found;
        double solution_cost;

        CBSNode* dummy_start;
        std::vector<Constraint> initial_constrains;

        bool run(
            const std::vector<State>& starts,
            const std::vector<task>& tasks,
            int time_limit
            );

        CBS(const Map& map, SingleAgentSolver& path_planner);
        ~CBS();

        void update_paths(CBSNode* node);
        void find_conflicts(int start_time, std::vector< std::shared_ptr <Conflict> >& conflicts) const;
    private:
        typedef boost::heap::fibonacci_heap< Node* > heap_open_t;
        heap_open_t open;
        boost::unordered_set<Node*> close;

        std::vector<Path*> paths;
        int number_of_agents;
        int time_limit;

        void push_node(CBSNode* node);
        void reinsert_node(CBSNode* node);
        CBSNode* pop_node();

        bool find_path(CBSNode* node, int agent_id);
        void resolve_conflict(const Conflict& conflict);
        bool add_child(CBSNode* child, CBSNode* parent);

        void find_conflicts();
        void choose_conflict();

        void get_solution();

        bool validate_solution() const;
        bool validate_path(const Path& path, const std::vector<Constraint>& constraints) const;
};

#endif //WAREHOUSE_AUTOMATION_CBS_H

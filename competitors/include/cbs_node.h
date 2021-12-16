#include "base_structures.h"

#include <memory>
#include <vector>


class CBSNode {
    public:
        CBSNode* parent;
        std::vector< Constraint > constraints;
        std::vector< std::shared_ptr<Conflict >> conflicts;
        std::vector<Path> paths;

        double g;
        double h;
        double f;
        double min_f;

        size_t depth;
        size_t window;

        uint64_t time_expanded;
        uint64_t time_generated;
        int num_of_collisions;

        CBSNode(): parent(nullptr), g(0), h(0), f(0), min_f(0), time_expanded(0), time_generated(0) {}
        CBSNode(CBSNode* parent);
        ~CBSNode() {};
};

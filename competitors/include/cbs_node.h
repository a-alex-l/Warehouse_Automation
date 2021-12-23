#include "base_structures.h"

#include <memory>
#include <utility>
#include <vector>
#include <set>


class CBSNode {
    public:
    std::set<Constraint> constraints;
    std::set<EdgeConstraint> edge_constraints;
    std::vector<Path> paths;  // all path must be the same len. If it turned out to be short add staying.
    unsigned cost = 0;        // doesn't equal paths[any] len

    CBSNode(std::set<Constraint> constraints, std::set<EdgeConstraint> edge_constraints,
                    std::vector<Path> paths, unsigned cost = 0):
            constraints(std::move(constraints)), edge_constraints(std::move(edge_constraints)),
            paths(std::move(paths)), cost(cost) {}
    ~CBSNode() = default;

    bool operator < (const CBSNode& other) const {  // for set
        return cost < other.cost;
    }
};

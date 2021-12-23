#include "base_structures.h"

#include <memory>
#include <utility>
#include <vector>
#include <set>


class CBSNode {
    public:
    bool is_valid = true;
    std::set<Constraint> constraints;
    std::set<EdgeConstraint> edge_constraints;
    std::vector<Path> paths;  // all path must be the same len. If it turned out to be short add staying.
    unsigned cost = 0;        // doesn't equal paths[any] len

    CBSNode(bool is_valid, std::set<Constraint> constraints, std::set<EdgeConstraint> edge_constraints,
                    std::vector<Path> paths, unsigned cost = 0): is_valid(is_valid),
            constraints(std::move(constraints)), edge_constraints(std::move(edge_constraints)),
            paths(std::move(paths)), cost(cost) {}
    ~CBSNode() = default;

    bool operator < (const CBSNode& other) const {  // for set
        return cost < other.cost || (cost == other.cost &&
                                     (constraints < other.constraints || (constraints == other.constraints &&
                                                                          edge_constraints < other.edge_constraints)));
    }

    friend std::ostream &operator<<(std::ostream &os, CBSNode const &node) {   //for debug
        os << "good? = " << node.is_valid << ", cost = " << node.cost << "\n";
        for (auto i : node.constraints)
            os << "(" << i.agent_id << " # " << i.location.x << ", " << i.location.y << " | " << i.timestemp << ") ";
        os << "\n";
        for (auto i : node.edge_constraints)
            os << "(" << i.agent_id << " # " << i.first_location.x << ", " << i.first_location.y << " | "
               << i.second_location.x << ", " << i.second_location.y << " | " << i.timestemp << ") ";
        os << "\n";
        for (auto i : node.paths) {
            for (int j = 0; j < i.locations.size(); j++)
                os << "(" << i.locations[j].x << ", " << i.locations[j].y << ") ";
            os << "\n";
        }
        return  os << "------------------\n";
    }
};

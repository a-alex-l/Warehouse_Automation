#pragma once

#include <vector>
#include <set>
#include <string>
#include <cmath>

#include "base_structures.h"
#include "node.h"

Path a_star(int agent_id, Location start, Location goal, unsigned init_cost,
            const std::set<Constraint> &constraints,
            const std::set<EdgeConstraint> &edge_constraints,
            const std::vector<std::string> &map);
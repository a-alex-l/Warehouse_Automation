#include <boost/unordered_map.hpp>

#include "base_structures.h"
#include "map.h"

#define WEIGHT_MAX INT_MAX/2


class BasicGraph {
public:
    Map& map;
    boost::unordered_map<Location, std::vector<double>> heuristics;

    boost::unordered_map<Location, double> compute_heuristics(Location root_location); // compute distances from all locations to the root location

    std::vector<State> get_neighbors(const State& state) const;

    int get_manhattan_distance(Location location1, Location location2) const;
};


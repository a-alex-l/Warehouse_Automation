#include "../include/basic_graph.h"


std::vector<State> BasicGraph::get_neighbors(const State& state) const {
    std::vector<State> neighbors;
	neighbors.push_back(State(state.location, state.timestamp + 1)); // wait
	for (Location location: map.get_neighbors(state.location)) {
		neighbors.push_back(State(location, state.timestamp + 1));
    }
    return neighbors;
}    

int BasicGraph::get_manhattan_distance(Location location1, Location location2) const {
	return std::abs(location1.x - location2.x) + std::abs(location1.y - location2.y);
}

#include <cmath>

#include "../include/map.h"


bool Map::in_bounds(Location location) {
    return 0 <= location.y && location.y < width 
        && 0 <= location.x && location.y < height;
}

bool Map::traversable(Location location) {
    return nodes[location.x][location.y] == 0;
}

std::vector<Location> Map::get_neighbors(Location location) {
    std::vector<Location> neighbors;
    for (int _i = -1; _i <= 1; _i += 2) {
        for (int _j = -1; _j <= 1; _j += 2) {
            int next_i = location.x + _i;
            int next_j = location.y + _j;
            Location next_location = Location(next_i, next_j);
            if (this->in_bounds(next_location) && this->traversable(next_location)) {
                neighbors.push_back(next_location);
            }
        }
    }
    return neighbors;
}

double Map::compute_cost(Location location1, Location location2) {
    if (std::abs(location1.x - location2.x) +
            std::abs(location1.y - location2.y) == 1) {
        return 1;
    } else {
		return -1;
    }
}

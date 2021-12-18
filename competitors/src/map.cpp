#include <cmath>

#include "../include/map.h"


bool Map::in_bounds(std::pair<int, int> location) {
    return 0 <= location.second && location.second < width 
        && 0 <= location.first && location.second < height;
}

bool Map::traversable(std::pair<int, int> location) {
    return nodes[location.first][location.second] == 0;
}

std::vector< std::pair<int, int> > Map::get_neighbors(std::pair<int, int> location) {
    std::vector< std::pair<int, int> > neighbors;
    for (int _i = -1; _i <= 1; _i += 2) {
        for (int _j = -1; _j <= 1; _j += 2) {
            int next_i = location.first + _i;
            int next_j = location.second + _j;
            std::pair<int, int> next_location = std::make_pair(next_i, next_j);
            if (this->in_bounds(next_location) && this->traversable(next_location)) {
                neighbors.push_back(std::make_pair(next_i, next_j));
            }
        }
    }
    return neighbors;
}

double Map::compute_cost(std::pair<int, int> location1, std::pair<int, int> location2) {
    if (std::abs(location1.first - location2.first) +
            std::abs(location1.second - location2.second) == 1) {
        return 1;
    } else {
        return std::sqrt(2);
    }
}

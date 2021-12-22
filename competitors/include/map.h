#include <vector>

#include "node.h"

class Map {
    public:
        int width;
        int height;
        std::vector< std::vector<Node> > nodes;

        bool in_bounds(Location location);
        bool traversable(Location location);

        std::vector<Location> get_neighbors(Location location);
        double compute_cost(Location location1, Location location2);
};

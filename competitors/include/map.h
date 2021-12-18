#include <vector>

#include "node.h"

class Map {
    public:
        int width;
        int height;
        std::vector< std::vector<Node> > nodes;

        bool in_bounds(std::pair<int, int> location);
        bool traversable(std::pair<int, int> location);

        std::vector< std::pair<int, int> > get_neighbors(std::pair<int, int> location);
        double compute_cost(std::pair<int, int> location1, std::pair<int, int> location2);
};

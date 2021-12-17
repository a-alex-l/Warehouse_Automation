#include <vector>

#include "node.h"

class Map {
    public:
        int width;
        int height;
        std::vector< std::vector<Node> > nodes;

        bool is_bounds(int i, int j);
        bool traversable(int i, int j);

        std::vector<Node> get_neighbors(int i, int j);
        double compute_cost(int i1, int j1, int i2, int j2);
};

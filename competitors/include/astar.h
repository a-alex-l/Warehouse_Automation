#include <boost/heap/fibonacci_heap.hpp>
#include <boost/unordered_set.hpp>

#include "map.h"


class AStar {
    public:
        Map* map;
        Node* start;
        Node* goal;

        typedef boost::heap::fibonacci_heap< Node* > heap_open_t;
        heap_open_t open;
        boost::unordered_set<Node*> close;

        void run();
};


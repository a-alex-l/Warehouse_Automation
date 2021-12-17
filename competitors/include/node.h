#include "base_structures.h"

#include <memory>
#include <vector>

class Node {
    public:
        Node* parent;

        int i;
        int j;
        double g;
        double h;
        double f;

        Node(int i, int j): parent(nullptr), i(i), j(j), g(0), h(0), f(0) {}
        Node(Node* parent, int i, int j, double g, double h): parent(parent), i(i), j(j), g(g), h(h), f(g+h) {}
        ~Node() {};

        bool operator < (const Node* other) const {
            return std::tie(this->f, this->h) < std::tie(other->f, other->h);
        }

        bool operator == (const Node* other) const {
            return std::tie(this->f, this->h) == std::tie(other->f, other->h);
        }

        struct compare_node {
            bool operator () (const Node* node1, const Node* node2) const {
                return node1->f >= node2->f;
            }
        };
};

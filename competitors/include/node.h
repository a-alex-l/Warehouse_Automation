#include "base_structures.h"

#include <memory>
#include <vector>

struct Node {
    Node* parent;
    Location location;
    int g;     // only +-1 by step
    double h;
    double f;

    Node(Location location): parent(nullptr), location(location), g(0), h(0), f(0) {}
    Node(Node* parent, Location location, double g, double h): parent(parent), location(location), g(g), h(h), f(g+h) {}
    ~Node() {};

    bool operator < (const Node* other) const {
        return std::tie(this->f, this->h) < std::tie(other->f, other->h);
    }

    bool operator == (const Node* other) const {
        return std::tie(this->f, this->h) == std::tie(other->f, other->h);
    }
};

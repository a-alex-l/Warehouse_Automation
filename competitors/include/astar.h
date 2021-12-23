#include <vector>
#include <set>
#include <string>
#include <map>
#include <list>
#include <cmath>

#include "base_structures.h"
#include "node.h"


struct NodePtrOpenComparator {
    bool operator()(const Node* l_node, const Node* r_node) const  {
        return l_node->f < r_node->f ||
               (l_node->f == r_node->f &&
                (l_node->location.x < r_node->location.x ||
                 (l_node->location.x == r_node->location.x && l_node->location.y < r_node->location.y)));
    }
};


struct Open {
    std::map<Location, Node*> ij_finder;
    std::set<Node*, NodePtrOpenComparator> f_sorting;

    void add_node(Node n) {
        if (ij_finder.find(n.location) == ij_finder.end() || ij_finder[n.location]->g > n.g) {
            Node* new_n = new Node(n);
            f_sorting.insert(new_n);
            ij_finder[n.location] = new_n;
        }
    }

    ~Open() {
        for (auto i : f_sorting)
            delete i;
    }

    bool empty() {
        return f_sorting.empty();
    }

    Node* get_best_f_node() {
        Node *best_node = *f_sorting.begin();
        ij_finder.erase(best_node->location);
        f_sorting.erase(best_node);
        return best_node;
    }
};


struct NodePtrClosedComparator {
    bool operator()(const Node* l_node, const Node* r_node) const  {
        return l_node->location.x < r_node->location.x ||
                 (l_node->location.x == r_node->location.x && l_node->location.y < r_node->location.y);
    }
};


struct Closed {
    std::set<Node *, NodePtrClosedComparator> storage;

    void insert(Node *node) {
        storage.insert(node);
    }

    bool has(Node *node) {
        return storage.find(node) != storage.end();
    }

    ~Closed() {
        for (auto i: storage)
            delete i;
    }
};


double get_diagonal_dist(Location start, Location goal) {
    int minn = std::min(abs(start.x - goal.x), abs(start.y - goal.y));
    int maxx = std::max(abs(start.x - goal.x), abs(start.y - goal.y));
    return minn + (maxx - minn) * std::sqrt(2.0);
}


std::vector<Node> get_neighbours(int agent_id, Node* node, Location goal,
                                 std::set<Constraint> constraints,
                                 std::set<Conflict> conflicts,
                                 const std::vector<std::string> &map) {
    std::vector<Node> nodes = {*node, *node, *node, *node};
    nodes[0].location.x++,nodes[1].location.x--,nodes[2].location.y++,nodes[3].location.y--;
    nodes[0].g++,nodes[1].g++,nodes[2].g++,nodes[3].g++;
    std::vector<bool> good(4, True);
    for (int i = 0; i < 4; i++) {
        good[i] = good[i] && map[nodes[i].location.x][nodes[i].location.y] != '#';
        good[i] = good[i] && (map[nodes[i].location.x][nodes[i].location.y] != 's' ||
                              map[node->location.x][node->location.y] != 's');
        good[i] = good[i] && (constraints.find(Constraint(agent_id, nodes[i].location, nodes[i].g)) == constraints.end());
        good[i] = good[i] && (conflicts.find(Conflict(agent_id, node->location, nodes[i].location, nodes[i].g)) == conflicts.end());
    }
    std::vector<Node> ans;
    for (int i = 0; i< 4; i++)
        if (good[i]) {
            nodes[i].h = get_diagonal_dist(nodes[i].location, goal);
            ans.push_back(nodes[i]);
        }
    return ans;
}


std::pair<Node*, Closed> a_star(int agent_id,
                                const std::vector<std::string> &map,
                                Location start, Location goal,
                                std::set<Conflict> conflicts,
                                std::set<Constraint> constraints) {
    Closed closed;
    Open open;
    open.add_node(Node(nullptr, start, 0, get_diagonal_dist(start, goal)));
    while (!open.empty()) {
        Node *node = open.get_best_f_node();
        closed.insert(node);
        if (node->location == goal)
            return std::make_pair(node, closed);
        std::vector<Node> neighbours = get_neighbours(agent_id, node, goal, constraints, conflicts, map);
        if (!neighbours.empty())
            for (Node &i : neighbours)
                if (!closed.has(&i))
                    open.add_node(i);
    }
    return std::make_pair(nullptr, closed);
};


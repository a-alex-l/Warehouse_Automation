#include <map>
#include <cmath>
#include <algorithm>

#include "a_star.h"


struct NodePtrOpenComparator {
    bool operator()(const Node* l_node, const Node* r_node) const  {
        return l_node->f < r_node->f ||
               (l_node->f == r_node->f &&
                (l_node->location.x < r_node->location.x ||
                 (l_node->location.x == r_node->location.x &&
                  (l_node->location.y < r_node->location.y ||
                   (l_node->location.y == r_node->location.y && l_node->g < r_node->g)))));
    }
};


struct Open {
    std::map<Location, Node*> ij_finder;
    std::set<Node*, NodePtrOpenComparator> f_sorting;

    void add_node(const Node &n) {
        if (ij_finder.find(n.location) == ij_finder.end() || ij_finder[n.location]->g > n.g) {
            Node* new_n = new Node(n);
            if (ij_finder.find(n.location) != ij_finder.end()) {
                f_sorting.erase(ij_finder[n.location]);
                delete ij_finder[n.location];
            }
            f_sorting.insert(new_n);
            ij_finder[n.location] = new_n;
        }
    }

    ~Open() {
        for (auto i : f_sorting)
            delete i;
    }

    [[nodiscard]] bool empty() const {
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
               (l_node->location.x == r_node->location.x &&
               (l_node->location.y < r_node->location.y ||
               (l_node->location.y == r_node->location.y && l_node->g < r_node->g)));
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


static unsigned get_h_dist(Location start, Location goal) {
    return abs(start.x - goal.x) + abs(start.y - goal.y);
}


static std::vector<Node> get_neighbours(int agent_id, Node* node, Location goal,
                                        const std::set<Constraint> &constraints,
                                        const std::set<EdgeConstraint> &edge_constraints,
                                        const std::vector<std::string> &map) {
    std::vector<Node> nodes = {*node, *node, *node, *node, *node};
    nodes[1].location.x++, nodes[2].location.x--, nodes[3].location.y++, nodes[4].location.y--;
    nodes[0].g++, nodes[1].g++, nodes[2].g++, nodes[3].g++, nodes[4].g++;
    std::vector<bool> good(5, true);
    for (int i = 0; i < 5; i++) {
        good[i] = good[i] && map[nodes[i].location.x][nodes[i].location.y] != '#';
        good[i] = good[i] && (map[nodes[i].location.x][nodes[i].location.y] != 's' ||
                              map[node->location.x][node->location.y] != 's');
        good[i] = good[i] && (constraints.find(Constraint(agent_id, nodes[i].location, nodes[i].g)) == constraints.end());
        good[i] = good[i] && (edge_constraints.find(
                EdgeConstraint(agent_id, node->location, nodes[i].location, nodes[i].g)) == edge_constraints.end());
    }
    std::vector<Node> ans;
    for (int i = 0; i < 5; i++)
        if (good[i]) {
            nodes[i].h = get_h_dist(nodes[i].location, goal);
            nodes[i].f = nodes[i].h + nodes[i].g;
            nodes[i].parent = node;
            ans.push_back(nodes[i]);
        }
    return ans;
}


static Path make_path(int agent_id, Node* node) {
    Path ans;
    ans.agent_id = agent_id;
    if (node == nullptr)
        return ans;
    while (node != nullptr) {
        ans.locations.push_back(node->location);
        node = node->parent;
    }
    std::reverse(ans.locations.begin(), ans.locations.end());
    return ans;
}


Path a_star(int agent_id, Location start, Location goal, unsigned init_cost,
            const std::set<Constraint> &constraints,
            const std::set<EdgeConstraint> &edge_constraints,
            const std::vector<std::string> &map) {
    Closed closed;
    Open open;
    open.add_node(Node(nullptr, start, init_cost, get_h_dist(start, goal)));
    while (!open.empty()) {
        Node *node = open.get_best_f_node();
        closed.insert(node);
        if (node->location == goal)
            return make_path(agent_id, node);
        std::vector<Node> neighbours = get_neighbours(agent_id, node, goal, constraints, edge_constraints, map);
        if (!neighbours.empty())
            for (Node &i : neighbours)
                if (!closed.has(&i))
                    open.add_node(i);
    }
    return make_path(agent_id, nullptr);
};

Path avoiding_step(int agent_id, Location point, unsigned init_cost,
            const std::set<Constraint> &constraints,
            const std::set<EdgeConstraint> &edge_constraints,
            const std::vector<std::string> &map) {
    Node node = Node(nullptr, point, init_cost, get_h_dist(point, point));
    std::vector<Node> neighbours = get_neighbours(agent_id, &node, point, constraints, edge_constraints, map);
    if (!neighbours.empty())
        for (Node &i : neighbours)
            return make_path(agent_id, &i);
    return make_path(agent_id, nullptr);
};

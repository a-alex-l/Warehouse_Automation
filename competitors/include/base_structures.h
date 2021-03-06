#pragma once
#include <vector>

struct Location {
    int x = -1;
    int y = -1;

    Location() = default;
    Location(int x, int y): x(x), y(y) {}

    bool operator == (const Location& other) const {
        return x == other.x && y == other.y;
    }

    bool operator < (const Location& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }

    bool operator != (const Location& other) const {
        return x != other.x || y != other.y;
    }
};


struct Path {
    int agent_id;
    std::vector<Location> locations;

    [[nodiscard]] bool empty() const { return locations.empty(); }


    void add(Path p) {
        for (int i = 1; i < p.locations.size(); i++)
            locations.push_back(p.locations[i]);
    }
};


struct Constraint {
    int agent_id = -1;
    Location location;
    int timestamp = -1;

    Constraint() = default;
    Constraint(int agent_id, Location location, int timestamp) :
            agent_id(agent_id), location(location), timestamp(timestamp) {};

    bool operator < (const Constraint& other) const {  // for set
        return location < other.location ||
                (location == other.location && (timestamp < other.timestamp ||
                                                (timestamp == other.timestamp && agent_id < other.agent_id)));
    }

    bool operator == (const Constraint& other) const {  // for set == set
        return location == other.location && timestamp == other.timestamp && agent_id == other.agent_id;
    }
};

struct EdgeConstraint {
    int agent_id = -1;
    Location first_location;
    Location second_location;
    int timestamp = -1;

    EdgeConstraint() = default;
    EdgeConstraint(int agent_id, Location first_location, Location second_location, int timestamp) : agent_id(agent_id),
                                                                                                     first_location(first_location), second_location(second_location), timestamp(timestamp) {};

    bool operator < (const EdgeConstraint& other) const {  // for set
        return first_location < other.first_location ||
               (first_location == other.first_location && (timestamp < other.timestamp ||
                                                           (timestamp == other.timestamp && (agent_id < other.agent_id ||
                                                                                             (agent_id == other.agent_id && second_location < other.second_location)))));
    }

    bool operator == (const EdgeConstraint& other) const {  // for set == set
        return first_location == other.first_location && timestamp == other.timestamp &&
               agent_id == other.agent_id && second_location == other.second_location;
    }
};

struct Conflict {    // edge constraint
    int first_agent_id;
    int second_agent_id;
    Location first_location;
    Location second_location;
    int timestamp;
};

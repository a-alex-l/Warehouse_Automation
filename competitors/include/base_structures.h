#pragma once
#include <vector>

struct Location {
    int x;
    int y;
    Location(int x, int y): x(x), y(y) {}

    bool operator == (const Location& other) {
        return x == other.x && y == other.y;
    }

    bool operator != (const Location& other) {
        return x != other.x || y != other.y;
    }
};

struct State {
    Location location;
    int timestamp;
    
    void operator = (const State& other) {
        location = other.location;
        timestamp = other.timestamp;
    }

    bool operator == (const State& other) {
        return location == other.location && timestamp == other.timestamp;
    }

    bool operator != (const State& other) {
        return location != other.location || timestamp != other.timestamp;
    }

    State(): location(Location(-1, -1)), timestamp(-1) {}
    explicit State(Location location, int timestamp = -1): location(location), timestamp(timestamp) {}
};

struct Path {
    int agent_id;
    double lower_bound;
    double path_cost;
    std::vector<State> states;
};

struct Constraint {
    int agent_id;
    Location location;
    int timestemp;   
};

struct Conflict {
    int first_agent_id;
    int second_agent_id;
    Location first_location;
    Location second_location;
    int timestemp;   
};

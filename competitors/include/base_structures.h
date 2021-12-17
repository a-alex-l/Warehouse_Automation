#pragma once
#include <vector>

struct State {
    int location;
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

    State(): location(-1), timestamp(-1) {}
    explicit State(int location, int timestamp = -1): location(location), timestamp(timestamp) {}
    State(const State& other) {
        location = other.location;
        timestamp = other.timestamp;
    }
};

struct Path {
    int agent_id;
    double lower_bound;
    double path_cost;
    std::vector<State> states;
};

struct Constraint {
    int agent_id;
    int location;
    int timestemp;   
};

struct Conflict {
    int first_agent_id;
    int second_agent_id;
    int first_location;
    int second_location;
    int timestemp;   
};

#include "../include/bfs_by_dimensions.h"
#include <iostream>
#include <map>
#include <cassert>


static std::vector<int> get_init_position_for_bfs(const std::vector<robot> &robots,
                                                  int task_size) {
    std::vector<int> ans;
    for (auto robot : robots) {
        ans.push_back(robot.coord1);
        ans.push_back(robot.coord2);
    }
    ans.resize(ans.size() + robots.size() + task_size, -1);
    return ans;
}

static long long convert_move_to_number(std::vector<int> &move) {
    long long move_number = 0;
    for (int i = 0; i < move.size(); i += 2) {
        if (move[i] != 0) {
            if (move[i] == -1)      move_number = move_number * 5 + 1;
            else                    move_number = move_number * 5 + 3;
        } else {
            if (move[i] == -1)      move_number = move_number * 5 + 2;
            else if (move[i] == 1)  move_number = move_number * 5 + 4;
        }
    }
    return move_number;
}

static long long fast_pow(long long a, long long d) {
    long long ans = 1;
    for (long long i = 1, j = 0; j < 63; j++, i *= 2, a = a * a) {
        if ((d&i) == i) {
            ans = ans * a;
        }
    }
    return ans;
}

static std::vector<int> get_new_move_by_number(long long move_number,
                                               int robots_size) {
    std::vector<int> move(robots_size * 2, 0);
    for (int i = int(move.size()) - 2; i >= 0; i -= 2) {
        switch ((move_number / fast_pow(5, i / 2)) % 5) {
            case 1: move[i] = -1, move[i + 1] =  0;
            case 2: move[i] =  0, move[i + 1] = -1;
            case 3: move[i] =  1, move[i + 1] =  0;
            case 4: move[i] =  0, move[i + 1] =  1;
        }
    }
    return move;
}

static std::vector<std::vector<int>> get_moves_by_tasks(const std::vector<int> &now,
                                                        const std::vector<task*> &tasks,
                                                        const std::vector<int> &move) {
    std::vector<std::vector<int>> moves(1, move);
    for (int i = 0 ; i < move.size(); i += 2) {

    }
}

static std::vector<int> apply_move(const std::vector<int> &now,
                                   const std::vector<int> &move,
                                   const std::list<task> &tasks,
                                   const std::vector<std::vector<bool>> &map) {
    std::vector<int> new_position = now;
    for (int i = 0; i < move.size(); i += 2) {
        new_position[i] += move[i];
        new_position[i + 1] += move[i + 1];
        if (map[new_position[i]][new_position[i + 1]])
            return now;
    }
    return new_position;
}

static bool do_we_win(const std::vector<int> &now, int robots_size) {
    for (int i = robots_size * 3; i < now.size(); i++) {
        if (now[i] != 1)
            return false;
    }
    return true;
}

void bfs_path_finder::set_path_plans(const std::map<std::vector<int>, std::vector<int>> &parent,
                                     const std::vector<int> &finish,
                                     const std::vector<robot> &robots,
                                     const std::list<task> &tasks) {
    std::vector<int> now = finish, start = get_init_position_for_bfs(robots, tasks.size());
    while (now != start) {
        const std::vector<int>& next = parent.at(now);
        for (int i = 0 ; i < robots.size() * 2; i += 2)
            path_plans[i].push_front({ now[i] - next[i], now[i + 1] - next[i + 1] });
        now = next;
    }
}

void bfs_path_finder::set_task_plans(const std::map<std::vector<int>, std::vector<int>> &parent,
                                     const std::vector<int> &finish,
                                     const std::vector<robot> &robots,
                                     const std::list<task> &tasks) {
    std::vector<int> now = finish, start = get_init_position_for_bfs(robots, tasks.size());
    while (now != start) {
        const std::vector<int>& next = parent.at(now);
        for (int i = 0 ; i < robots.size() * 2; i += 2)
            path_plans[i].push_front({ now[i] - next[i], now[i + 1] - next[i + 1] });
        now = next;
    }
}

void bfs_path_finder::init_plans(const std::vector<robot> &robots,
                                 const std::list<task> &tasks,
                                 const std::vector<std::vector<bool>> &map) {
    assert(robots.size() <= 26 && "You can't use more then 26 robots.\nEven on 10 it's nearly pointless.");
    std::map<std::vector<int>, std::vector<int>> parent;
    std::queue<std::vector<int>> que;
    que.push(get_init_position_for_bfs(robots, tasks.size()));
    std::vector<int> now;
    while(!que.empty()) {
        if (parent.size() % 100000 == 0) {
            std::cout << parent.size() << std::endl;
        }
        now = que.front();
        que.pop();
        for (long long i = 1; i < fast_pow(5, robots.size()); i++) {
            std::vector<int> new_position =
                    apply_move(now, get_new_move_by_number(i, robots.size()), tasks, map);
            if (parent.find(new_position) == parent.end()) {
                que.push(new_position);
                parent[new_position] = now;
                if (do_we_win(new_position, robots.size())) {
                    now = new_position;
                    break;
                }
            }
        }
    }
    assert(!que.empty() && "Tasks are impossible.");
    set_path_plans(parent, now, robots, tasks);
    set_task_plans(parent, now, robots, tasks);
}

void bfs_path_finder::get_moves(std::vector<robot> &robots,
                                const std::list<task> &tasks,
                                const std::vector<std::vector<bool>> &map) {
    for (int i = 0; i < robots.size() ;i++) {
        if (!path_plans[i].empty()) {
            robots[i].move_coord1 = path_plans[i].front().first;
            robots[i].move_coord2 = path_plans[i].front().second;
            path_plans[i].pop_front();
        }
    }
}

void bfs_path_finder::get_tasks_to_robots(std::vector<robot> &robots,
                                          const std::list<task> &tasks,
                                          const std::vector<std::vector<bool>> &map) {
    for (int i = 0; i < robots.size() ;i++) {
        if (robots[i].job == tasks.end() && !task_plans[i].empty()) {
            robots[i].job = task_plans[i].front();
            task_plans[i].pop_front();
        }
    }
}
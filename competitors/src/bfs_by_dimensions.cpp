#include "../include/bfs_by_dimensions.h"
#include <iostream>
#include <map>
#include <cassert>

template <class T>
static std::vector<T>& v_to_vv(std::vector<T> &v) {
    std::vector<T> tmp(v);
    v.insert(v.end(), tmp.begin(), tmp.end());
    return v;
}


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

static bool can_move_with(const std::vector<int> &now,
                          const std::vector<int> &move,
                          const std::vector<std::vector<bool>> &map) {
    for (int i = 0; i < move.size(); i += 2) {
        if (map[now[i] + move[i]][now[i + 1] + move[i + 1]])
            return false;
    }
    for (int i = 0; i < move.size(); i += 2) {
        for (int j = i + 2; j < move.size(); j += 2) {
            if (now[i] + move[i] == now[j] + move[j] &&
                    now[i + 1] + move[i + 1] == now[j + 1] + move[j + 1])
                return false;
        }
    }
    return true;
}

static std::vector<int> get_new_move_by_number(long long &move_number,
                                               const std::vector<int> &now,
                                               const std::vector<std::vector<bool>> &map,
                                               int robots_size) {
    std::vector<int> move(robots_size * 2, 0);
    do {
        for (int i = int(move.size()) - 2; i >= 0; i -= 2) {
            switch ((move_number / fast_pow(5, i / 2)) % 5) {
                case 0:
                    move[i] = 0, move[i + 1] = 0;
                    break;
                case 1:
                    move[i] = -1, move[i + 1] = 0;
                    break;
                case 2:
                    move[i] = 0, move[i + 1] = -1;
                    break;
                case 3:
                    move[i] = 1, move[i + 1] = 0;
                    break;
                case 4:
                    move[i] = 0, move[i + 1] = 1;
                    break;
            }
        }
        move_number--;
    } while(!can_move_with(now, move, map) && move_number != -1);
    return move;
}

static std::vector<int> apply_move(const std::vector<int> &now,
                                   const std::vector<int> &move) {
    std::vector<int> new_position = now;
    for (int i = 0; i < move.size(); i ++) {
        new_position[i] += move[i];
    }
    return new_position;
}

static std::vector<std::vector<int>> get_new_positions(const std::vector<int> &now,
                                                       const std::vector<task> &tasks,
                                                       const std::vector<int> &move) {
    std::vector<int> new_position = apply_move(now, move);
    std::vector<std::vector<int>> new_positions(1, new_position);
    for (int i = 0 ; i < move.size(); i += 2) {
        if (now[i / 2 + move.size()] == -1) {
            for (int j = 0; j < tasks.size(); j++) {
                if (now[move.size() / 2 * 3 + j] == -1 &&
                    tasks[j].from_coord1 == now[i] &&
                    tasks[j].from_coord2 == now[i + 1]) {
                    v_to_vv(new_positions);
                    for (int k = int(new_positions.size()) / 2; k < new_positions.size(); k++) {
                        new_positions[k][move.size() / 2 * 3 + j] = 0;
                        new_positions[k][i / 2 + move.size()] = j;
                    }
                }
            }
        }
        if (now[i / 2 + move.size()] != -1) {
            if (tasks[now[i / 2 + move.size()]].to_coord1 == new_position[i] &&
                    tasks[now[i / 2 + move.size()]].to_coord2 == new_position[i + 1]) {
                v_to_vv(new_positions);
                for (int j = int(new_positions.size()) / 2; j < new_positions.size(); j++) {
                    new_positions[j][move.size() / 2 * 3 + now[i / 2 + move.size()]] = 1;
                    new_positions[j][i / 2 + move.size()] = -1;
                }
            }
        }
    }
    return new_positions;
}

static bool do_we_win(const std::vector<int> &now, int robots_size) {
    for (int i = robots_size * 3; i < now.size(); i++) {
        if (now[i] != 1)
            return false;
    }
    return true;
}

void bfs_path_finder::set_path_plans(const std::map<std::vector<int>, std::vector<int>> &parent,
                                     std::vector<int> now,
                                     const std::vector<robot> &robots,
                                     const std::vector<task> &tasks) {
    path_plans.resize(robots.size());
    std::vector<int> start = get_init_position_for_bfs(robots, tasks.size());
    while (now != start) {
        const std::vector<int>& next = parent.at(now);
        for (int i = 0 ; i < robots.size(); i++)
            path_plans[i].push_front({ now[i * 2] - next[i * 2], now[i * 2 + 1] - next[i * 2 + 1] });
        now = next;
    }
}

void bfs_path_finder::set_task_plans(const std::map<std::vector<int>, std::vector<int>> &parent,
                                     const std::vector<int> &finish,
                                     const std::vector<robot> &robots,
                                     const std::vector<task> &tasks) {
    task_plans.resize(robots.size());
    std::vector<int> now = finish, start = get_init_position_for_bfs(robots, tasks.size());
    while (now != start) {
        const std::vector<int>& next = parent.at(now);
        for (int i = 0 ; i < robots.size(); i++)
            if (now[robots.size() * 2 + i] != next[robots.size() * 2 + i] &&
                        now[robots.size() * 2 + i] != -1 &&
                        next[robots.size() * 3 + now[robots.size() * 2 + i]] == -1)
                task_plans[i].push_front(now[robots.size() * 2 + i]);
        now = next;
    }
}

void bfs_path_finder::init_plans(const std::vector<robot> &robots,
                                 const std::vector<task> &tasks,
                                 const std::vector<std::vector<bool>> &map) {
    assert(robots.size() <= 26 && "You can't use more then 26 robots.\nEven on 10 it's nearly pointless.");
    std::vector<task> tasks_vector = std::vector<task>(std::begin(tasks), std::end(tasks));
    std::map<std::vector<int>, std::vector<int>> parent;
    std::queue<std::vector<int>> que;
    que.push(get_init_position_for_bfs(robots, tasks.size()));
    std::vector<int> now;
    while(!que.empty()) {
        if (rand() % 3000 == 0)
            std::cout << "Que: " << que.size() << " Used: " << parent.size() << std::endl;
        now = que.front();
        que.pop();
        long long i = fast_pow(5, robots.size()) - 1;
        do {
            auto new_positions = get_new_positions(now, tasks_vector,
                                      get_new_move_by_number(i, now, map, robots.size()));
            for (auto &new_position : new_positions) {
                if (parent.find(new_position) == parent.end()) {
                    que.push(new_position);
                    parent[new_position] = now;
                    if (do_we_win(new_position, robots.size())) {
                        now = new_position;
                        i = -200;
                        break;
                    }
                }
            }
        } while (i >= 0);
        if (i == -200)
            break;
    }
    assert(!que.empty() && "Tasks are impossible.");
    set_path_plans(parent, now, robots, tasks_vector);
    set_task_plans(parent, now, robots, tasks_vector);
}

void bfs_path_finder::get_moves(std::vector<robot> &robots,
                                const std::vector<task> &tasks,
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
                                          std::vector<task> &tasks,
                                          const std::vector<std::vector<bool>> &map) {
    for (int i = 0; i < robots.size(); i++) {
        if (robots[i].job == nullptr && !task_plans[i].empty()) {
            if (!task_plans[i].empty()) {
                robots[i].job = &tasks[task_plans[i].front()];
                task_plans[i].pop_front();
            }
        }
    }
}
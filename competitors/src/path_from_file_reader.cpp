#include "../include/path_from_file_reader.h"
#include <fstream>

void path_from_file_reader::get_moves(std::vector<robot> &robots,
                                const std::vector<task> &tasks,
                                const std::vector<std::string> &map) {
    for (int i = 0; i < robots.size() ;i++) {
        if (!path_plans[i].empty()) {
            robots[i].move_coord1 = path_plans[i].front().first;
            robots[i].move_coord2 = path_plans[i].front().second;
            path_plans[i].pop_front();
        }
    }
}

void path_from_file_reader::get_tasks_to_robots(std::vector<robot> &robots,
                                          std::vector<task> &tasks,
                                          const std::vector<std::string> &map) {
    for (int i = 0; i < robots.size(); i++) {
        if (robots[i].job == nullptr && !task_plans[i].empty()) {
            if (!task_plans[i].empty()) {
                robots[i].job = &tasks[task_plans[i].front()];
                task_plans[i].pop_front();
            }
        }
    }
}

path_from_file_reader::path_from_file_reader(const std::string &file_name) {
    std::ifstream input_file;
    input_file.open(file_name);
    if (!input_file.is_open())
        throw std::ios_base::failure("Error: wrong file name. Can't open file " + file_name);
    int robots_count;
    std::string word;
    while (input_file >> word) {
        if (word == "robots")
            input_file >> word >> robots_count;
        if (word == "Step:") { // must be at the end
            task_plans.resize(robots_count);
            path_plans.resize(robots_count);
            while (true) {
                input_file >> word;
                for (int i = 0; i < robots_count; i++) {
                    int dx, dy, dt;
                    input_file >> dx >> dy >> dt;
                    path_plans[i].push_back(std::make_pair(dx, dy));
                    if (task_plans[i].empty() || dt != task_plans[i].back())
                        task_plans[i].push_back(dt);
                }
                input_file >> word;
                if (word == "Win!")
                    break;
            }
        }
    }
    input_file.close();
}

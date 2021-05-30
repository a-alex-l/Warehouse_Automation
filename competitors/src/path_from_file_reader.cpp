#include "../include/path_from_file_reader.h"
#include <fstream>

void path_from_file_reader::init_plans(const std::vector<robot> &robots,
                                       const std::vector<task> &tasks,
                                       const std::vector<std::vector<bool>> &map) {

}

void path_from_file_reader::get_moves(std::vector<robot> &robots,
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

void path_from_file_reader::get_tasks_to_robots(std::vector<robot> &robots,
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

path_from_file_reader::path_from_file_reader(const std::string &file_name) {
    std::ifstream input_file;
    input_file.open(file_name);
    if (!input_file.is_open())
        throw std::ios_base::failure("Error: wrong file name. Can't open file " + file_name);
    std::string word;

    input_file.close();
}

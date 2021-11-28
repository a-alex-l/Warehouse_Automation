#include "../include/script_parser.h"
#include "../../constants.h"

#include <iostream>
#include <fstream>
#include <string>
#include <set>

void parse(const std::string &file_name,
           std::vector<std::string> &map,
           std::vector<robot> &robots,
           std::vector<task> &tasks) {
    std::ifstream input_file;
    input_file.open(file_name);
    if (!input_file.is_open())
        throw std::ios_base::failure("Error: wrong file name. Can't open file " + file_name + "! ");
    std::string word;
    while (input_file >> word) {
        if (word == "map") {
            int first_size, second_size;
            input_file >> word >> first_size >> second_size;
            map.resize(first_size, std::string(second_size, '.'));
            getline(input_file, word);
            for (int i = 0; i < map.size(); i++) {
                getline(input_file, word);
                map[i] = word;
            }
        }
        if (word == "robots") {
            int robots_size;
            input_file >> word >> robots_size;
            robots.resize(robots_size);
            for (auto &robot : robots)
                input_file >> robot.coord1 >> robot.coord2;
        }
        if (word == "tasks") {
            int tasks_count;
            input_file >> word >> tasks_count;
            tasks.resize(tasks_count);
            for (auto &task: tasks)
                input_file >> task.from_coord1 >> task.from_coord2
                           >> task.to_coord1 >> task.to_coord2;
        }
    }
    if (tasks.empty()) {
        tasks.resize(TASKS_COUNT);
        robots.resize(ROBOTS_COUNT);
        std::set<std::pair<int, int>> used_places;
        for (auto &robot : robots) {
            robot.coord1 = rand() % map.size(), robot.coord2 = rand() % map[0].size();
            while (map[robot.coord1][robot.coord2] == '#' or
                    used_places.find(std::make_pair(robot.coord1, robot.coord2)) != used_places.end())
                robot.coord1 = rand() % map.size(), robot.coord2 = rand() % map[0].size();
            used_places.insert(std::make_pair(robot.coord1, robot.coord2));
        }
        std::vector<std::pair<int, int>> points__, points_s;
        for (int i = 0; i < map.size(); i++)
            for (int j = 0; j < map[0].size(); j++) {
                if (map[i][j] == '_')
                    points__.emplace_back(i, j);
                if (map[i][j] == 's')
                    points_s.emplace_back(i, j);
            }
        for (auto &task: tasks) {
            std::pair<int, int> from = points__[rand() % points__.size()],
                    to = points_s[rand() % points_s.size()];
            if (rand() % 2)
                std::swap(from, to);
            task.from_coord1 = from.first;
            task.from_coord2 = from.second;
            task.to_coord1 = to.first;
            task.to_coord2 = to.second;
        }
    }
    for (auto &task : tasks) {
        int r = 55 + rand() % 200, g = 55 + rand() % 200, b = 55 + rand() % 200;
        task.color = sf::Color(400 * r / (r + b + g),
                               400 * g / (r + b + g),
                               400 * b / (r + b + g));
    }
    input_file.close();
}

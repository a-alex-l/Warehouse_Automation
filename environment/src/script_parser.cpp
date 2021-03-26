#include "../include/script_parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>

void parse(const std::string &file_name,
           std::vector<std::vector<bool>> &map,
           std::vector<robot> &robots,
           std::vector<task> &tasks) {
    std::ifstream input_file;
    input_file.open(file_name);
    if (!input_file.is_open())
        throw std::ios_base::failure("Error: wrong file name. Can't open file " + file_name);
    std::string word;
    while (input_file >> word) {
        if (word == "map") {
            int first_size, second_size;
            input_file >> word >> first_size >> second_size;
            map.resize(first_size, std::vector<bool>(second_size, false));
            getline(input_file, word);
            for (int i = 0; i < map.size(); i++) {
                getline(input_file, word);
                for (int  j = 0; j < map[0].size(); j++)
                    map[i][j] = (word[j] == '#');
            }
        }
        if (word == "robots") {
            int robots_size;
            input_file >> word  >> robots_size;
            robots.resize(robots_size);
            for (auto &robot : robots)
                input_file >> robot.coord1 >> robot.coord2;
        }
        if (word == "tasks") {
            int tasks_count;
            input_file >> word  >> tasks_count;
            tasks.resize(tasks_count);
            for (auto &task : tasks) {
                input_file >> word >> word >>
                           task.from_coord1 >> task.from_coord2 >> word >>
                           task.to_coord1 >> task.to_coord2;
                int r = 55 + rand() % 200, g = 55 + rand() % 200, b = 55 + rand() % 200;
                task.color = sf::Color(400 * r / (r + b + g),
                                       400 * g / (r + b + g),
                                       400 * b / (r + b + g));
            }
        }
    }
    input_file.close();
}

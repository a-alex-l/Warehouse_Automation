#include <iostream>
#include "../include/sfml_show.h"
#include "../include/game.h"
#include "../include/script_parser.h"
#include <cassert>

game::game(const std::string &file_name, path_finder *path_maker) {
    std::cout << "Parsing." << std::endl;
    parse(file_name, map, robots, tasks);
    path_planner = path_maker;
}

void game::start() {
    std::cout << "Game start." << std::endl;
    show(map, robots, tasks);
    std::cout << "Init planning." << std::endl;
    path_planner->init_plans(robots, tasks, map);
    loop();
}

void game::loop() {
    std::cout << "Loop." << std::endl;
    path_planner->get_moves(robots, tasks, map);
    show(map, robots, tasks);
    move_robots();
    remove_done_tasks();
    path_planner->get_tasks_to_robots(robots, tasks, map);
    static int how_long_tasks_not_done = 0, tasks_last_length = tasks.size();
    how_long_tasks_not_done++;
    if (tasks.size() != tasks_last_length)
        how_long_tasks_not_done = 0;
    if (!tasks.empty() || how_long_tasks_not_done == map[0].size() * map.size())
        loop();
}


void game::move_robots() {
    for (auto &robot : robots) {
        robot.coord1 += robot.move_coord1;
        robot.coord2 += robot.move_coord2;
        robot.move_coord1 = robot.move_coord2 = 0;
        assert(!map[robot.coord1][robot.coord2] && "Error: robot tried enter wall!");
    }
}

void game::remove_done_tasks() {
    for (auto &robot : robots) {
        if (robot.job != nullptr && robot.coord1 == robot.job->to_coord1 && robot.coord2 == robot.job->to_coord2) {
            robot.job->status = 1;
            robot.job = nullptr;
        }
    }
}



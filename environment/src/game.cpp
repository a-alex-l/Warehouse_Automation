#include <iostream>
#include "../include/sfml_show.h"
#include "../include/game.h"
#include "../include/script_parser.h"
#include <cassert>
#include <fstream>

game::game(const std::string &file_name, path_finder *path_maker) {
    std::cout << "Parsing." << std::endl;
    parse(file_name, map, robots, tasks);
    path_planner = path_maker;
    this->file_name = file_name;
    this->file_name.resize(this->file_name.size() - 4);
    this->file_name += "_synopsis.txt";
}

void game::start() {
    write_synopsis(0);
    std::cout << "Game start." << std::endl;
    show(map, robots, tasks);
    std::cout << "Init planning." << std::endl;
    path_planner->init_plans(robots, tasks, map);
    path_planner->get_tasks_to_robots(robots, tasks, map);
    update_tasks();
    show(map, robots, tasks);
    loop();
}

static bool do_we_win(const std::vector<task> &tasks) {
    for (task t : tasks)
        if (t.status != 1)
            return false;
    return true;
}

void game::loop() {
    std::cout << "Loop." << std::endl;
    path_planner->get_moves(robots, tasks, map);
    show(map, robots, tasks);
    static int steps_count = 0;
    steps_count++;
    write_synopsis(steps_count);
    
    move_robots();
    update_tasks();
    path_planner->get_tasks_to_robots(robots, tasks, map);
    update_tasks();
    if (!do_we_win(tasks))
        loop();
    else
        write_synopsis(steps_count);
}


void game::move_robots() {
    for (int r1 = 0 ; r1 < robots.size(); r1++) {
        for (int r2 = r1 + 1 ; r2 < robots.size(); r2++) {
            assert(!(robots[r1].coord1 == robots[r2].coord1 + robots[r2].move_coord1 &&
                     robots[r1].coord2 == robots[r2].coord2 + robots[r2].move_coord2 &&
                     robots[r2].coord1 == robots[r1].coord1 + robots[r1].move_coord1 &&
                     robots[r2].coord2 == robots[r1].coord2 + robots[r1].move_coord2) &&
                   "Error: robots tried to go through another one!");
            assert(!(robots[r2].coord1 + robots[r2].move_coord1 == robots[r1].coord1 + robots[r1].move_coord1 &&
                     robots[r1].coord2 + robots[r1].move_coord2 == robots[r2].coord2 + robots[r2].move_coord2) &&
                   "Error: robot tried to go into another one!");
        }
    }
    for (auto &robot : robots) {
        assert((map[robot.coord1][robot.coord2] != 's' ||
                map[robot.coord1 + robot.move_coord1][robot.coord2 + robot.move_coord2] != 's') &&
                "Error: robot tried enter a wall!");
        robot.coord1 += robot.move_coord1;
        robot.coord2 += robot.move_coord2;
        robot.move_coord1 = robot.move_coord2 = 0;
        assert(map[robot.coord1][robot.coord2] != '#' && "Error: robot tried enter a wall!");
    }
}

void game::update_tasks() {
    for (auto &robot : robots) {
        if (robot.job != nullptr) {
            if (robot.job->status == -1 &&
                robot.coord1 == robot.job->from_coord1 &&
                robot.coord2 == robot.job->from_coord2) {
                robot.job->status = 0;
            }
            if (robot.job->status == 0 &&
                robot.coord1 == robot.job->to_coord1 &&
                robot.coord2 == robot.job->to_coord2) {
                robot.job->status = 1;
                robot.job = nullptr;
            }
        }
    }
}

void game::write_synopsis(int steps_count) {
    static std::ofstream output_file;
    if (!output_file.is_open()) {
        output_file.open(file_name);
        if (!output_file.is_open())
            throw std::ios_base::failure("Error: wrong file name. Can't open or create file " + file_name);
    }
    if (steps_count == 0) {
        output_file << "robots = " << robots.size() << "\n";
        for (auto &robot : robots) {
            output_file << robot.coord1 << " " << robot.coord2 << " ";
        }
        output_file << "\n\nmap = " << map.size()  << " " << map[0].size() << "\n";
        for (auto &line : map) {
            output_file << line << "\n";
        }
        output_file << "\n\ntasks = " << tasks.size() << "\n";
        for (auto &task : tasks) {
            output_file << task.from_coord1 << " " << task.from_coord2 << " "
                        << task.to_coord1 << " " << task.to_coord2 << "\n";
        }
        output_file << "\n";
        return;
    }
    output_file << "Step: " << steps_count << "\n";
    for (auto robot : robots) {
        output_file << "    " << robot.move_coord1 << " " << robot.move_coord2 << " ";
        if (robot.job != nullptr)
            output_file << robot.job - &tasks[0] << "\n";
        else
            output_file << "-1\n";
    }
    if (do_we_win(tasks)) {
        output_file << "Win!";
        output_file.close();
    }
}



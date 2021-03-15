#ifndef WAREHOUSE_AUTOMATIZATION_SCRIPT_PARSER_H
#define WAREHOUSE_AUTOMATIZATION_SCRIPT_PARSER_H

#include "robot.h"
#include "task.h"
#include "../../competitors/include/path_finder.h"
#include <vector>
#include <string>

void parse(const std::string &file_name,
           std::vector<std::vector<bool>> &map,
           std::vector<robot> &robots,
           std::vector<task> &tasks,
           path_finder* path_planner);

#endif //WAREHOUSE_AUTOMATIZATION_SCRIPT_PARSER_H

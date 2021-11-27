#ifndef WAREHOUSE_AUTOMATIZATION_SCRIPT_PARSER_H
#define WAREHOUSE_AUTOMATIZATION_SCRIPT_PARSER_H

#include "robot.h"
#include "task.h"
#include "../../competitors/include/path_finder.h"
#include <vector>
#include <string>
#include <list>

void parse(const std::string &file_name,
           std::vector<std::string> &map,
           std::vector<robot> &robots,
           std::vector<task> &tasks);

#endif //WAREHOUSE_AUTOMATIZATION_SCRIPT_PARSER_H

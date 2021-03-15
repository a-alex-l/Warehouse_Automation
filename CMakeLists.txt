cmake_minimum_required(VERSION 3.17)
project(Warehouse_Automatization)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.cpp environment/include/robot.h environment/include/game.h environment/include/script_parser.h competitors/include/path_finder.h environment/src/game.cpp environment/include/task.h)

add_executable(test test.cpp environment/include/robot.h environment/include/game.h environment/include/script_parser.h competitors/include/path_finder.h environment/src/game.cpp)
cmake_minimum_required(VERSION 3.10)
project(Warehouse_Automation)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

include_directories(environment/include competitors/include)

add_executable(main
        main.cpp
        constants.h

        environment/include/task.h
        environment/include/game.h
        environment/include/robot.h
        environment/include/sfml_show.h
        environment/include/script_parser.h
        environment/src/game.cpp
        environment/src/script_parser.cpp

        competitors/include/path_finder.h
        competitors/include/bfs_by_dimensions.h
        competitors/include/path_from_file_reader.h
        competitors/include/cbs.h
        competitors/include/cbs_node.h
        competitors/include/ca_star.h
        competitors/include/a_star.h
        competitors/include/node.h
        competitors/include/base_structures.h

        competitors/src/bfs_by_dimensions.cpp
        competitors/src/cbs.cpp
        competitors/src/pbs.cpp
        competitors/src/ca_star.cpp
        competitors/src/a_star.cpp
        competitors/src/path_from_file_reader.cpp)

target_link_libraries(main sfml-graphics sfml-audio)

add_executable(test
        test.cpp

        environment/include/task.h
        environment/include/game.h
        environment/include/robot.h
        environment/include/sfml_show.h
        environment/include/script_parser.h
        environment/src/game.cpp
        environment/src/script_parser.cpp

        competitors/include/path_finder.h
        competitors/include/bfs_by_dimensions.h
        competitors/include/path_from_file_reader.h
        competitors/include/cbs.h
        competitors/include/cbs_node.h
        competitors/include/ca_star.h
        competitors/include/a_star.h
        competitors/include/node.h
        competitors/include/base_structures.h

        competitors/src/bfs_by_dimensions.cpp
        competitors/src/cbs.cpp
        competitors/src/pbs.cpp
        competitors/src/ca_star.cpp
        competitors/src/a_star.cpp
        competitors/src/path_from_file_reader.cpp)


target_link_libraries(test sfml-graphics sfml-audio)


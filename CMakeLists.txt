cmake_minimum_required(VERSION 3.10)
project(Warehouse_Automation)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

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
        competitors/src/bfs_by_dimensions.cpp
        competitors/src/path_from_file_reader.cpp competitors/include/cbs.h competitors/src/cbs.cpp competitors/include/ca_star.h competitors/include/pbs.h competitors/src/ca_star.cpp competitors/src/pbs.cpp)

target_link_libraries(main sfml-graphics sfml-audio)

add_executable(test
        test.cpp

        environment/include/robot.h
        environment/include/game.h
        environment/include/script_parser.h
        environment/src/game.cpp
        environment/include/task.h
        environment/src/script_parser.cpp

        competitors/include/path_finder.h
        competitors/include/bfs_by_dimensions.h
        competitors/src/bfs_by_dimensions.cpp
        environment/include/sfml_show.h
        competitors/include/path_from_file_reader.h
        competitors/src/path_from_file_reader.cpp)

target_link_libraries(test sfml-graphics sfml-audio)


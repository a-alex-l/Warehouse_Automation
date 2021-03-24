cmake_minimum_required(VERSION 3.17)
project(Warehouse_Automatization)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(main
        main.cpp

        environment/include/robot.h
        environment/include/game.h
        environment/include/script_parser.h
        environment/src/game.cpp
        environment/include/task.h
        environment/src/script_parser.cpp

        competitors/include/path_finder.h
        competitors/include/bfs_by_dimensions.h
        competitors/src/bfs_by_dimensions.cpp environment/include/sfml_show.h)

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
        competitors/src/bfs_by_dimensions.cpp environment/include/sfml_show.h)

target_link_libraries(test sfml-graphics sfml-audio)


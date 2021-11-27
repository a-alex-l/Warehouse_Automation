#include <iostream>
#include "environment/include/game.h"
#include "competitors/include/bfs_by_dimensions.h"
#include "competitors/include/path_from_file_reader.h"


inline void init_run(int argc, char** argv, path_finder *path_maker, game &run) {
    if (argc == 1) {
        throw std::logic_error("Error: Map path parameter isn't set!");
    }
    if (argc == 2)
        path_maker = new bfs_path_finder();
    if (argc == 3) {
        if (std::string(argv[2]) == "bfs")
            path_maker = new bfs_path_finder();
        if (std::string(argv[2]) == "read")
            path_maker = new path_from_file_reader(argv[1]);
    }
    run = game(argv[1], path_maker);
}


int main(int argc, char** argv) {
    path_finder *path_maker = nullptr;
    game run;
    init_run(argc, argv, path_maker, run);
    run.start();
    return 0;
}
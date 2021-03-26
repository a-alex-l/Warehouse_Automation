#include <iostream>
#include "environment/include/game.h"
#include "competitors/include/bfs_by_dimensions.h"

int main() {
    path_finder *path_maker = new bfs_path_finder();
    game play("../tests/tests_scripts/test2.txt", path_maker);
    play.start();
    return 0;
}

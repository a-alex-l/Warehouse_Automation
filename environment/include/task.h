#ifndef WAREHOUSE_AUTOMATIZATION_TASK_H
#define WAREHOUSE_AUTOMATIZATION_TASK_H

#include <SFML/Graphics.hpp>

struct task {
    int from_coord1, from_coord2;
    int to_coord1, to_coord2;
    sf::Color color = sf::Color(255, 0, 0);
    int status = -1; // -1 = untouched, 0 = carrying, 1 = done
};

#endif //WAREHOUSE_AUTOMATIZATION_TASK_H

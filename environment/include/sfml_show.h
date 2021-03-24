#ifndef WAREHOUSE_AUTOMATION_SFML_SHOW_H
#define WAREHOUSE_AUTOMATION_SFML_SHOW_H

#include <iostream>
#include <vector>
#include <list>
#include "../include/robot.h"
#include "../include/task.h"

void show(std::vector<std::vector<bool>> map,
          std::vector<robot> robots,
          std::list<task> tasks) {
    std::cout << "Show." << std::endl;
    static sf::RenderWindow* window = nullptr;
    static sf::Sprite board, robot;
    static sf::Texture texture_board, texture_robot;
    if (window == nullptr) { // ***** init of static sprites *****
        window = new sf::RenderWindow(
                sf::VideoMode(1 + 30 * map[0].size(),
                              1 + 30 * map.size()),
                "Warehouse");
        sf::Image image_board;
        image_board.create(1 + 30 * map[0].size(), 1 + 30 * map.size(), sf::Color(255, 255, 255));
        for (int i = 0; i < 1 + 30 * map[0].size(); i += 30)
            for (int j = 0; j < 1 + 30 * map.size(); j += 1)
                image_board.setPixel(i, j, sf::Color(100, 100, 100));
        for (int i = 0; i < 1 + 30 * map[0].size(); i += 1)
            for (int j = 0; j < 1 + 30 * map.size(); j += 30)
                image_board.setPixel(i, j, sf::Color(100, 100, 100));
        for (int i = 0; i < map[0].size(); i++)
            for (int j = 0; j < map.size(); j++)
                if (map[j][i])
                    for (int coord1 = 1 + 30 * i; coord1 < 30 * (i + 1); coord1++)
                        for (int coord2 = 1 + 30 * j; coord2 < 30 * (j + 1); coord2++)
                            image_board.setPixel(coord1, coord2, sf::Color(150, 150, 150));
        texture_board.loadFromImage(image_board);
        board.setTexture(texture_board);

        texture_robot.loadFromFile("../assets/Robot.png");
        robot.setTexture(texture_robot);
    }
    for (int frame = 0; frame < 30; frame++) {
        window->clear();
        window->draw(board);
        for (auto r : robots) {
            robot.setPosition(r.coord1 * 30 + r.move_coord1 * frame + 3,
                              r.coord2 * 30 + r.move_coord2 * frame + 3);
            window->draw(robot);
        }
        window->display();
        sf::sleep(sf::milliseconds(10));
    }
}

#endif //WAREHOUSE_AUTOMATION_SFML_SHOW_H

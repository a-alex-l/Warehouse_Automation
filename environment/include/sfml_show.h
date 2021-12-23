#ifndef WAREHOUSE_AUTOMATION_SFML_SHOW_H
#define WAREHOUSE_AUTOMATION_SFML_SHOW_H

#include <iostream>
#include <vector>
#include <list>
#include "../include/robot.h"
#include "../include/task.h"

void show(std::vector<std::string> map,
          const std::vector<robot>& robots,
          const std::vector<task>& tasks) {
    std::cout << "Show." << std::endl;
    static sf::RenderWindow* window = nullptr;
    static sf::Sprite board, robot;
    static sf::Texture texture_board, texture_robot;
    if (window == nullptr) { // ***** init of static sprites *****
        sf::ContextSettings settings;
        settings.antialiasingLevel = 8;
        window = new sf::RenderWindow(
                sf::VideoMode(1 + 30 * map[0].size(),
                              1 + 30 * map.size()), "Warehouse", sf::Style::Default, settings);
        sf::Image image_board;
        image_board.create(1 + 30 * map[0].size(), 1 + 30 * map.size(), sf::Color(255, 255, 255));
        for (int i = 0; i < 1 + 30 * map.size(); i += 30)
            for (int j = 0; j < 1 + 30 * map[0].size(); j += 1)
                image_board.setPixel(j, i, sf::Color(100, 100, 100));
        for (int i = 0; i < 1 + 30 * map.size(); i += 1)
            for (int j = 0; j < 1 + 30 * map[0].size(); j += 30)
                image_board.setPixel(j, i, sf::Color(100, 100, 100));
        for (int i = 0; i < map.size(); i++)
            for (int j = 0; j < map[0].size(); j++) {
                sf::Color color = sf::Color(255, 255, 255); // '.'
                if (map[i][j] == '#')
                    color = sf::Color(150, 150, 150);
                if (map[i][j] == '_')
                    color = sf::Color(200, 200, 255);
                if (map[i][j] == 's')
                    color = sf::Color(200, 255, 200);
                for (int coord1 = 1 + 30 * i; coord1 < 30 * (i + 1); coord1++)
                    for (int coord2 = 1 + 30 * j; coord2 < 30 * (j + 1); coord2++)
                        image_board.setPixel(coord2, coord1, color);
            }
        texture_board.loadFromImage(image_board);
        board.setTexture(texture_board);

        texture_robot.loadFromFile("../assets/Robot.png");
        robot.setTexture(texture_robot);
    }
    if (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();
        }
        window->setActive();

        for (int frame = 0; frame < 30; frame++) {
            window->clear();
            window->draw(board);
            for (auto &r : robots) {
                robot.setPosition(r.coord2 * 30 + r.move_coord2 * frame + 3,
                                  r.coord1 * 30 + r.move_coord1 * frame + 3);
                window->draw(robot);
                if (r.job != nullptr && r.job->status == 0) {
                    sf::RectangleShape rectangle(sf::Vector2f(7, 7));
                    rectangle.setFillColor(r.job->color);
                    rectangle.setPosition(r.coord2 * 30 + r.move_coord2 * frame + 12,
                                          r.coord1 * 30 + r.move_coord1 * frame + 12);
                    window->draw(rectangle);
                }
            }
            for (auto &t : tasks) {
                if (t.status == -1 || t.status == 0) {
                    sf::RectangleShape rectangle(sf::Vector2f(9, 9));
                    rectangle.setFillColor(t.color);
                    rectangle.setPosition(t.to_coord2 * 30 + 11,
                                          t.to_coord1 * 30 + 11);
                    window->draw(rectangle);
                }
                if (t.status == -1) {
                    sf::RectangleShape rectangle(sf::Vector2f(5, 5));
                    rectangle.setFillColor(t.color);
                    rectangle.setPosition(t.from_coord2 * 30 + 13,
                                          t.from_coord1 * 30 + 13);
                    window->draw(rectangle);
                }
            }
            window->display();
            sf::sleep(sf::milliseconds(15));
        }
    }
}

#endif //WAREHOUSE_AUTOMATION_SFML_SHOW_H

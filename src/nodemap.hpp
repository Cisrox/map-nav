//
// Node maps
//

#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>

#pragma once

class nodeMap {

    class node {
        std::pair<int, int> position;
        sf::CircleShape circle;
        bool wall = false;

    public:
        std::string name = "X";
        bool isWall() {return wall;};
        node(int x, int y) {position.first = x;
                            position.second = y;};
        std::pair<int, int> getPos() {return position;};

    };

    std::vector<std::vector<std::unique_ptr<node>>> map;

public:
    std::string getMapString();
    void print() {std::cout << this->getMapString();};
    nodeMap(int x, int y, int maxConnections = 8, bool walls = false);

};
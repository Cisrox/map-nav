//
// Node maps
//

#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <ctime>
#include <set>

#pragma once

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define NORTHEAST 4
#define NORTHWEST 5
#define SOUTHEAST 6
#define SOUTHWEST 7

class nodeMap {

    class node {
        std::pair<int, int> position;
        sf::CircleShape circle;
        bool wall = false;
        std::vector<bool> outEdges;

    public:
        std::string name = "X";
        bool isWall() {return wall;};
        node(int x, int y);
        std::pair<int, int> getPos() {return position;};
        int getX() {return getPos().first;};
        int getY() {return getPos().second;};
        bool isEdge(int& edgePosition) {return outEdges[edgePosition];};
        bool isCorner(int& xMax, int& yMax);
        bool isBorder(int& xMax, int& yMax);
        bool checkBoundary(int& xMax, int& yMax, int& edgePosition);
        int getOutdegree();
        void addOutEdge(int& randomPosition);
    };

    void populateMap(int& x, int& y);
    void generateEdges(int& maxConnections);
    std::vector<std::vector<std::unique_ptr<node>>> map;
    int maxX;
    int maxY;

public:
    std::string getMapString();
    std::unique_ptr<node>& getNode(int x, int y) { return map[y][x];};
    void print() {std::cout << this->getMapString();};
    nodeMap(int x, int y, int maxOutDegree = 8, bool walls = false);

};
#include <stack>
#include <queue>
#include <vector>
#include <memory>

#include "nodemap.hpp"

#pragma once

class traversalAlgorithm {
public:
    traversalAlgorithm(){
        int i = 0;
    }
    const int dx[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    const int dy[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    virtual std::unique_ptr<nodeMap::node>* traverseN(int n, nodeMap& maze, sf::RenderWindow& simulation){
        return &maze.getNode(0, 0);
    }
    bool goalFound = false;
    bool outOfNodes = false;
};

class BFS : public traversalAlgorithm {
public:
    BFS(nodeMap& maze);
    std::unique_ptr<nodeMap::node>* traverseN(int n, nodeMap& maze, sf::RenderWindow& simulation) override;
    std::queue<std::unique_ptr<nodeMap::node>*> queue;
};

class DFS : public traversalAlgorithm {
public:
    DFS(nodeMap& maze);
    std::unique_ptr<nodeMap::node>* traverseN(int n, nodeMap& maze, sf::RenderWindow& simulation) override;
    std::stack<std::unique_ptr<nodeMap::node>*> stack;
};
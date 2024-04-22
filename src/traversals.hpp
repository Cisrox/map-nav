#include <stack>
#include <queue>
#include <vector>

#include "nodemap.hpp"

#pragma once

class traversalAlgorithm {
public:
    traversalAlgorithm(){
        int i = 0;
    }
    const int dx[8] = {0, 0, -1, 1, -1, -1, 1, 1};
    const int dy[8] = {-1, 1, 0, 0, -1, 1, -1, 1};
    virtual nodeMap::node traverseN(int n, nodeMap& maze){
        int i = 0;
    }
    std::set<nodeMap::node*> visited;
    bool goalFound = false;
    bool outOfNodes = false;
};

class BFS : traversalAlgorithm {
public:
    BFS(nodeMap& maze);
    nodeMap::node traverseN(int n, nodeMap& maze) override;
    std::queue<nodeMap::node> queue;
};

class DFS : public traversalAlgorithm {
public:
    DFS(nodeMap& maze);
    nodeMap::node traverseN(int n, nodeMap& maze) override;
    std::stack<nodeMap::node> stack;
};
#include "traversals.hpp"



//Enqueue the starting point
BFS::BFS(nodeMap& maze) {
    queue.push(&maze.getStartNode());
}

//Place the starting point on the stack
DFS::DFS(nodeMap& maze){
    stack.push(&maze.getStartNode());
}


std::unique_ptr<nodeMap::node>* BFS::traverseN(int n, nodeMap& maze, sf::RenderWindow& simulation) {
    if (queue.empty()){
        outOfNodes = true;
        return &maze.getStartNode();
    }
    else {
        for (int j = 0; j < n; j++){
            std::unique_ptr<nodeMap::node>* current = queue.front();
            current->get()->traverse(simulation);
            queue.pop();

            for (int i = 0; i < 8; i++) {
                if (current->get()->isEdge(i)) {
                    int newX = current->get()->getX() + dx[i];
                    int newY = current->get()->getY() + dy[i];
                    // if within boundaries
                    if (newX <= maze.maxX && newY <= maze.maxY && newX >= 0 && newY >= 0){
                        if (maze.getNode(newX, newY)->isWall())  {continue;}
                        if (!(maze.getNode(newX, newY)->isTraversed())) {
                            queue.push(&maze.getNode(newX, newY));
                            maze.getNode(newX, newY)->traversed = true;
                            // added to queue
                            maze.getNode(newX, newY)->circle.setFillColor(sf::Color::Red);
                        }
                    }
                }
            }
        }
        if (queue.empty()){
            return &maze.getStartNode();
        }
        return queue.front();
    }
}

std::unique_ptr<nodeMap::node>* DFS::traverseN(int n, nodeMap& maze, sf::RenderWindow& simulation) {
    if (stack.empty()){
        outOfNodes = true;
        return &maze.getStartNode();
    }
    else {
        for (int j = 0; j < n; j++){
            std::unique_ptr<nodeMap::node>* current = stack.top();
            current->get()->traverse(simulation);
            stack.pop();

            for (int i = 0; i < 8; i++) {
                if (current->get()->isEdge(i)) {
                    int newX = current->get()->getX() + dx[i];
                    int newY = current->get()->getY() + dy[i];
                    // if within boundaries
                    if (newX <= maze.maxX && newY <= maze.maxY && newX >= 0 && newY >= 0){
                        if (maze.getNode(newX, newY)->isWall())  {continue;}
                        if (!(maze.getNode(newX, newY)->isTraversed())) {
                            stack.push(&maze.getNode(newX, newY));
                            maze.getNode(newX, newY)->traversed = true;
                            // added to queue
                            maze.getNode(newX, newY)->circle.setFillColor(sf::Color::Red);
                        }
                    }
                }
            }
        }
        if (stack.empty()){
            return &maze.getStartNode();
        }
        return stack.top();
    }
}
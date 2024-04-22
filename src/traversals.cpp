#include "traversals.hpp"



//Enqueue the starting point
BFS::BFS(nodeMap& maze) {
    queue.push(*maze.getNode(maze.startX, maze.startY));
}

//Place the starting point on the stack
DFS::DFS(nodeMap& maze){
    stack.push(*maze.getNode(maze.startX, maze.startY));
}


nodeMap::node BFS::traverseN(int n, nodeMap& maze) {
    if (queue.empty()){
        outOfNodes = true;
    }
    else{
        for (int j = 0; j < n; j++){
            nodeMap::node current = queue.front();
            queue.pop();

            visited.insert(&current);

            maze.map[current.getX()][current.getY()]->circle.setFillColor(sf::Color(255, 234, 0));

            for (int i = 0; i < 8; ++i) {
                if (current.isEdge(i)) {
                    int newX = current.getX() + dx[i];
                    int newY = current.getY() + dy[i];
                    if (newX <= maze.maxX && newY <= maze.maxY && newX >= 0 && newY >= 0){
                        nodeMap::node newnode = *maze.getNode(newX, newY);
                        if (visited.count(&newnode) == 0) {
                            queue.push(*maze.getNode(newX, newY));
                        }
                    }
                }
            }
            return current;
        }
    }
}

nodeMap::node DFS::traverseN(int n, nodeMap& maze) {

}
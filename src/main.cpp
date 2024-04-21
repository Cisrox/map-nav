//
// Main
//

#include "gui.hpp"
#include "nodemap.hpp"

int main() {
    // get choices/settings from the intro window
    int rows;
    int columns;
    int maxConnections;
    bool genWalls;
    int algorithmOneCode = 1;
    int algorithmTwoCode = 2;
    if (generateIntroWindow(rows, columns, maxConnections, genWalls) == -1) {
        return -1;
    }

    // create a graph
    nodeMap maze(columns, rows, maxConnections, genWalls);

    // simulate algorithm 1 on graph (collect time taken somehow)
    generateSimulationWindow(maze, algorithmOneCode);

    maze.reset();

    // simulate algorithm 2 on graph (collect time taken somehow)
    generateSimulationWindow(maze, algorithmTwoCode);

    maze.reset();

    // compare total time, declare a winner (exit screen)
    return 0;
}
//
// Main
//

#include "gui.hpp"
#include "nodemap.hpp"
#include "traversals.hpp"

int main() {
    // get choices/settings from the intro window
    int rows;
    int columns;
    int maxConnections;
    bool genWalls;
    int algorithmOneCode = 1;
    int algorithmTwoCode = 2;
    std::string algorithmOneName;
    std::string algorithmTwoName;
    if (generateIntroWindow(rows, columns, maxConnections, genWalls) == -1) {
        return -1;
    }

    // create a graph
    nodeMap maze(columns, rows, maxConnections, genWalls);
    if (algorithmOneCode == 1) {
        algorithmOneName = "BFS";
    }
    if (algorithmOneCode == 2) {
        algorithmOneName = "DFS";
    }
    if (algorithmTwoCode == 1) {
        algorithmTwoName = "BFS";
    }
    if (algorithmTwoCode == 2) {
        algorithmTwoName = "DFS";
    }

    // simulate algorithm 1 on graph (collect time taken somehow)
    long long timeOne = generateSimulationWindow(maze, algorithmOneCode);
    if (timeOne == -1) {
        return -1;
    }
    maze.reset();

    // simulate algorithm 2 on graph (collect time taken somehow)
    long long timeTwo = generateSimulationWindow(maze, algorithmTwoCode);
    if (timeTwo == -1) {
        return -1;
    }
    maze.reset();

    // compare total time, declare a winner (exit screen)
    if (timeOne == timeTwo) {
        std::cout << "Tie";
        generateWinnerMenu(algorithmOneName, algorithmTwoName, timeOne, timeTwo, true);
    } else {
        generateWinnerMenu(algorithmOneName, algorithmTwoName, timeOne, timeTwo);
    }
    return 0;
}
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

// A grid based data structure that stores nodes
class nodeMap {

    class node {
        std::pair<int, int> position; // (x, y)
        sf::CircleShape circle; // Visual representation of the node
        bool wall = false; // Whether this is a wall (cannot be traversed onto)
        std::vector<bool> outEdges; // Vector of bool of max size 8 (indexes 0 - 7).
                                    // Each index corresponds to the same direction for each node.
        std::vector<std::vector<sf::VertexArray>> outEdgesLines; // Vector of vertex vectors, stores the lines needed to
                                                            // generate edge rays.
                                    // Each index corresponds to the same direction for each node
        bool traversed = false;
        bool goalNode = false;
        bool startNode = false;

    public:
        std::string name = "X"; // Node's name
        bool isWall() {return wall;}; // Returns if it is a wall
        node(int x, int y, int radius = 30); // Generate a rudimentary node.
        std::pair<int, int> getPos() {return position;}; // Returns position pair
        int getX() {return getPos().first;}; // Returns x
        int getY() {return getPos().second;}; // Returns y
        bool isEdge(int& edgePosition) {return outEdges[edgePosition];}; // Returns if there is an edge in direction
        bool isCorner(int& xMax, int& yMax); // Returns if this node is in the corner of the board
        bool isBorder(int& xMax, int& yMax);  // Returns if this node is in the border of the board
        bool checkBoundary(int& xMax, int& yMax, int& edgePosition); // Returns if an edge would direct out of bounds
        int getOutDegree(); // Returns the out degree of the node.
        void addOutEdge(int& randomPosition); // Adds an edge in the given direction.
        void drawEdges(sf::RenderWindow& window); // Draws all of a nodes edges
        sf::CircleShape& getCircle() {return circle;}; // Returns the circle shape of a given node
        float getCenterX() {return ((circle.getPosition().x) + (circle.getOrigin().x));}; // Returns x val of center
        float getCenterY() {return ((circle.getPosition().y) + (circle.getOrigin().y));}; // Returns y val of center
        void reset(); // Resets node and its edges back to default.
        void setStartNode(); // Sets nodes characteristics to match a start node's
        void setGoalNode(); // Sets nodes characteristics to match a goal node's
        const bool isGoalNode() {return goalNode;}; // Returns whether this is the goal node.
        const bool isTraversed() {return traversed;}; // Returns whether a node has been traversed already.
    };

    void populateMap(int& x, int& y); // Fills the map[y][x] vector with rudimentary nodes.
    void generateEdges(int& maxConnections); // Generates desired amount of out edges for each node in map[y][x]

    std::vector<std::vector<std::unique_ptr<node>>> map; // Note: This is organized like [y][x].
                                                        // unique_ptr cannot be copied, so nodes must be passed by
                                                        // reference. Loop through like for(auto& x : map) {...}
    int maxX; // Boundary value for x
    int maxY; // Boundary value for y
    int goalX = 0; // Goal node X
    int goalY = 0; // Goal node Y
    int startX = 0; // Start node X
    int startY = 0; // Start node Y


public:
    std::string getMapString(); // Returns a string representation of the nodeMap, using node names.
    std::string getOutDegreeString(); // Returns a string representation of the nodeMap, using outdegrees.
    std::unique_ptr<node>& getNode(int x, int y) { return map[y][x];}; // Returns the reference to node at [y][x]
    void print() {std::cout << this->getMapString();}; // Prints string representation of nodeMap
    void printOutDegrees() {std::cout << this->getOutDegreeString();}; // Prints out degree representation of nodeMap
    nodeMap(int x, int y, int maxOutDegree = 8, bool walls = false); // Generates a new nodeMap with given parameters.
    void drawFull(sf::RenderWindow& window); // Draws the entire map to window.
    void reset(); // Clears any recoloring done by traversal algorithm
    void setStartNode(int x, int y); // Sets start node values based on given coordinates
    void setGoalNode(int x, int y); // Sets goal node values based on given coordinates.
    std::unique_ptr<node>& getStartNode() {return map[startY][startX];}; // Returns reference to start node.
    std::unique_ptr<node>& getGoalNode() {return map[goalY][goalX];}; // Returns reference to goal node.
    void chooseStartAndFinish(); // Chooses a start and goal node for the maze.
};
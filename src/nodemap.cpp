//
// Node maps
//

#include "nodemap.hpp"

// Generation of a new nodeMap of Y rows and X columns.
nodeMap::nodeMap(int x, int y, int maxOutDegree, bool walls) {
    this->maxX = x-1;
    this->maxY = y-1;

    // Populates the map with blank nodes
    this->populateMap(x, y);

    // Fill with walls if necessary
    if (walls) {
        //do something
    }

    // Generate edges
    this->generateEdges(maxOutDegree);

}

// Converts a nodeMap into a string representation, where each line is a row of the name of each node in order.
std::string nodeMap::getMapString() {
    std::string mapString;
    // For each row vector
    for (auto const& currentRow : this->map) {
        // For each node in row
        for(auto const& currentNode : currentRow) {
            mapString += currentNode->name;
        }
        mapString += "\n";
    }
    return mapString;
}

// Populates the nodeMap with rudimentary nodes, with no connections.
void nodeMap::populateMap(int& x, int& y) {
    // For each row
    for (int currentY = 0; currentY < y; currentY++) {
        std::vector<std::unique_ptr<node>> currentRow;
        // For each position in row
        for (int currentX = 0; currentX < x; currentX++) {
            // Create a new node object with given position, adds it to the map
            std::unique_ptr<node> newNode(new node(currentX, currentY));
            currentRow.push_back(std::move(newNode));
        }
        this->map.push_back(std::move(currentRow));
    }
}

// Generates random out edges for every node in the map, up to either the max possible amount they can have,
// or the max possible out degree, whichever they reach first.
void nodeMap::generateEdges(int& maxOutDegree) {
    // For each row vector
    for (auto const& currentRow : this->map) {
        // For each node in row
        for(auto const& currentNode : currentRow) {
            // Generate using a better source?
            srand(time(NULL));
            bool edgesFull = false;
            int edgesCount = 0;
            while (!edgesFull) {
                std::set<int> numbersTried;
                int randomPosition;

                // Generates random numbers until one is generated that has not been tried yet.
                // 0 = North, 1 = South, 2 = East, 3 = West
                // 4 = NorthEast, 5 = NorthWest, 6 = SouthEast, 7 = SouthWest
                while (true) {
                    randomPosition = rand() % 8;
                    if (numbersTried.find(randomPosition) == numbersTried.end()) {
                        numbersTried.insert(randomPosition);
                        break;
                    }
                }
                // If there is not already an edge at this position
                if (!(currentNode->isEdge(randomPosition))) {
                    // If the edge we are trying to add would point out of bounds
                    if (currentNode->checkBoundary(this->maxX, this->maxY, randomPosition)) {
                        continue;
                    }

                    // Adds an edge in the given direction
                    currentNode->addOutEdge(randomPosition);
                    edgesCount++;

                    // If a corner has reached its max number of possible edges
                    if (currentNode->isCorner(this->maxX, this->maxY)) {
                        if (edgesCount == 3) {
                            edgesFull = true;
                        }
                    }

                    // If a border has reached its max number of possible edges (Corners already resolved)
                    if (currentNode->isBorder(this->maxX, this->maxY)) {
                        if (edgesCount == 5) {
                            edgesFull = true;
                        }
                    }

                    // If the number of edges has reached the desired out degree
                    if (edgesCount == maxOutDegree) {
                        edgesFull = true;
                    }

                }
            }
        }
    }
}

//
// Nodes
//

// Node constructor
nodeMap::node::node(int x, int y) {
    position.first = x;
    position.second = y;
    // For it's 8 possible adjacent spots (N, S, E, W, NE, NW, SE, SW)
    for (int i = 0; i < 8; i++) {
        // Set edge to false
        outEdges.push_back(false);
    }
}

// Checks whether adding an edge in the given direction would attempt to connect outside the boundaries of the map.
bool nodeMap::node::checkBoundary(int& xMax, int& yMax, int& edgePosition) {

    // If on the top row
    if (getY() == 0) {
        // If trying to add an edge above
        if (edgePosition == NORTH || edgePosition == NORTHEAST || edgePosition == NORTHWEST) {
            return true;
        }

        // If top left corner
        if (getX() == 0) {
            // If trying to add an edge to the left (OOB)
            if (edgePosition == WEST || edgePosition == SOUTHWEST) {
                return true;
            }
        }

        // If top right corner
        if (getX() == xMax) {
            // If trying to add an edge to the right (OOB)
            if (edgePosition == EAST || edgePosition == SOUTHEAST) {
                return true;
            }
        }
    }

    // If on the bottom row
    if (getY() == yMax) {
        // If trying to add an edge below
        if (edgePosition == SOUTH || edgePosition == SOUTHEAST || edgePosition == SOUTHWEST) {
            return true;
        }

        // If bottom left corner
        if (getX() == 0) {
            // If trying to add an edge to the left (OOB)
            if (edgePosition == WEST || edgePosition == NORTHWEST) {
                return true;
            }
        }

        // If bottom right corner
        if (getX() == xMax) {
            // If trying to add an edge to the right (OOB)
            if (edgePosition == EAST || edgePosition == NORTHEAST) {
                return true;
            }
        }

    }

    // If on the left column (Corners already covered)
    if (getX() == 0) {
        // If trying to add an edge to the left (OOB)
        if (edgePosition == WEST || edgePosition == NORTHWEST || edgePosition == SOUTHWEST) {
            return true;
        }
    }

    // If on the right column (Corners already covered)
    if (getX() == xMax) {
        // If trying to add an edge to the right (OOB)
        if (edgePosition == EAST || edgePosition == NORTHEAST || edgePosition == SOUTHEAST) {
            return true;
        }
    }

    return false;
}

// Adds an out edge in the given direction
void nodeMap::node::addOutEdge(int &randomPosition) {
    // Sets an out edge at this position.
    this->outEdges[randomPosition] = true;
}

// Checks whether this node is a corner node.
bool nodeMap::node::isCorner(int &xMax, int &yMax) {
    // If in top left corner
    if (getX() == 0 && getY() == 0) { return true;}
    // If in top right corner
    if (getX() == xMax && getY() == 0) { return true;}
    // If in bottom left corner
    if (getX() == 0 && getY() == yMax) { return true;}
    // If in bottom right corner
    if (getX() == xMax && getY() == yMax) { return true;}

    return false;

}

// Checks whether this node is a border node (Can also be a corner!)
bool nodeMap::node::isBorder(int &xMax, int &yMax) {
    // If in left or right column
    if (getX() == 0 || getX() == xMax) { return true;}

    // If in top or bottom row
    if (getY() == 0 || getY() == yMax) { return true;}

    return false;
}

// Gets the outDegree of a desired node.
int nodeMap::node::getOutDegree() {
    int outDegree = 0;
    // For each bool bit in outEdges
    for (auto outEdge : outEdges) {
        // If there is an out edge, increment by 1
        if (outEdge) {
            outDegree++;
        }
    }
    return outDegree;
}

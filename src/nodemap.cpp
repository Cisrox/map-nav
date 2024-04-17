//
// Node maps
//
#include "nodemap.hpp"

nodeMap::nodeMap(int x, int y, int maxConnections, bool walls) {

    // Populates the map with blank nodes
    this->populateMap(x, y);

    // Fill with walls if necessary
    if (walls) {
        //do something
    }

    // Generate adjacency


}

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

void nodeMap::populateMap(int x, int y) {
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


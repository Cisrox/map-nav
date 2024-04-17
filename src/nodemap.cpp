//
// Node maps
//
#include "nodemap.hpp"

nodeMap::nodeMap(int x, int y, int maxConnections, bool walls) {

    // Populates the map with blank nodes
    for (int currentY = 0; currentY < y; currentY++) {
        std::vector<std::unique_ptr<node>> currentRow;
        for (int currentX = 0; currentX < x; currentX++) {
            // Create a new node object with given position, adds it to the map
            std::unique_ptr<node> newNode(new node(currentX, currentY));
            currentRow.push_back(std::move(newNode));
        }
        this->map.push_back(std::move(currentRow));
    }
    // Generate adjacency

}

std::string nodeMap::getMapString() {
    std::string mapString;
    for (auto const& currentRow : this->map) {
        for(auto const& currentNode : currentRow) {
            mapString += currentNode->name;
        }
        mapString += "\n";
    }
    return mapString;
}


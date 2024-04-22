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

    this->chooseStartAndFinish();

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
            // Seed randomizer
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_int_distribution<int> dist(0, 7);
            bool edgesFull = false;
            int edgesCount = 0;
            while (!edgesFull) {
                std::set<int> numbersTried;
                int randomPosition;

                // Generates random numbers until one is generated that has not been tried yet.
                // 0 = North, 1 = South, 2 = East, 3 = West
                // 4 = NorthEast, 5 = NorthWest, 6 = SouthEast, 7 = SouthWest
                while (true) {
                    randomPosition = dist(mt);
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

// Creates a grid of all node's out degrees.
std::string nodeMap::getOutDegreeString() {
    std::string outDegreeString;
    // For each row vector
    for (auto const& currentRow : this->map) {
        // For each node in row
        for(auto const& currentNode : currentRow) {
            outDegreeString += std::to_string(currentNode->getOutDegree());
        }
        outDegreeString += "\n";
    }
    return outDegreeString;
}

// Draws the entire map to the given window
void nodeMap::drawFull(sf::RenderWindow &window) {
    // For each row
    for (auto const& currentRow : this->map) {
        // For each node in row
        for(auto const& currentNode : currentRow) {
            window.draw(currentNode->getCircle());
            currentNode->drawEdges(window);
        }
    }
}

// Resets entire map
void nodeMap::reset() {
    for (auto& rows : this->map) {
        for (auto& currentNode : rows) {
            currentNode->reset();
        }
    }
}

// Sets a node to be the start node
void nodeMap::setStartNode(int x, int y) {
    startX = x;
    startY = y;
    map[y][x]->setStartNode();
}

// Sets a node to be the goal node
void nodeMap::setGoalNode(int x, int y) {
    goalX = x;
    goalY = y;
    map[y][x]->setGoalNode();
}

// Choose goal node position and start node position
void nodeMap::chooseStartAndFinish() {

    // seed randomizer
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> xDist(0, maxX);
    std::uniform_int_distribution<int> yDist(0, maxY);

    int randStartX = xDist(mt);
    int randStartY = yDist(mt);

    setStartNode(randStartX, randStartY);

    int randGoalX = xDist(mt);
    int randGoalY = yDist(mt);

    // if by extreme chance the goal and start positions are the same, re-roll
    while (randStartX == randGoalX && randStartY == randGoalY) {
        randGoalX = xDist(mt);
        randGoalY = yDist(mt);
    }

    setGoalNode(randGoalX, randGoalY);
}

void nodeMap::drawSection(sf::RenderWindow &window, int x, int y) {
    drawFull(window);
}

void nodeMap::drawTimer(sf::RenderWindow &window, int x, int y, int minutes, int seconds){
    if (!this->digits.loadFromFile("C:/map-nav/img/digits.png"))
        std::cout << "SHOOT" << std::endl;
    int dm1;
    int dm2;
    int ds1;
    int ds2;
    if (minutes < 10){
        dm1 = 0;
        dm2 = minutes;
    }
    else if (minutes >= 10 && minutes < 59){
        dm1 = minutes / 10;
        dm2 = minutes % 10;
    }
    else{
        dm1 = 5;
        dm2 = 9;
    }
    if (seconds < 10){
        ds1 = 0;
        ds2 = seconds;
    }
    else if (seconds >= 10 && seconds < 59){
        ds1 = seconds / 10;
        ds2 = seconds % 10;
    }
    else{
        ds1 = 5;
        ds2 = 9;
    }
    this->Timer_md1.setScale(2.f, 2.f);
    this->Timer_md2.setScale(2.f, 2.f);
    this->Timer_sd1.setScale(2.f, 2.f);
    this->Timer_sd2.setScale(2.f, 2.f);
    this->Timer_md1.setTextureRect(sf::IntRect(21 * dm1, 0, 21, 32));
    this->Timer_md1.setTexture(this->digits);
    this->Timer_md2.setTextureRect(sf::IntRect(21 * dm2, 0, 21, 32));
    this->Timer_md2.setTexture(this->digits);
    this->Timer_sd1.setTextureRect(sf::IntRect(21 * ds1, 0, 21, 32));
    this->Timer_sd1.setTexture(this->digits);
    this->Timer_sd2.setTextureRect(sf::IntRect(21 * ds2, 0, 21, 32));
    this->Timer_sd2.setTexture(this->digits);
    this->Timer_md1.setPosition(x + 550, y - 375);
    this->Timer_md2.setPosition(x + 592, y - 375);
    this->Timer_sd1.setPosition(x + 634, y - 375);
    this->Timer_sd2.setPosition(x + 676, y - 375);
    window.draw(Timer_md1);
    window.draw(Timer_md2);
    window.draw(Timer_sd1);
    window.draw(Timer_sd2);
}

//
// Nodes
//

// Node constructor
nodeMap::node::node(int x, int y, int radius) {
    position.first = x;
    position.second = y;

    // Generates a circle of size radius, with coordinates relative to (Radius + X*Radius*3), (Radius + Y*Radius*3)
    // The default radius is size 30.
    circle.setRadius(radius);
    if (isWall()) {
        this->circle.setFillColor(sf::Color::Black);
    } else {
        this->circle.setFillColor(sf::Color(155, 155, 155));
    }
    circle.setOutlineThickness(-2);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOrigin(circle.getRadius()/2, circle.getRadius()/2);
    circle.setPosition(circle.getRadius()+(x*circle.getRadius()*3),
                       circle.getRadius()+(y*circle.getRadius()*3));

    // For it's 8 possible adjacent spots (N, S, E, W, NE, NW, SE, SW)
    for (int i = 0; i < 8; i++) {
        // Set edge to false
        outEdges.push_back(false);

        // Generate line shapes for each direction

        if (i == NORTH) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX+(radius/3), centerY-radius);
            sf::Vector2f pointTwo(centerX+(radius/3), centerY-(radius*2));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointLeft(centerX+(radius/3)-(radius/5), centerY-(radius*2)+(radius/5));
            triangle[1].position = trianglePointLeft;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointRight(centerX+(radius/3)+(radius/5), centerY-(radius*2)+(radius/5));
            triangle[2].position = trianglePointRight;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);

        }

        if (i == SOUTH) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX-(radius/3), centerY+radius);
            sf::Vector2f pointTwo(centerX-(radius/3), centerY+(radius*2));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointLeft(centerX-(radius/3)-(radius/5), centerY+(radius*2)-(radius/5));
            triangle[1].position = trianglePointLeft;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointRight(centerX-(radius/3)+(radius/5), centerY+(radius*2)-(radius/5));
            triangle[2].position = trianglePointRight;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);
        }

        if (i == EAST) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX+radius, centerY+(radius/3));
            sf::Vector2f pointTwo(centerX+(radius*2), centerY+(radius/3));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointTop(centerX+(radius*2)-(radius/5), centerY+(radius/3)-(radius/5));
            triangle[1].position = trianglePointTop;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointBottom(centerX+(radius*2)-(radius/5), centerY+(radius/3)+(radius/5));
            triangle[2].position = trianglePointBottom;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);

        }

        if (i == WEST) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX-radius, centerY-(radius/3));
            sf::Vector2f pointTwo(centerX-(radius*2), centerY-(radius/3));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointTop(centerX-(radius*2)+(radius/5), centerY-(radius/3)-(radius/5));
            triangle[1].position = trianglePointTop;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointBottom(centerX-(radius*2)+(radius/5), centerY-(radius/3)+(radius/5));
            triangle[2].position = trianglePointBottom;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);
        }

        if (i == NORTHEAST) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);
            float angle = (sqrt(2)/2);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX+(radius*angle)+(radius/3*angle), centerY-(radius*angle));
            sf::Vector2f pointTwo(centerX+(radius*3*angle)+(radius/3*angle), centerY-(radius*3*angle));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointTop(centerX+(radius*3*angle)+(radius/3*angle)-(radius/5),
                                          centerY-(radius*3*angle));
            triangle[1].position = trianglePointTop;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointBottom(centerX+(radius*3*angle)+(radius/3*angle),
                                             centerY-(radius*3*angle)+(radius/5));
            triangle[2].position = trianglePointBottom;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);
        }

        if (i == NORTHWEST) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);
            float angle = (sqrt(2)/2);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX-(radius*angle)-(radius/3*angle), centerY-(radius*angle));
            sf::Vector2f pointTwo(centerX-(radius*3*angle)-(radius/3*angle), centerY-(radius*3*angle));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointTop(centerX-(radius*3*angle)-(radius/3*angle)+(radius/5),
                                          centerY-(radius*3*angle));
            triangle[1].position = trianglePointTop;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointBottom(centerX-(radius*3*angle)-(radius/3*angle),
                                             centerY-(radius*3*angle)+(radius/5));
            triangle[2].position = trianglePointBottom;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);
        }

        if (i == SOUTHEAST) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);
            float angle = (sqrt(2)/2);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX+(radius*angle)+(radius/3*angle), centerY+(radius*angle));
            sf::Vector2f pointTwo(centerX+(radius*3*angle)+(radius/3*angle), centerY+(radius*3*angle));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointTop(centerX+(radius*3*angle)+(radius/3*angle)-(radius/5),
                                          centerY+(radius*3*angle));
            triangle[1].position = trianglePointTop;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointBottom(centerX+(radius*3*angle)+(radius/3*angle),
                                             centerY+(radius*3*angle)-(radius/5));
            triangle[2].position = trianglePointBottom;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);
        }

        if (i == SOUTHWEST) {
            std::vector<sf::VertexArray> edgeRays;

            float centerX = (circle.getPosition().x)+(circle.getOrigin().x);
            float centerY = (circle.getPosition().y)+(circle.getOrigin().y);
            float angle = (sqrt(2)/2);

            sf::VertexArray mainLine(sf::Lines, 2);
            sf::Vector2f pointOne(centerX-(radius*angle)-(radius/3*angle), centerY+(radius*angle));
            sf::Vector2f pointTwo(centerX-(radius*3*angle)-(radius/3*angle), centerY+(radius*3*angle));
            mainLine[0].position = pointOne;
            mainLine[0].color = sf::Color::Black;
            mainLine[1].position = pointTwo;
            mainLine[1].color = sf::Color::Black;

            edgeRays.emplace_back(mainLine);

            sf::VertexArray triangle(sf::Triangles, 3);
            triangle[0].position = pointTwo;
            triangle[0].color = sf::Color::Black;

            sf::Vector2f trianglePointTop(centerX-(radius*3*angle)-(radius/3*angle)+(radius/5),
                                          centerY+(radius*3*angle));
            triangle[1].position = trianglePointTop;
            triangle[1].color = sf::Color::Black;

            sf::Vector2f trianglePointBottom(centerX-(radius*3*angle)-(radius/3*angle),
                                             centerY+(radius*3*angle)-(radius/5));
            triangle[2].position = trianglePointBottom;
            triangle[2].color = sf::Color::Black;

            edgeRays.emplace_back(triangle);

            outEdgesLines.emplace_back(edgeRays);
        }

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

// Draws all edges in the entire maze.
void nodeMap::node::drawEdges(sf::RenderWindow &window) {
    for (int i = 0; i < 8; i++) {
        if(isEdge(i)) {
            for (auto& line : outEdgesLines[i]) {
                window.draw(line);
            }
        }
    }

}

// Wipes node back to default settings.
void nodeMap::node::reset() {
    // reset node to default color
    if (isWall()) {
        this->circle.setFillColor(sf::Color::Black);
        this->traversed = false;
    }
    else if (startNode) {
        ;
    }
    else if (goalNode) {
        this->traversed = false;
    }
    else {
        this->circle.setFillColor(sf::Color(155, 155, 155));
        this->traversed = false;
    }



    // for each set of line pieces
    for (auto& figure : outEdgesLines) {
        // for each shape
        for (auto& vertex : figure) {
            // for each vertex in shape
            for (int i = 0; i < vertex.getVertexCount(); i++) {
                // reset color to black
                vertex[i].color = sf::Color::Black;
            }
        }
    }
}

void nodeMap::node::setGoalNode() {
    // Sets color to bright purple
    this->circle.setFillColor(sf::Color(191, 65, 191));
    this->goalNode = true;
}

void nodeMap::node::setStartNode() {
    // Sets color to bright yellow
    this->circle.setFillColor(sf::Color(255, 234, 0));
    this->startNode = true;
    this->traversed = true;
}

void nodeMap::node::traverse(sf::RenderWindow& simulation) {
    if (startNode) {
        return;
    }
    this->circle.setFillColor(sf::Color(0, 255, 0));
    this->traversed = true;
    simulation.draw(circle);
}

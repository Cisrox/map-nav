//
// GUI
//

#include <SFML/Graphics.hpp>
#include <iostream>
#include "nodemap.hpp"
#include "traversals.hpp"
#pragma once

// change return type, input any necessary data/images (Done?)
int generateIntroWindow(int& rows, int& columns, int& maxConnections, bool& genWalls);
void generateSimulationWindow(nodeMap& maze, int algorithmCode);


// other gui functions
void setTextMiddle(sf::Text &text, float x, float y);
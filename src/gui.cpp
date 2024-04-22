//
// GUI
//

#include "gui.hpp"
#include <string>
#include <cctype>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <unistd.h>


void setTextMiddle(sf::Text &text, float x, float y) {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

int generateIntroWindow(int& rows, int& columns, int& maxConnections, bool& genWalls) {
    sf::RenderWindow intro(sf::VideoMode(800, 600), "Intro Window");
    sf::Font font;
    if (!font.loadFromFile("../img/font.ttf")){
        return -1;
    }
    //Graphic Image
    sf::Texture cover;
    if (!cover.loadFromFile("../img/mapNavCover.jpg")) {
        std::cerr << "Could not load texture" << std::endl;
        return -1;
    }

    sf::Sprite coverSprite;
    coverSprite.setTexture(cover);
    coverSprite.setPosition(0, 150);
    // Original size of the texture
    sf::Vector2u textureSize = cover.getSize();
    //get desired size using scale factors
    float desiredWidth = 800;
    float desiredHeight = 435;
    float scaleX = desiredWidth / textureSize.x;
    float scaleY = desiredHeight / textureSize.y;
    coverSprite.setScale(scaleX, scaleY);

    //Welcome Text
    sf::Text welcome;
    welcome.setFont(font);
    welcome.setString("ROCKET Search Algorithm Comparison");
    welcome.setCharacterSize(24);
    welcome.setFillColor(sf::Color::Black);
    welcome.setStyle(sf::Text::Bold);
    setTextMiddle(welcome, 400, 30);

    //Input field text boxes
    sf::RectangleShape columnRect(sf::Vector2f(90, 20));
    columnRect.setPosition(138, 90);
    columnRect.setFillColor(sf::Color(200, 200, 200));  // Light gray

    sf::RectangleShape rowRect(sf::Vector2f(90, 20));
    rowRect.setPosition(138, 60);
    rowRect.setFillColor(sf::Color(200, 200, 200));  // Light gray

    sf::RectangleShape edgesRect(sf::Vector2f(30, 20));
    edgesRect.setPosition(715, 60);
    edgesRect.setFillColor(sf::Color(200, 200, 200));  // Light gray

    sf::RectangleShape yesButton(sf::Vector2f(50, 25));
    yesButton.setPosition(630, 90);
    yesButton.setFillColor(sf::Color(200, 200, 200));

    sf::RectangleShape noButton(sf::Vector2f(50, 25));
    noButton.setPosition(690, 90);
    noButton.setFillColor(sf::Color(200, 200, 200));

    //Columns Text
    sf::Text entercolumns;
    entercolumns.setFont(font);
    entercolumns.setString("Number of Columns:");
    entercolumns.setCharacterSize(10);
    entercolumns.setFillColor(sf::Color::Black);
    entercolumns.setStyle(sf::Text::Bold);
    entercolumns.setPosition(10, 95);

    //User inputted numColumns
    sf::Text userCol;
    userCol.setFont(font);
    userCol.setCharacterSize(10);
    userCol.setFillColor(sf::Color::Black);
    userCol.setStyle(sf::Text::Bold);
    userCol.setPosition(139, 95);

    //Rows Text
    sf::Text enterrows;
    enterrows.setFont(font);
    enterrows.setString("Number of Rows:");
    enterrows.setCharacterSize(10);
    enterrows.setFillColor(sf::Color::Black);
    enterrows.setStyle(sf::Text::Bold);
    enterrows.setPosition(10, 65);

    //User inputted numRows
    sf::Text userRow;
    userRow.setFont(font);
    userRow.setCharacterSize(10);
    userRow.setFillColor(sf::Color::Black);
    userRow.setStyle(sf::Text::Bold);
    userRow.setPosition(139, 65);

    //Max edges Text
    sf::Text enterMaxEdges;
    enterMaxEdges.setFont(font);
    enterMaxEdges.setString("Max Number of Outward Edges:");
    enterMaxEdges.setCharacterSize(10);
    enterMaxEdges.setFillColor(sf::Color::Black);
    enterMaxEdges.setStyle(sf::Text::Bold);
    enterMaxEdges.setPosition(510, 65);

    //User inputted max edges
    sf::Text userEdges;
    userEdges.setFont(font);
    userEdges.setCharacterSize(10);
    userEdges.setFillColor(sf::Color::Black);
    userEdges.setStyle(sf::Text::Bold);
    userEdges.setPosition(716, 65);

    //Walls Text
    sf::Text wallsTxt;
    wallsTxt.setFont(font);
    wallsTxt.setString("Generate Walls?");
    wallsTxt.setCharacterSize(10);
    wallsTxt.setFillColor(sf::Color::Black);
    wallsTxt.setStyle(sf::Text::Bold);
    wallsTxt.setPosition(510, 95);

    // Create text for buttons
    sf::Text yesText, noText;
    yesText.setFont(font);
    yesText.setString("Yes");
    yesText.setCharacterSize(10);
    yesText.setFillColor(sf::Color::White);
    yesText.setPosition(640, 95);

    noText.setFont(font);
    noText.setString("No");
    noText.setCharacterSize(10);
    noText.setFillColor(sf::Color::White);
    noText.setPosition(700, 95);

    // Create start button text
    sf::Text startText;
    startText.setFont(font);
    startText.setString("START");
    startText.setCharacterSize(40);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(350, 500);

    // Create start button
    sf::RectangleShape startRect(sf::Vector2f(140, 60));
    startRect.setPosition(340, 500);
    startRect.setFillColor(sf::Color(200, 200, 200));  // Light gray

    std::string colInput;
    std::string rowInput;
    std::string edgesInput;
    std::string finalColInput = "0";
    std::string finalRowInput = "0";
    std::string finalEdgesInput = "0";
    bool colActive = false, rowActive = false, edgesActive = false;
    bool wallsGenerated = false;
    sf::Clock cursorClock;
    bool showCursor = true;
    const sf::Time blinkDuration = sf::milliseconds(500);

    while (intro.isOpen()) {
        sf::Event event{};
        while (intro.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(intro);
                bool clickedOnCol = columnRect.getGlobalBounds().contains(mousePos.x, mousePos.y);
                bool clickedOnRow = rowRect.getGlobalBounds().contains(mousePos.x, mousePos.y);
                bool clickedOnEdges = edgesRect.getGlobalBounds().contains(mousePos.x, mousePos.y);
                //check if Yes/No button was clicked
                if (yesButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    noButton.setFillColor(sf::Color(200, 200, 200));
                    yesButton.setFillColor(sf::Color(150, 150, 150));
                    wallsGenerated = true;
                }
                if (noButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    yesButton.setFillColor(sf::Color(200, 200, 200));
                    noButton.setFillColor(sf::Color(150, 150, 150));
                    wallsGenerated = false;
                }
                if (startRect.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    int finalRows = stoi(finalRowInput);
                    int finalCol = stoi(finalColInput);
                    int finalEdges = stoi(finalEdgesInput);

                    if (finalRows == 0) {
                        continue;
                    }
                    if (finalCol == 0) {
                        continue;
                    }
                    if (finalEdges == 0) {
                        continue;
                    }

                    rows = finalRows;
                    columns = finalCol;
                    maxConnections = finalEdges;
                    genWalls = wallsGenerated;
                    return 7;
                }
                if (colActive && !clickedOnCol) {
                    finalColInput = colInput;  //save the final input
                    colActive = false;
                    std::cout << "Columns entered: " << finalColInput << std::endl;  // Debug output
                }
                if (rowActive && !clickedOnRow) {
                    finalRowInput = rowInput;  //save the final input
                    rowActive = false;
                    std::cout << "Rows entered: " << finalRowInput << std::endl;  // Debug output
                }
                if (edgesActive && !clickedOnEdges) {
                    finalEdgesInput = edgesInput;  //save the final input
                    edgesActive = false;
                    std::cout << "Max edges entered: " << finalEdgesInput << std::endl;  // Debug output
                }
                colActive = columnRect.getGlobalBounds().contains(mousePos.x, mousePos.y);
                rowActive = rowRect.getGlobalBounds().contains(mousePos.x, mousePos.y);
                edgesActive = edgesRect.getGlobalBounds().contains(mousePos.x, mousePos.y);
            } else if (event.type == sf::Event::TextEntered && (colActive || rowActive || edgesActive)) {
                std::string* currentInput = nullptr;
                if (colActive) {
                    currentInput = &colInput;
                } else if (rowActive) {
                    currentInput = &rowInput;
                } else if (edgesActive) {
                    currentInput = &edgesInput;
                }

                if (currentInput) { //can't be null
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b' && !currentInput->empty()) {  //handle backspace
                        currentInput->pop_back();
                    } else if (std::isdigit(enteredChar)) {
                        if (edgesActive) {
                            //additional checks for edges input
                            if (*currentInput == "") {
                                int num = enteredChar - '0';
                                if (num >= 0 && num <= 8) {
                                    currentInput->push_back(enteredChar);
                                }
                            }
                        } else {
                            currentInput->push_back(enteredChar);
                        }
                    }
                }
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (colActive) {
                        finalColInput = colInput;  //save the final input
                        colActive = false;
                        std::cout << "Columns entered: " << finalColInput << std::endl;
                    } else if (rowActive) {
                        finalRowInput = rowInput;  //save the final input
                        rowActive = false;
                        std::cout << "Rows entered: " << finalRowInput << std::endl;
                    } else if (edgesActive) {
                        finalEdgesInput = edgesInput;  //save the final input
                        edgesActive = false;
                        std::cout << "Max edges entered: " << finalEdgesInput << std::endl;
                    }
                }
            }
            if (event.type == sf::Event::Closed) {
                intro.close();
                return -1;
            }

        }

        if (cursorClock.getElapsedTime() >= blinkDuration) {
            showCursor = !showCursor;
            cursorClock.restart();
        }

        // Update and display input with cursor
        std::string colDisplay = colInput + (showCursor && colActive ? "|" : "");
        std::string rowDisplay = rowInput + (showCursor && rowActive ? "|" : "");
        std::string edgesDisplay = edgesInput + (showCursor && edgesActive ? "|" : "");
        userEdges.setString(edgesDisplay);
        userCol.setString(colDisplay);
        userRow.setString(rowDisplay);

        intro.clear(sf::Color::White);
        intro.draw(rowRect);
        intro.draw(columnRect);
        intro.draw(edgesRect);
        intro.draw(welcome);
        intro.draw(entercolumns);
        intro.draw(userCol);
        intro.draw(enterrows);
        intro.draw(userRow);
        intro.draw(enterMaxEdges);
        intro.draw(userEdges);
        intro.draw(yesButton);
        intro.draw(noButton);
        intro.draw(wallsTxt);
        intro.draw(yesText);
        intro.draw(noText);
        intro.draw(coverSprite);
        intro.draw(startRect);
        intro.draw(startText);
        intro.display();
    }
    return 0;
}

// Simulations

void generateSimulationWindow(nodeMap& maze, int algorithmCode) {
    //Instantiate algorithm pointers for algorithmic operations
    BFS* algorithm1;
    DFS* algorithm2;
    if (algorithmCode == 1)
        algorithm1 = new BFS(maze);
    if (algorithmCode == 2)
        algorithm2 = new DFS(maze);



    sf::RenderWindow simulation(sf::VideoMode(1600, 900), "Simulation");

    // Snap to start node
    sf::View view(sf::Vector2f(maze.getStartNode()->getCenterX(),maze.getStartNode()->getCenterY()),
                  sf::Vector2f(1600.f, 900.f));
    simulation.setView(view);
    int currentX = maze.getStartNode()->getX();
    int currentY = maze.getStartNode()->getY();

    // run the program as long as the window is open
    while (simulation.isOpen())
    {
        simulation.clear(sf::Color::White);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        while (simulation.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                simulation.close();
            }


        }


        //run an algorithm step, get the algorithm's current node's position
        if (algorithmCode == 1){
            std::unique_ptr<nodeMap::node>* currentNode = algorithm1->traverseN(1, maze, simulation);
            if (currentNode->get()->goalNode){
                std::cout << currentNode->get()->getX()<< std::endl;
                std::cout << maze.goalX;
                maze.map[currentNode->get()->getY()][currentNode->get()->getX()]->circle.setFillColor(sf::Color::Green);
            }
            sleep(1);
            view.setCenter(currentNode->get()->getCenterX(), currentNode->get()->getCenterY());
            simulation.setView(view);
        }

        if (algorithmCode == 2)
            algorithm2->traverseN(1, maze, simulation);

        // draw only the fraction that is visible/close to visible for perf (currently just draws everything)
        maze.drawSection(simulation, currentX, currentY);

        simulation.display();

    }
    delete algorithm1;
    delete algorithm2;
};
//
// GUI
//

#include "gui.hpp"

int generateIntroWindow() {
    sf::RenderWindow intro(sf::VideoMode(800, 600), "Intro Window");

    // run while the intro window is open
    while (intro.isOpen())
    {
        // check for any events
        sf::Event event{};
        while (intro.pollEvent(event))
        {
            // close the window if the exit button is clicked
            if (event.type == sf::Event::Closed)
                intro.close();
        }
    }

    return 0;
}
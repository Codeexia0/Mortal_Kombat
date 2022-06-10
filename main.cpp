#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>s


int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Clock clock;

    while (window.isOpen()) {

        sf::Time elapsed = clock.restart();

        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the winow
            if (event.type == sf::Event::Closed)
                window.close();

        }

        window.clear(sf::Color::Black);

        // draw everything here...

        // end the current frame
        window.display();
    }

    return 0;
}

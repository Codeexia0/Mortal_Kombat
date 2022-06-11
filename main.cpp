#include<SFML/Graphics.hpp>
#include<iostream>
#include"Global.h"
#include"Animation.h"
#include "Player.h"
using namespace std;

int main()
{
    srand(time(NULL));
    window = new sf::RenderWindow(sf::VideoMode(800, 350), "Mortal Kombat 13+");
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);

    Player player(Vector2f(200, 230));



    sf::Clock deltaClock;

    while (window->isOpen())
    {
        float deltaTime = deltaClock.restart().asSeconds();
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            //If key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::D:
                    break;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                default: break;
                }
            }

        }


        //Clear window and draw new
        window->clear( sf::Color(77,77,77));

        player.update(deltaTime);
        player.draw();



        window->display();
    }
    return 0;
}

#include<SFML/Graphics.hpp>
#include<iostream>
#include "Global.h"
#include"Animation.h"
using namespace std;

int main()
{

    srand(time(NULL));
    window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Game");
    window->setFramerateLimit(60);
    window->setVerticalSyncEnabled(true);
    window->setKeyRepeatEnabled(false);


    sf::Font font;
    if (!font.loadFromFile("tahoma.ttf"))
    {
        cout << " load font error\n";
    }


    Animation animation("test", "subzero-idle.png", Vector2i(48, 111), 12,0.05f);
    Animation punch("test2", "subzero-punch1.png", Vector2i(80, 109), 3, 0.07f,false);

    animation.setPosition(Vector2f(200, 200));
    punch.setPosition(Vector2f(200, 200));

    bool isPunch = false;

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
                    isPunch = true;
                    punch.replay();
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


        if (isPunch) {
            punch.play(deltaTime);
            punch.draw();
            if (punch.isEnd()) {
                isPunch = false;
            }
        }
        else {
            animation.play(deltaTime);
            animation.draw();
        }


        window->display();
    }
    return 0;
}

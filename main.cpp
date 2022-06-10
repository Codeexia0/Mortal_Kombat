#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);//Activating vertical synchronization will limit the number of frames displayed to the refresh rate of the monitor(limit the framerate to a good value)
    window.setKeyRepeatEnabled(false);// If it is disabled, you will only get a single event when the key is pressed.

    sf::Texture texture;
    if (!(texture.loadFromFile("subzero-idle.png")))
    {
        cout << "Could Not Load File.." << endl;
    }
    sf::Sprite _sprite;
    _sprite.setTexture(texture);

    _sprite.setTextureRect(sf::IntRect(48, 0, 48, 111));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

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
        window.clear( sf::Color(77,77,77));
        window.draw(_sprite);
        window.display();
    }
    return 0;
}

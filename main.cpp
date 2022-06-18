#include<SFML/Graphics.hpp>
#include<iostream>
#include"Global.h"
#include"Animation.h"
#include "Player.h"
#include "SoundEffects.h"
using namespace std;

int main()
{
    srand(time(NULL));
    window = new sf::RenderWindow(sf::VideoMode(800, 350), "Mortal Kombat 13+");
    window->setFramerateLimit(60); //the window will use a small delay after each call to display() to ensure that the current frame lasted long enough to match the framerate limit
    window->setVerticalSyncEnabled(true); //to avoid some visual artifacts
    window->setKeyRepeatEnabled(false); //to get a single event when the key is pressed

    font = new Font();
    if (!font->loadFromFile("tahoma.ttf"))
    {
        cout << " load font error\n";
    }

    bool gameOver = false;
    Text koText;
    koText.setFont(*font);
    koText.setCharacterSize(60);
    koText.setPosition(800/2-60, 80);
    koText.setFillColor(Color::Red);
    koText.setString("K.O");


    Animation backgroundAnimation("background", "bg.png", Vector2i(799, 233), 3, 0.07f);
    backgroundAnimation.setScale(Vector2f(1.0f, 1.5f));

    Player player(Vector2f(200, 180));
    Player player2(Vector2f(600, 180),true);

    player.setEnemy(&player2);//choosing oppenent for each other so they can hit each other and take damage
    player2.setEnemy(&player);

    MSoundEffect startSound("round1.wav");
    MSoundEffect koSound("fatality.wav");
    startSound.play();


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
                player.onKeyPress(event.key.code);//movement
                player2.onKeyPress(event.key.code);
            }
            if (event.type == sf::Event::KeyReleased) {
                player.onKeyRelease(event.key.code);
                player2.onKeyRelease(event.key.code);
            }
        }


        //Clear window and draw new
        window->clear( sf::Color(77,77,77));


        backgroundAnimation.play(deltaTime);//animating the background as well
        backgroundAnimation.draw();


        player.update(deltaTime); //status update
        player2.update(deltaTime);


        player.draw();
        player2.draw();

        if (!gameOver &&( player.getHealth() <= 0 || player2.getHealth() <= 0)) {
            gameOver = true;
            koSound.play();
        }

        if (gameOver) {
            window->draw(koText);
        }

        window->display();
    }
    return 0;
}

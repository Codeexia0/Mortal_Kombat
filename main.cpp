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

    font = new Font();
    if (!font->loadFromFile("assets/tahoma.ttf"))
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


    Animation backgroundAnimation("background", "assets/bg.png", Vector2i(799, 233), 3, 0.07f);
    backgroundAnimation.setScale(Vector2f(1.0f, 1.5f));

    Player player(Vector2f(200, 180));
    Player player2(Vector2f(600, 180),true);

    player.setEnemy(&player2);
    player2.setEnemy(&player);


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
                player.onKeyPress(event.key.code);
                player2.onKeyPress(event.key.code);
            }
            if (event.type == sf::Event::KeyReleased) {
                player.onKeyRelease(event.key.code);
                player2.onKeyRelease(event.key.code);
            }
        }


        //Clear window and draw new
        window->clear( sf::Color(77,77,77));


        backgroundAnimation.play(deltaTime);
        backgroundAnimation.draw();


        player.update(deltaTime);
        player2.update(deltaTime);


        player.draw();
        player2.draw();

        if (!gameOver &&( player.getHealth() <= 0 || player2.getHealth() <= 0)) {
            gameOver = true;
        }

        if (gameOver) {
            window->draw(koText);
        }

        window->display();
    }
    return 0;
}

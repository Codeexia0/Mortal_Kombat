#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include "Global.h"

using namespace std;
using namespace sf;

class Animation {

    string id;
    Vector2i size;
    Texture texture;
    Sprite sprite;

    float playTime = 0;
    float delayTime = 0;
    int currentFrame = 0;
    int maxFrame = 0;

    bool loop = false;
public:

    Animation(string id,string filePath,Vector2i size,int maxFrame,float delayTime= 0.1f,bool loop = true) {

        this->loop = loop;
        this->maxFrame = maxFrame;
        this->id = id;
        this->size = size;
        this->delayTime = delayTime;
        this->playTime = delayTime;
        if (!(texture.loadFromFile(filePath)))
        {
            cout << "Could Not Load File.." << endl;
        }
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    }

    void play(float deltaTime) {

        if (currentFrame >= maxFrame) {
            return;
        }

        this->playTime -= deltaTime;
        if (playTime <= 0) {
            this->playTime = this->delayTime;
            currentFrame++;
            if (currentFrame >= maxFrame && loop) {
                currentFrame = 0;
            }
        }

        sprite.setTextureRect(sf::IntRect(currentFrame * size.x, 0, size.x, size.y));
    }

    void replay() {
        currentFrame = 0;
    }
    bool isEnd() {
        return currentFrame >= maxFrame;
    }

    void setPosition(Vector2f pos) {
        sprite.setPosition(pos);
    }

    void setScale(Vector2f scale) {
        sprite.setScale(scale);
    }

    void draw() {
        window->draw(sprite);
    }

};

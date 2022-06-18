#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include "Global.h"

using namespace std;
using namespace sf;

class Animation {
private:
    string id;
    Vector2i size;
    Texture texture;
    Sprite sprite;

    float playTime = 0; //setting them to 0 so we dont get any garbage results while functioning
    float delayTime = 0;
    int currentFrame = 0;
    int maxFrame = 0;

    bool loop = false;
public:

    Animation(string id,string filePath,Vector2i size,int maxFrame,float delayTime= 0.1f,bool loop = true) {

        this->loop = loop; //this-> is pointer used get access to the loop from private class(easier to acces)
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
            sprite.setTextureRect(sf::IntRect((maxFrame-1) * size.x, 0, size.x, size.y));
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

    int getFrame() {
        return currentFrame;
    }

    FloatRect getRect() { //Construct the rectangle from its coordinates (for actions)
        FloatRect rect = sprite.getGlobalBounds();
        rect.left += 30;
        rect.top += 30;
        rect.width -= 30;
        rect.height -= 30;
        return rect;
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

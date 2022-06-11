#pragma once
#include "Animation.h"
#include<map>

class Player {

    string currentAnimationId;
    map<string, Animation*> animations;

    Vector2f position;

    enum Action //user-defined data type that can be assigned some limited values
    {
        idle,
        punch
    };

    Action action;

public:
    Player(Vector2f position,bool flip = false) {
        this->position = position;

        Animation* idle = new Animation("idle", "subzero-idle.png", Vector2i(48, 111), 12, 0.05f);
        Animation* punch = new Animation("punch", "subzero-punch1.png", Vector2i(80, 109), 3, 0.07f, false);
        animations.insert(pair<string, Animation*>("idle", idle));
        animations.insert(pair<string, Animation*>("punch", punch));

        action = Action::idle;
    }

    void update(float deltaTime) {
        /*map<string, Animation*>::iterator itr;
        for (itr = animations.begin(); itr != animations.end(); itr++) {
            itr->second->setPosition(position);
            itr->second->play(deltaTime);
        }*/

        switch (action)
        {
        case Player::idle:
            animations.at("idle")->setPosition(position);
            animations.at("idle")->play(deltaTime);
            break;
        case Player::punch:
            animations.at("punch")->setPosition(position);
            animations.at("punch")->play(deltaTime);
            break;
        }

    }

    void draw() {

        switch (action)
        {
        case Player::idle:
            animations.at("idle")->draw();
            break;
        case Player::punch:
            animations.at("punch")->draw();
            break;
        }

    }

};

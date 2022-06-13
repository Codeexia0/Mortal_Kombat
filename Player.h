#pragma once
#include "Animation.h"
#include<map>

class Player {

    string currentAnimationId;
    map<string, Animation*> animations;

    Vector2f position;
    Vector2f velocity;

    enum Action
    {
        idle,
        walk,
        punch
    };

    Action action;

    float speed = 5;
    bool isPlayer2 = false;

    Player* enemy;

public:
    Player(Vector2f position,bool isPlayer2 = false) {
        this->position = position;
        velocity = Vector2f(0, 0);
        action = Action::idle;
        this->isPlayer2 = isPlayer2;


        if (!isPlayer2) {
            Animation* idle = new Animation("idle", "assets/subzero-idle.png", Vector2i(48, 111), 12, 0.05f);
            Animation* walk = new Animation("walk", "assets/subzero-walk.png", Vector2i(64, 109), 9, 0.05f);
            Animation* punch = new Animation("punch", "assets/subzero-punch1.png", Vector2i(80, 109), 3, 0.07f, false);
            animations.insert(pair<string, Animation*>("idle", idle));
            animations.insert(pair<string, Animation*>("walk", walk));
            animations.insert(pair<string, Animation*>("punch", punch));
        }
        else {
            Animation* idle = new Animation("idle", "assets/sco-idle.png", Vector2i(64, 111), 7, 0.07f);
            Animation* walk = new Animation("walk", "assets/subzero-walk.png", Vector2i(64, 109), 9, 0.05f);
            Animation* punch = new Animation("punch", "assets/subzero-punch1.png", Vector2i(80, 109), 3, 0.07f, false);

            idle->setScale(Vector2f(-1, 1));
            walk->setScale(Vector2f(-1, 1));
            punch->setScale(Vector2f(-1, 1));

            animations.insert(pair<string, Animation*>("idle", idle));
            animations.insert(pair<string, Animation*>("walk", walk));
            animations.insert(pair<string, Animation*>("punch", punch));
        }
    }

    void setEnemy(Player* enemy) {
        this->enemy = enemy;
    }

    void onKeyPress(Keyboard::Key key) {

        if (!isPlayer2) {
            switch (key)
            {
            case sf::Keyboard::A:
                velocity.x = -speed;
                action = walk;
                break;
            case sf::Keyboard::D:
                velocity.x = speed;
                action = walk;
                break;
            case sf::Keyboard::F:
                action = punch;
                animations.at("punch")->replay();
                break;
            }
        }

    }

    void onKeyRelease(Keyboard::Key key) {

        if (!isPlayer2) {
            switch (key)
            {
            case sf::Keyboard::A:
                if (velocity.x == -speed) {
                    velocity.x = 0;
                    action = idle;
                }
                break;
            case sf::Keyboard::D:
                if (velocity.x == speed) {
                    velocity.x = 0;
                    action = idle;
                }
                break;
            }
        }

    }



    void update(float deltaTime) {

        if (!isPlayer2) {
            if (velocity.x > 0 && distance(position.x, position.y, enemy->getPos().x, enemy->getPos().y) >= 120) {
                position += velocity;
            }
            else if (velocity.x < 0 ) {
                position += velocity;
                if (position.x <= 10) {
                    position.x = 0;
                }
            }
        }
        else {
        }

        switch (action)
        {
        case Action::idle:
            animations.at("idle")->play(deltaTime);
            break;
        case Action::walk:
            animations.at("walk")->play(deltaTime);
            break;
        case Action::punch:
            animations.at("punch")->play(deltaTime);

            if (animations.at("punch")->isEnd()) {
                action = Action::idle;
            }

            break;
        }

    }


    void checkDistance() {

    }



    void draw() {

        switch (action)
        {
        case Action::idle:
            animations.at("idle")->setPosition(position);

            animations.at("idle")->draw();
            break;
        case Action::walk:
            animations.at("walk")->setPosition(position);
            animations.at("walk")->draw();
            break;
        case Action::punch:
            animations.at("punch")->setPosition(position);
            animations.at("punch")->draw();
            break;
        }

    }


    Vector2f getPos() {
        return position;
    }



};

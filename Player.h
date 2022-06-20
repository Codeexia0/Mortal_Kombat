#pragma once
#include "Animation.h"
#include "SoundEffects.h"
#include<map>

class Player {
    string currentAnimationId;//name of the animations
    map<string, Animation*> animations; //containers that store key-value pair elements in sorted form

    Vector2f position; //(float x, float y)
    Vector2f velocity; //(speed in x and y direction)

    enum Action //no typedef required
    {
        idle,
        walk,
        punch,
        kick,
        hit,
        death
    };

    Action action;

    float speed = 5;
    bool isPlayer2 = false;

    Player* enemy;
    int health = 30; //health of players

    bool resetHit = true;
    RectangleShape* healthbar; //red rectangle
    RectangleShape* healthbarBG; //grey rectangle


    MSoundEffect* kickSound;
    MSoundEffect* punchSound;

public:
    Player(Vector2f position,bool isPlayer2 = false) {
        this->position = position;
        velocity = Vector2f(0, 0);
        action = Action::idle; //start with idle
        this->isPlayer2 = isPlayer2;

        kickSound = new MSoundEffect("kick.ogg");
        punchSound = new MSoundEffect("punch.ogg");


        if (!isPlayer2) { //if isPLayer is false
            //"new"(smart pointers) are used to make sure that an object is deleted if it is no longer used (referenced)
            Animation* idle = new Animation("idle", "subzero-idle.png", Vector2i(48, 111), 12, 0.05f);//bool loop is true
            Animation* walk = new Animation("walk", "subzero-walk.png", Vector2i(64, 109), 9, 0.05f);
            Animation* punch = new Animation("punch", "subzero-punch1.png", Vector2i(80, 109), 3, 0.07f, false);
            Animation* hit = new Animation("hit", "subzero-hit.png", Vector2i(64, 111), 3, 0.07f, false);
            Animation* kick = new Animation("kick", "subzero-kick.png", Vector2i(80, 109), 4, 0.07f, false);
            Animation* death = new Animation("death", "subzero-death.png", Vector2i(80, 109), 6, 0.07f, false);

            idle->setScale(Vector2f(1.5, 1.5)); //(x,y)
            walk->setScale(Vector2f(1.5, 1.5));
            punch->setScale(Vector2f(1.5, 1.5));
            hit->setScale(Vector2f(1.5, 1.5));
            kick->setScale(Vector2f(1.5, 1.5));
            death->setScale(Vector2f(1.5, 1.5));

            animations.insert(pair<string, Animation*>("idle", idle)); //using map<> we join key-value pair elements in sorted form
            animations.insert(pair<string, Animation*>("walk", walk));
            animations.insert(pair<string, Animation*>("punch", punch));
            animations.insert(pair<string, Animation*>("hit", hit));
            animations.insert(pair<string, Animation*>("kick", kick));
            animations.insert(pair<string, Animation*>("death", death));

            healthbar = new RectangleShape();//creating rectangle shape for health
            healthbar->setPosition(Vector2f(0, 0));
            healthbar->setSize(Vector2f(health * 10, 20));
            healthbar->setFillColor(Color::Red);
            healthbarBG = new RectangleShape();
            healthbarBG->setPosition(Vector2f(0, 0));
            healthbarBG->setSize(Vector2f(health * 10, 20));
            healthbarBG->setFillColor(Color(233,233,233, 150));


        }
        else {
            Animation* idle = new Animation("idle", "sco-idle.png", Vector2i(64, 111), 7, 0.07f);
            Animation* walk = new Animation("walk", "sco-walk.png", Vector2i(64, 109), 9, 0.05f);
            Animation* punch = new Animation("punch", "sco-punch1.png", Vector2i(80, 109), 3, 0.07f, false);
            Animation* hit = new Animation("hit", "sco-hit.png", Vector2i(64, 111), 3, 0.07f, false);
            Animation* kick = new Animation("kick", "sco-kick.png", Vector2i(80, 109), 4, 0.07f, false);
            Animation* death = new Animation("death", "sco-death.png", Vector2i(80, 109), 6, 0.07f, false);


            idle->setScale(Vector2f(-1.5, 1.5));
            walk->setScale(Vector2f(-1.5, 1.5));
            punch->setScale(Vector2f(-1.5, 1.5));
            hit->setScale(Vector2f(-1.5, 1.5));
            kick->setScale(Vector2f(-1.5, 1.5));
            death->setScale(Vector2f(-1.5, 1.5));

            animations.insert(pair<string, Animation*>("idle", idle));
            animations.insert(pair<string, Animation*>("walk", walk));
            animations.insert(pair<string, Animation*>("punch", punch));
            animations.insert(pair<string, Animation*>("hit", hit));
            animations.insert(pair<string, Animation*>("kick", kick));
            animations.insert(pair<string, Animation*>("death", death));

            healthbar = new RectangleShape();
            healthbar->setPosition(Vector2f(800, 0));
            healthbar->setSize(Vector2f(health * 10, 20));
            healthbar->setScale(Vector2f(-1, 1));
            healthbar->setFillColor(Color::Red);
            healthbarBG = new RectangleShape();
            healthbarBG->setPosition(Vector2f(800, 0));
            healthbarBG->setSize(Vector2f(health * 10, 20));
            healthbarBG->setScale(Vector2f(-1, 1));
            healthbarBG->setFillColor(Color(233, 233, 233, 150));
        }
    }

    void setEnemy(Player* enemy) {
        this->enemy = enemy;
    }

    void onKeyPress(Keyboard::Key key) { //actions to happen when the required key is pressed

        if (health <= 0) {
            return;
        }

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
            case sf::Keyboard::W:
                if (action == Action::hit || action == punch) {
                    return;
                }
                action = punch;
                animations.at("punch")->replay();
                break;
            case sf::Keyboard::S:
                if (action == Action::hit || action == kick) {
                    return;
                }
                action = kick;
                animations.at("kick")->replay();
                break;
            }
        }
        else {
            switch (key)
            {
            case sf::Keyboard::Left:
                velocity.x = -speed;
                action = walk;
                break;
            case sf::Keyboard::Right:
                velocity.x = speed;
                action = walk;
                break;
            case sf::Keyboard::Up:
                if (action == Action::hit || action == punch) {
                    return;
                }
                action = punch;
                animations.at("punch")->replay();
                break;
            case sf::Keyboard::Down:
                if (action == Action::hit || action == kick) {
                    return;
                }
                action = kick;
                animations.at("kick")->replay();
                break;
            }
        }

    }

    void onKeyRelease(Keyboard::Key key) { //to stop movement when the key is released
        if (health <= 0) {
            return;
        }

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
        else {
            switch (key)
            {
            case sf::Keyboard::Left:
                if (velocity.x == -speed) {
                    velocity.x = 0;
                    action = idle;
                }
                break;
            case sf::Keyboard::Right:
                if (velocity.x == speed) {
                    velocity.x = 0;
                    action = idle;
                }
                break;
            }
        }

    }

    void movement() {
        if (health <= 0) { //"There is nothing after death and death itself is nothing."(~##Senace the Younger##~)
            return;
        }

        if (action == hit) {
            return;
        }
        float touchDistance = 160; //perfect touching distance for players when they come together
        if (!isPlayer2) {
            if (velocity.x > 0 && distance(position.x, position.y, enemy->getPos().x, enemy->getPos().y) >= touchDistance) { //for subzero checking the distance so they don't go over each other
                position += velocity;}
            else if (velocity.x < 0) {
                position += velocity;
                if (position.x <= 10) {
                    position.x = 0;
                }
            }
        }
        else {
            if (velocity.x > 0 ) {//setting boundaries
                position += velocity;
                if (position.x >= 800) {//distance from left to right is 800
                    position.x = 800;
                }
            }
            else if (velocity.x < 0 && distance(position.x, position.y, enemy->getPos().x, enemy->getPos().y) >= touchDistance) { //for scorpion(player on the right)
                position += velocity;

            }
        }
    }


    void update(float deltaTime) {

        movement();

        switch (action)
        {
        case Action::idle:
            resetHit = true;
            animations.at("idle")->play(deltaTime); //setting update of actions like which action should play when it is asked
            break;
        case Action::walk:
            animations.at("walk")->play(deltaTime);
            break;
        case Action::death:
            if (!isPlayer2) {
                position.x -= 3; //subzero slides away when he dies
            }
            else {
                position.x += 3; //for scorpion
            }
            animations.at("death")->play(deltaTime); //falling to the ground
            break;
        case Action::punch:
            animations.at("punch")->play(deltaTime);

            if (animations.at("punch")->getFrame() == 2 && isIntersects(getRect(),enemy->getRect())) {//checking if the punch touches the oppenent so it can take damage
                enemy->setAction(Action::hit,Action::punch);//if yes then it can be count as a hit
            }   //First part(Action::hit) means that second player is being hit(true) and second part(Action::punch) means that form of hit is punch

            if (animations.at("punch")->isEnd()) { //after punch it comes back to its idle position so it doesnt just stay in punch position
                action = Action::idle;
            }
            break;
        case Action::kick:
            animations.at("kick")->play(deltaTime);

            if (animations.at("kick")->getFrame() == 2 && isIntersects(getRect(), enemy->getRect())) {
                enemy->setAction(Action::hit,Action::kick);
            }

            if (animations.at("kick")->isEnd()) {
                action = Action::idle;
            }
            break;
        case Action::hit:
            animations.at("hit")->play(deltaTime);//animation of being hit
            if (animations.at("hit")->isEnd()) { //after being hit player returns to his idle postion(like nothing happened)
                action = Action::idle;
            }
            break;
        }

    }

    void draw() {
        window->draw(*healthbarBG);
        window->draw(*healthbar);

        switch (action)
        {
        case Action::idle: //drawing actions
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
        case Action::kick:
            animations.at("kick")->setPosition(position);
            animations.at("kick")->draw();
            break;
        case Action::hit:
            animations.at("hit")->setPosition(position);
            animations.at("hit")->draw();
            break;
        case Action::death:
            animations.at("death")->setPosition(position);
            animations.at("death")->draw();
            break;
        }

    }


    Vector2f getPos() {
        return position;
    }

    int getHealth() {
        return health;
    }

    void setAction(Action action,Action fromAction) { //looking for countable hits
        if (health <= 0) {
            return;
        }
        this->action = action;
        switch (action)
        {
        case Player::idle:
            break;
        case Player::walk:
            break;
        case Player::punch:
            animations.at("punch")->replay();
            break;
        case Player::kick:
            animations.at("kick")->replay();
            break;
        case Player::hit: //if there is a hit
            if (resetHit) {
                switch (fromAction)
                {
                case Player::punch://if it is a punch
                    punchSound->play();//punch sound is being played
                    health -= 2; //losing 2 unit of health when punched(hand)
                    break;
                case Player::kick:
                    kickSound->play();
                    health -= 1; //losing 1 unit of health when kicked(leg)
                    break;
                }
            }
            healthbar->setSize(Vector2f(health * 10, 20)); //we set health to 30 so its size is 300(x) to 20(y)
            resetHit = false;

            if (health <= 0) {
                animations.at("death")->replay(); //play death scene when health is equal or small than 0>=(1-2=-1)
                this->action = death;
            }
            else {
                animations.at("hit")->replay();
            }
            break;
        case Player::death:
            break;
        default:
            break;
        }
    }

    FloatRect getRect() { //rectangle of actions that are used for checking touching

        switch (action)
        {
        case Action::idle:
            return animations.at("idle")->getRect();
            break;
        case Action::walk:
            return animations.at("walk")->getRect();
            break;
        case Action::punch:
            return animations.at("punch")->getRect();
            break;
        case Action::kick:
            return animations.at("kick")->getRect();
            break;
        case Action::hit:
            return animations.at("hit")->getRect();
            break;
        case Action::death:
            return animations.at("death")->getRect();
            break;
        }
    }
};

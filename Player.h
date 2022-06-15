#pragma once
#include "Animation.h"
#include "SoundEffects.h"
#include<map>

class Player {
    string currentAnimationId;
    map<string, Animation*> animations; //containers that store key-value pair elements in sorted form

    Vector2f position; //(float x, float y)
    Vector2f velocity;

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
    int health = 30;

    bool resetHit = true;
    RectangleShape* healthbar;
    RectangleShape* healthbarBG;


    MSoundEffect* kickSound;
    MSoundEffect* punchSound;

public:
    Player(Vector2f position,bool isPlayer2 = false) {
        this->position = position;
        velocity = Vector2f(0, 0);
        action = Action::idle;
        this->isPlayer2 = isPlayer2;

        kickSound = new MSoundEffect("kick.ogg");
        punchSound = new MSoundEffect("punch.ogg");


        if (!isPlayer2) {
            Animation* idle = new Animation("idle", "subzero-idle.png", Vector2i(48, 111), 12, 0.05f);
            Animation* walk = new Animation("walk", "subzero-walk.png", Vector2i(64, 109), 9, 0.05f);
            Animation* punch = new Animation("punch", "subzero-punch1.png", Vector2i(80, 109), 3, 0.07f, false);
            Animation* hit = new Animation("hit", "subzero-hit.png", Vector2i(64, 111), 3, 0.07f, false);
            Animation* kick = new Animation("kick", "subzero-kick.png", Vector2i(80, 109), 4, 0.07f, false);
            Animation* death = new Animation("death", "subzero-death.png", Vector2i(80, 109), 6, 0.07f, false);

            idle->setScale(Vector2f(1.5, 1.5));
            walk->setScale(Vector2f(1.5, 1.5));
            punch->setScale(Vector2f(1.5, 1.5));
            hit->setScale(Vector2f(1.5, 1.5));
            kick->setScale(Vector2f(1.5, 1.5));
            death->setScale(Vector2f(1.5, 1.5));

            animations.insert(pair<string, Animation*>("idle", idle));
            animations.insert(pair<string, Animation*>("walk", walk));
            animations.insert(pair<string, Animation*>("punch", punch));
            animations.insert(pair<string, Animation*>("hit", hit));
            animations.insert(pair<string, Animation*>("kick", kick));
            animations.insert(pair<string, Animation*>("death", death));

            healthbar = new RectangleShape();
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

    void onKeyPress(Keyboard::Key key) {

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

    void onKeyRelease(Keyboard::Key key) {
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
        if (health <= 0) {
            return;
        }

        if (action == hit) {
            return;
        }
        float touchDistance = 160;
        if (!isPlayer2) {
            if (velocity.x > 0 && distance(position.x, position.y, enemy->getPos().x, enemy->getPos().y) >= touchDistance) {
                position += velocity;
            }
            else if (velocity.x < 0) {
                position += velocity;
                if (position.x <= 10) {
                    position.x = 0;
                }
            }
        }
        else {
            if (velocity.x > 0 ) {
                position += velocity;
                if (position.x >= 800) {
                    position.x = 800;
                }
            }
            else if (velocity.x < 0 && distance(position.x, position.y, enemy->getPos().x, enemy->getPos().y) >= touchDistance) {
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
            animations.at("idle")->play(deltaTime);
            break;
        case Action::walk:
            animations.at("walk")->play(deltaTime);
            break;
        case Action::death:
            if (!isPlayer2) {
                position.x -= 3;
            }
            else {
                position.x += 3;
            }
            animations.at("death")->play(deltaTime);
            break;
        case Action::punch:
            animations.at("punch")->play(deltaTime);

            if (animations.at("punch")->getFrame() == 2 && isIntersects(getRect(),enemy->getRect())) {
                enemy->setAction(Action::hit,Action::punch);
            }

            if (animations.at("punch")->isEnd()) {
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
            animations.at("hit")->play(deltaTime);
            if (animations.at("hit")->isEnd()) {
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

    void setAction(Action action,Action fromAction) {
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
        case Player::hit:
            if (resetHit) {
                switch (fromAction)
                {
                case Player::punch:
                    punchSound->play();
                    health -= 2;
                    break;
                case Player::kick:
                    kickSound->play();
                    health -= 1;
                    break;
                }
            }
            healthbar->setSize(Vector2f(health * 10, 20));
            resetHit = false;

            if (health <= 0) {
                animations.at("death")->replay();
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

    FloatRect getRect() {

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

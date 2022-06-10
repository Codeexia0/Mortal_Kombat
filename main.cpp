#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class AnimatedSprite : public sf::Sprite {
public:
    AnimatedSprite(const int fps,const std::string& path) : fps_(fps) //make an initializer list for fps_
    {

        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << path << std::endl;
        }

        setTexture(texture_);
        setTextureRect(sf::IntRect(48, 0, 48, 111));
    }

    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }



    void animate(const sf::Time &elapsed){
        bouncce();
        float dt = elapsed.asSeconds();

        t_ = t_ + dt;

        if(t_ > 1.0/fps_){
            fragments_index++;
            t_ = 0.0;
        }

        if(fragments_index == running_frames.size()){
            fragments_index = 0;
        }


        setTextureRect(running_frames[fragments_index]);

        move(x_speed_*dt,y_speed_*dt);
    }

    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }

    void add_animation_frame(const sf::IntRect& frame){
        running_frames.emplace_back(frame);


    }

private:
    sf::Sprite sprite;
    sf::Texture texture_;
    sf::Vector2i size;


    float playTime = 0;
    float delayTime = 0;
    int currentFrame = 0;
    int maxFrame = 0;

    int fps_;
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;
    float t_ = 0.0;

    unsigned int fragments_index = 0;
    std::vector<sf::IntRect> running_frames;



    void bouncce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();

        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }

        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
        }

        if(rectangle_bounds.left <= l_bound_ ){
           x_speed_ = abs(x_speed_);
        }

        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
        }
    }


};

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(300, 200), "Game");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);//Activating vertical synchronization will limit the number of frames displayed to the refresh rate of the monitor(limit the framerate to a good value)
    window.setKeyRepeatEnabled(false);// If it is disabled, you will only get a single event when the key is pressed.

    AnimatedSprite hero(10, "subzero-idle.png");



    sf::Clock clock;
    while (window.isOpen())
    {


            sf::Time elapsed = clock.restart();

            sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //If key is pressed
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();




        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
           hero.animate(elapsed);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
           hero.animate(elapsed);
        }


            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                default: break;
                }
            }

        }
        sf::Texture texture;
        if (!texture.loadFromFile("014.png")) {
            std::cerr << "Could not load texture" << std::endl;
            return 1;
        }




        texture.setRepeated(true);
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, 300, 200));



        //Clear window and draw new
        window.clear( sf::Color(77,77,77));
//        window.draw(_sprite);
        window.draw(sprite);
        window.draw(hero);

        window.display();

    }
    return 0;
}

#pragma once
#include <SFML/Audio.hpp>


class MSoundEffect {

    sf::SoundBuffer buffer;//This class encapsulates the audio data
    sf::Sound sound;

public:
    MSoundEffect(std::string path) {
        if (!buffer.loadFromFile(path)) {
            return ;
        }
        sound.setBuffer(buffer);
    }
    ~MSoundEffect(){}

    void play() {
        sound.play();
    }

};

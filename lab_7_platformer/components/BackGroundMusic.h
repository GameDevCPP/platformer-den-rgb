
#ifndef GAMES_ENGINEERING_BACKGROUNDMUSIC_H
#define GAMES_ENGINEERING_BACKGROUNDMUSIC_H


#include <iostream>
#include "SFML/Audio/Music.hpp"

class BackGroundMusic {
public:
    static void playAudio(std::string audioFile) {


        if (!music.openFromFile(audioFile)){
            std::cout << "Error..." << std::endl;
        }
        else{
            music.setLoop(true);
            music.setVolume(20);
            music.play();
        }
    }
private:
    static sf::Music music;
};
sf::Music BackGroundMusic::music;

#endif //GAMES_ENGINEERING_BACKGROUNDMUSIC_H


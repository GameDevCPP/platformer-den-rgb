#ifndef GAMES_ENGINEERING_SOUNDEFFECTS_H
#define GAMES_ENGINEERING_SOUNDEFFECTS_H

#include <SFML/Audio.hpp>
#include <string>

class SoundEffects
{
public:
    static void play(const std::string& filePath);

private:
    static sf::SoundBuffer m_soundBuffer;
    static sf::Sound m_sound;

    static bool initSoundBuffer(const std::string& filePath);
};

#endif // GAMES_ENGINEERING_SOUNDEFFECTS_H

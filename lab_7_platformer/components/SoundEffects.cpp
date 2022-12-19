#include "SoundEffects.h"

bool SoundEffects::initSoundBuffer(const std::string& filePath)
{
    return m_soundBuffer.loadFromFile(filePath);
}

void SoundEffects::play(const std::string& filePath)
{
    if (!initSoundBuffer(filePath))
    {
        // Throw an exception if the file could not be loaded
        throw std::runtime_error("Failed to load sound effect: " + filePath);
    }

    // Set up the sound
    m_sound.setBuffer(m_soundBuffer);
    m_sound.setVolume(100.0f);
    m_sound.play();
}

sf::SoundBuffer SoundEffects::m_soundBuffer;
sf::Sound SoundEffects::m_sound;

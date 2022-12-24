#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include "../components/BackGroundMusic.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

// Font and text for the menu title
Font font;
Text titleText;

// Buttons for menu options
RectangleShape playButton;
Text playText;

RectangleShape exitButton;
Text exitText;

// Variables for button hover animation
Color originalColor;

// SFML Music object for background music
sf::Music bgm;

// Volume slider and handle
sf::RectangleShape volumeSlider;
sf::RectangleShape volumeHandle;
Text volText;

// Mute button
sf::RectangleShape muteButton;
Text muteText;

// Variables for audio control
float volume = 100.0f;
bool isMuted = false;

void setMute(bool mute) {
    isMuted = mute;
    if (isMuted) {
        bgm.setVolume(0.0f);
    } else {
        bgm.setVolume(volume);
    }
}

void MenuScene::Load() {
    cout << "Menu Load \n";

// Load font from file
    font.loadFromFile("res/fonts/RobotoMono-Regular.ttf");

// Set up title text
    titleText.setFont(font);
    titleText.setOutlineColor(sf::Color::Magenta);
    titleText.setOutlineThickness(4);
    titleText.setString("Twin Split");
    titleText.setCharacterSize(96);
    titleText.setFillColor(Color::White);
    titleText.setPosition(Vector2f(350, 50));

// Set up play button
    playButton.setSize(Vector2f(200, 50));
    playButton.setFillColor(sf::Color::Transparent);
    playButton.setOutlineThickness(4);
    playButton.setOutlineColor(Color::White);
    playButton.setPosition(Vector2f(550, 250));


    playText.setFont(font);
    playText.setString("Play");
    playText.setCharacterSize(32);
    playText.setFillColor(Color::White);
    playText.setPosition(Vector2f(610, 255));
    playText.setOutlineColor(sf::Color::Magenta);
    playText.setOutlineThickness(4);

    volText.setFont(font);
    volText.setString("Volume");
    volText.setCharacterSize(32);
    volText.setFillColor(Color::White);
    volText.setPosition(Vector2f(370, 325));
    volText.setOutlineColor(sf::Color::Magenta);
    volText.setOutlineThickness(4);

// Set up volume slider
    volumeSlider.setSize(sf::Vector2f(200.0f, 10.0f));
    volumeSlider.setPosition(sf::Vector2f(350.0f, 380.0f));
    volumeSlider.setFillColor(sf::Color::Transparent);
    volumeSlider.setOutlineColor(sf::Color::Magenta);
    volumeSlider.setOutlineThickness(4);

// Set up volume handle
    volumeHandle.setSize(sf::Vector2f(10.0f, 10.0f));
    volumeHandle.setFillColor(sf::Color::White);
    volumeHandle.setPosition(sf::Vector2f(540.0f, 380.0f));

// Set up exit button
    exitButton.setSize(Vector2f(200, 50));
    exitButton.setFillColor(Color::Transparent);
    exitButton.setOutlineThickness(4);
    exitButton.setOutlineColor(Color::White);
    exitButton.setPosition(Vector2f(550, 450));

    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(32);
    exitText.setFillColor(Color::White);
    exitText.setPosition(Vector2f(610, 455));
    exitText.setOutlineColor(sf::Color::Magenta);
    exitText.setOutlineThickness(4);

// Set up mute button
    muteButton.setSize(sf::Vector2f(200.0f, 50.0f));
    muteButton.setPosition(sf::Vector2f(750.0f, 350.0f));
    muteButton.setFillColor(sf::Color::Transparent);
    muteButton.setOutlineColor(sf::Color::White);
    muteButton.setOutlineThickness(4);

    muteText.setFont(font);
    muteText.setString("Mute");
    muteText.setCharacterSize(32);
    muteText.setFillColor(Color::White);
    muteText.setPosition(Vector2f(810, 355));
    muteText.setOutlineColor(sf::Color::Magenta);
    muteText.setOutlineThickness(4);

// Load background music file into music object
    bgm.openFromFile("res/audio/bm.wav");

// Set initial volume and mute state
    bgm.setVolume(volume);
    setMute(isMuted);

// Start playing background music
    bgm.play();

    setLoaded(true);
}

void MenuScene::Update(const double& dt) {
// Check if the play button is hovered over
    if (playButton.getGlobalBounds().contains(Vector2f (static_cast<float>(Mouse::getPosition(Engine::GetWindow()).x), static_cast<float>(Mouse::getPosition(Engine::GetWindow()).y)))) {

        playButton.setFillColor(sf::Color::Magenta);

        // Check if the play button is clicked
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Engine::ChangeScene(&level3);
        }
    }
    else {
        playButton.setFillColor(originalColor);
    }

// Check if the volume slider is hovered over
    if (volumeSlider.getGlobalBounds().contains(Vector2f (static_cast<float>(Mouse::getPosition(Engine::GetWindow()).x), static_cast<float>(Mouse::getPosition(Engine::GetWindow()).y)))) {

        // Check if the volume handle is being dragged
        if (Mouse::isButtonPressed(Mouse::Left)) {
            // Update the position of the volume handle based on the mouse position
            volumeHandle.setPosition(sf::Vector2f(static_cast<float>(Mouse::getPosition(Engine::GetWindow()).x), volumeSlider.getPosition().y));

            // Clamp the position of the volume handle to the bounds of the volume slider
            if (volumeHandle.getPosition().x < volumeSlider.getPosition().x) {
                volumeHandle.setPosition(sf::Vector2f(volumeSlider.getPosition().x, volumeSlider.getPosition().y));
            }
            else if (volumeHandle.getPosition().x > volumeSlider.getPosition().x + volumeSlider.getSize().x - volumeHandle.getSize().x) {
                volumeHandle.setPosition(sf::Vector2f(volumeSlider.getPosition().x + volumeSlider.getSize().x - volumeHandle.getSize().x, volumeSlider.getPosition().y));
            }

            // Update the volume based on the position of the volume handle
            volume = (volumeHandle.getPosition().x - volumeSlider.getPosition().x) / (volumeSlider.getSize().x - volumeHandle.getSize().x) * 100.0f;
            bgm.setVolume(volume);
        }
    }

// Check if the mute button is hovered over
    if (muteButton.getGlobalBounds().contains(Vector2f (static_cast<float>(Mouse::getPosition(Engine::GetWindow()).x), static_cast<float>(Mouse::getPosition(Engine::GetWindow()).y)))) {

        muteButton.setFillColor(sf::Color::Magenta);

        // Check if the mute button is clicked
        if (Mouse::isButtonPressed(Mouse::Left)) {
            setMute(!isMuted);
        }
    }
    else {
        muteButton.setFillColor(originalColor);
    }

// Check if the exit button is hovered over
    if (exitButton.getGlobalBounds().contains(Vector2f (static_cast<float>(Mouse::getPosition(Engine::GetWindow()).x), static_cast<float>(Mouse::getPosition(Engine::GetWindow()).y)))) {

        exitButton.setFillColor(sf::Color::Magenta);

        // Check if the exit button is clicked
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Engine::GetWindow().close();
        }
    }
    else {
        exitButton.setFillColor(originalColor);
    }

// Update mute button text to reflect current mute state
    if (isMuted) {
        muteText.setString("Unmute");
    } else {
        muteText.setString("Mute");
    }
}

void MenuScene::Render() {
    Engine::GetWindow().draw(titleText);
    Engine::GetWindow().draw(playButton);
    Engine::GetWindow().draw(playText);
    Engine::GetWindow().draw(exitButton);
    Engine::GetWindow().draw(exitText);
    Engine::GetWindow().draw(volumeSlider);
    Engine::GetWindow().draw(volumeHandle);
    Engine::GetWindow().draw(muteButton);
    Engine::GetWindow().draw(muteText);
    Engine::GetWindow().draw(volText);
}


void MenuScene::UnLoad() {
    cout << "Menu Unload \n";
    setLoaded(false);
}

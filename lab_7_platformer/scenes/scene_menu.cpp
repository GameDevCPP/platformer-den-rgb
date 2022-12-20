#include "scene_menu.h"
#include "../components/cmp_text.h"
#include "../game.h"
#include "../components/BackGroundMusic.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

// Font and text for the menu title
Font font;
Text titleText;

// Buttons for menu options
RectangleShape playButton;
Text playText;

RectangleShape settingsButton;
Text settingsText;

RectangleShape exitButton;
Text exitText;

// Variables for button hover animation
Color originalColor;


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

// Set up settings button
    settingsButton.setSize(Vector2f(200, 50));
    settingsButton.setFillColor(Color::Transparent);
    settingsButton.setOutlineThickness(4);
    settingsButton.setOutlineColor(Color::White);
    settingsButton.setPosition(Vector2f(550, 350));

    settingsText.setFont(font);
    settingsText.setString("Settings");
    settingsText.setCharacterSize(32);
    settingsText.setFillColor(Color::White);
    settingsText.setPosition(Vector2f(575, 355));
    settingsText.setOutlineColor(sf::Color::Magenta);
    settingsText.setOutlineThickness(4);

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

    setLoaded(true);
    BackGroundMusic::playAudio("res/audio/bm.wav");
}

void MenuScene::Update(const double& dt) {
// Check if the play button is hovered over
    if (playButton.getGlobalBounds().contains(Vector2f (static_cast<float>(Mouse::getPosition(Engine::GetWindow()).x), static_cast<float>(Mouse::getPosition(Engine::GetWindow()).y)))) {

        playButton.setFillColor(sf::Color::Magenta);

        // Check if the play button is clicked
        if (Mouse::isButtonPressed(Mouse::Left)) {
            Engine::ChangeScene(&level1);
        }
    }
    else {
        playButton.setFillColor(originalColor);
    }

// Check if the settings button is hovered over
    if (settingsButton.getGlobalBounds().contains(Vector2f (static_cast<float>(Mouse::getPosition(Engine::GetWindow()).x), static_cast<float>(Mouse::getPosition(Engine::GetWindow()).y)))) {


        settingsButton.setFillColor(sf::Color::Magenta);

        // Check if the settings button is clicked
        if (Mouse::isButtonPressed(Mouse::Left)) {
            // TODO: Open settings scene
        }
    }
    else {
        settingsButton.setFillColor(originalColor);
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

    Scene::Update(dt);

}

void MenuScene::Render() {
    Engine::GetWindow().draw(titleText);
    Engine::GetWindow().draw(playButton);
    Engine::GetWindow().draw(playText);
    Engine::GetWindow().draw(settingsButton);
    Engine::GetWindow().draw(settingsText);
    Engine::GetWindow().draw(exitButton);
    Engine::GetWindow().draw(exitText);
    Scene::Render();

}

void MenuScene::UnLoad() {
    cout << "Menu Unload \n";
    setLoaded(false);
}

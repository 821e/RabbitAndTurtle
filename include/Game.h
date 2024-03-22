#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Rabbit.h"
#include "Turtle.h"
#include "Track.h"
#include "Fox.h"

class Game {
public:
    enum class State {
        Starting,
        Ready,
        InProgress,
        Finished
    };

    Game();
    void run();

private:
    sf::RenderWindow window;
    sf::Music backgroundMusic;
    State gameState;
    Rabbit rabbit;
    Turtle turtle;
    Track raceTrack;
    Fox fox;
    sf::Text winnerText;
    sf::Font gameFont;
    sf::Texture rabbitTexture, turtleTexture, foxTexture, trackTexture;
    sf::SoundBuffer celebrationSoundBuffer;
    sf::Sound celebrationSound;
    sf::Texture startScreenTexture;
    sf::Sprite startScreenSprite;

    void initialize();
    void loadAssets();
    void setupRace();
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    void declareWinner(const std::string& winner);
};

#endif // GAME_H
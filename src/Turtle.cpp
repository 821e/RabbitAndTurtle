#include "Turtle.h"
#include <iostream>

Turtle::Turtle() : speed(25.0f), finishedRace(false), frameIndex(0) {
    if (!font.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/fonts/game_font.ttf")) {
        std::cout << "Failed to load font." << std::endl;
    }

    determinationText.setFont(font);
    determinationText.setString("");
    determinationText.setCharacterSize(17);
    determinationText.setFillColor(sf::Color::White);
}

void Turtle::setTextures(const std::vector<sf::Texture>& newTextures) {
    walkingTextures = newTextures;
    if (!walkingTextures.empty()) {
        sprite.setTexture(walkingTextures[0]);
    }
}

void Turtle::setTexture(sf::Texture& texture) {
    //setTextures() to handle multiple frames.
}

void Turtle::update(sf::Time deltaTime) {
    if (!finishedRace) {
        sprite.move(speed * deltaTime.asSeconds(), 0);
        determinationText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 50);

        if (frameClock.getElapsedTime().asSeconds() > 0.25) {
            frameIndex = (frameIndex + 1) % walkingTextures.size();
            sprite.setTexture(walkingTextures[frameIndex]);
            frameClock.restart();
        }

        if (sprite.getPosition().x > 1240) {
            finishRace();
        }
    }
}

void Turtle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(determinationText);
}

bool Turtle::hasFinishedRace() const {
    return finishedRace;
}

void Turtle::finishRace() {
    finishedRace = true;
    speed = 1;
    determinationText.setString("I did it, slow and steady!");
    determinationText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 40);
}

#include "Track.h"
#include <iostream>

Track::Track() {
   // finishLine.setSize(sf::Vector2f(5.0f, 600.0f));
    //finishLine.setFillColor(sf::Color::Red);
    //finishLine.setPosition(1000.0f, 0);

    loadAssets();
}

void Track::loadAssets() {
    // Load the font
    if (!font.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/fonts/game_font.ttf")) {
        std::cerr << "Failed to load font from assets/fonts/game_font.ttf" << std::endl;
    }

    // Load the background texture
    if (!backgroundTexture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/background.png")) {
        std::cerr << "Failed to load background texture" << std::endl;
    } else {
        background.setTexture(backgroundTexture);
    }

    // Load the lane texture
    if (!laneTexture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/track.png")) {
        std::cerr << "Failed to load track texture" << std::endl;
    } else {
        laneSprite.setTexture(laneTexture);
        // Position the lane sprite
        laneSprite.setPosition(-20, 310); // Set this to the position where you want the lanes to appear
    }
}

void Track::setTexture(const sf::Texture& texture) {
    background.setTexture(texture);
}

void Track::draw(sf::RenderWindow& window) {
    window.draw(background); // Draw the background
    window.draw(laneSprite); // Draw the lane on top of the background
    window.draw(finishLine);
}

sf::FloatRect Track::getFinishLine() const {
    return finishLine.getGlobalBounds();
}

void Track::update(sf::Time elapsedTime) {
    // Update logic for the track, if any
}

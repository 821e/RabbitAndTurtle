#include "Fox.h"

Fox::Fox() : raceStarted(false) {
    if (!font.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/fonts/game_font.ttf")) {
    }
    startSignalText.setFont(font);
    startSignalText.setString("Get Ready!");
    startSignalText.setCharacterSize(24);
    startSignalText.setFillColor(sf::Color::White);
    startSignalText.setPosition(100, 50);
}

void Fox::setTexture(sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Fox::update(sf::Time deltaTime) {
    if (raceStarted && !raceFinished) {
        // Move the fox at a certain speed only if it has not yet reached the end goal
        if (sprite.getPosition().x < 1200) {
            sprite.move(50.f * deltaTime.asSeconds(), 0);
        } else {
            // Optional: Mark the race as finished if the fox reaching the end goal signifies the end of the race
            raceFinished = true;
            // Here, you could also trigger any actions that occur when the race finishes,
            // such as declaring a winner, through a callback or directly here.
        }

        // Check for winner logic could be here if necessary
    }
}

void Fox::draw(sf::RenderWindow& window) {
    Entity::draw(window);
    if (!raceStarted) {
        window.draw(startSignalText);
    }
}

void Fox::setRaceStartCallback(std::function<void()> callback) {
    raceStartCallback = callback;
}

void Fox::setRaceEndCallback(std::function<void(std::string)> callback) {
    raceEndCallback = callback;
}

void Fox::startRace() {
    if (raceStartCallback) {
        raceStartCallback();
    }
    raceStarted = true;
    startSignalText.setString(""); // Clear start signal text
}

void Fox::checkForWinner(const Entity& rabbit, const Entity& turtle) {
    if (!raceStarted) return;

    if (rabbit.hasFinishedRace() || turtle.hasFinishedRace()) {
        std::string winner = turtle.hasFinishedRace() ? "Turtle" : "Rabbit";
        if (raceEndCallback) {
            raceEndCallback(winner);
        }
        raceStarted = false;
        // Optionally, display the winner or end race signals here
    }
}

#include "Rabbit.h"
#include <iostream>
#include <SFML/Audio.hpp>


Rabbit::Rabbit() : speed(64.0f), napping(false), finishedRace(false), napDuration(sf::seconds(31)), currentState(RabbitState::Walking) {
    initialPosition = sf::Vector2f(100.0f, 300.0f);
    loadTextures();

    if (!font.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/fonts/game_font.ttf")) {
        std::cerr << "Failed to load font from assets/fonts/game_font.ttf" << std::endl;
    }

    napText.setFont(font);
    napText.setString("Zzzzz");
    napText.setCharacterSize(24);
    napText.setFillColor(sf::Color::White);
}

void Rabbit::loadTextures() {
    sf::Texture texture;

    if (texture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/rabbit_running.png")) {
        textures[RabbitState::Racing] = texture;
    } else {
        std::cerr << "Failed to load rabbit_running.png" << std::endl;
    }

    if (texture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/rabbit_walking.png")) {
        textures[RabbitState::Walking] = texture;
    } else {
        std::cerr << "Failed to load rabbit_walking.png" << std::endl;
    }

    if (texture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/rabbit_napping.png")) {
        textures[RabbitState::Napping] = texture;
    } else {
        std::cerr << "Failed to load rabbit_napping.png" << std::endl;
    }

    if (texture.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/images/rabbit_waking_up.png")) {
        textures[RabbitState::WakingUp] = texture;
    } else {
        std::cerr << "Failed to load rabbit_waking_up.png" << std::endl;
    }
    if (!napSoundBuffer.loadFromFile("/Users/rakan/Developer/cpp/TheRabbitAndTheTurtle/assets/sounds/gentle_sleep_music.ogg")) {
        std::cerr << "Failed to load gentle_sleep_music.ogg" << std::endl;
    }
    napSound.setBuffer(napSoundBuffer);

    changeState(RabbitState::Walking);
}

void Rabbit::changeState(RabbitState newState) {
    currentState = newState;
    sprite.setTexture(textures[newState], true);
}


void Rabbit::update(sf::Time deltaTime) {
    if (finishedRace) {
        return;
    }

    // Adjusted parameters for slower and more subtle shaking
    const float shakeMagnitude = 2.0f; // Lower magnitude for a subtler shake
    const float shakeSpeed = 5.0f; // Lower speed for a slower shake

    if (currentState == RabbitState::Walking || currentState == RabbitState::Racing) {
        if (shakeDirectionUp) {
            shakeOffsetY -= shakeSpeed * deltaTime.asSeconds();
            if (shakeOffsetY < -shakeMagnitude) {
                shakeDirectionUp = false;
            }
        } else {
            shakeOffsetY += shakeSpeed * deltaTime.asSeconds();
            if (shakeOffsetY > shakeMagnitude) {
                shakeDirectionUp = true;
            }
        }
    } else {
        shakeOffsetY = 0.0f; // Reset the shake offset when not walking or racing
    }

    // Update the rabbit's position considering the shake effect
    sf::Vector2f newPosition = {sprite.getPosition().x, initialPosition.y + shakeOffsetY -25};
    sprite.setPosition(newPosition);

    switch (currentState) {
        case RabbitState::Walking:
            // Apply both forward movement and shake effect
            sprite.move(speed * deltaTime.asSeconds(), shakeOffsetY);
            if (sprite.getPosition().x > 610 && !napping) {
                startNapping();
            }
            break;
        case RabbitState::Racing:
            // Apply both forward movement and shake effect
            sprite.move(speed * deltaTime.asSeconds(), shakeOffsetY);
            break;
        case RabbitState::Napping:
            if (napTimer.getElapsedTime() >= napDuration) {
                wakeUp();
            } else {
                updateNapTextPosition(deltaTime);
            }
            break;
        case RabbitState::WakingUp:
            if (napTimer.getElapsedTime() >= sf::seconds(2)) {
                changeState(RabbitState::Racing);
            }
            break;
        default:
            break;
    }

    if (sprite.getPosition().x > 1220) {
        finishRace();
    }
}



void Rabbit::startNapping() {
    napping = true;
    napTimer.restart();
    changeState(RabbitState::Napping);

    napSound.setVolume(80.0f);
    napSound.play();
}

void Rabbit::wakeUp() {
    napping = false;
    changeState(RabbitState::WakingUp);
    napTimer.restart();
}




void Rabbit::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    if (currentState == RabbitState::Napping) {
        window.draw(napText);
    }
}

void Rabbit::finishRace() {
    finishedRace = true;
    speed = 0;
}

bool Rabbit::hasFinishedRace() const {
    return finishedRace;
}

void Rabbit::updateNapTextPosition(sf::Time deltaTime) {
    static float verticalOffset = 1.0f; // Keeps track of the current vertical offset
    static bool movingUp = true;

    const float speed = 10.0f;
    const float maxOffset = 20.0f;

    if (movingUp) {
        verticalOffset -= speed * deltaTime.asSeconds();
        if (verticalOffset < -maxOffset) {
            movingUp = false;
        }
    } else {
        verticalOffset += speed * deltaTime.asSeconds();
        if (verticalOffset > maxOffset) {
            movingUp = true;
        }
    }

    napText.setPosition(sprite.getPosition().x, sprite.getPosition().y + verticalOffset - 50); // Update text position based on offset
}
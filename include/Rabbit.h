#ifndef RABBIT_H
#define RABBIT_H

#include "Entity.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>
#include <map>

enum class RabbitState {
    Racing,
    Walking,
    Napping,
    WakingUp
};

class Rabbit : public Entity {
public:
    Rabbit();
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    bool isNapping() const;
    void startNapping();
    void wakeUp();
    bool hasFinishedRace() const override;
    void finishRace() override;

private:
    std::map<RabbitState, sf::Texture> textures;
    RabbitState currentState;
    float speed;
    bool napping;
    bool finishedRace;
    sf::Clock napTimer;
    sf::Time napDuration;
    sf::Text napText;
    sf::Font font;
    sf::SoundBuffer napSoundBuffer;
    sf::Sound napSound;

    // New members for the shaking effect
    float shakeOffsetY = 0.0f; // Vertical offset for the shaking effect
    bool shakeDirectionUp = true; // Direction of the shaking movement
    sf::Vector2f initialPosition;

    void changeState(RabbitState newState);
    void loadTextures();
    void updateNapTextPosition(sf::Time deltaTime);
};

#endif // RABBIT_H

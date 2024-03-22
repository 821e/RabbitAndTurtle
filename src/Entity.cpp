#include "Entity.h"

Entity::Entity() : speed(0.0f), finishedRace(false) {
    // Initialization with default values
}

void Entity::setTexture(sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Entity::update(sf::Time deltaTime) {
    // This remains purely virtual; specific logic will be in derived classes
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

bool Entity::hasFinishedRace() const {
    return finishedRace;
}

void Entity::finishRace() {
    finishedRace = true;
    speed = 0;
}

void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition();
}

void Entity::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity();
    virtual ~Entity() = default; // Ensure proper cleanup of derived classes

    virtual void setTexture(sf::Texture& texture);
    virtual void update(sf::Time deltaTime) = 0; // Keep as pure virtual
    virtual void draw(sf::RenderWindow& window);
    virtual bool hasFinishedRace() const;
    virtual void finishRace();

    // New methods for enhanced functionality
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    void move(float offsetX, float offsetY);

protected:
    sf::Sprite sprite;
    float speed;
    bool finishedRace;
};

#endif // ENTITY_H

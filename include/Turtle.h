#ifndef TURTLE_H
#define TURTLE_H

#include "Entity.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>

class Turtle : public Entity {
public:
    Turtle();
    void setTextures(const std::vector<sf::Texture>& newTextures);
    void setTexture(sf::Texture& texture) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    bool hasFinishedRace() const override;
    void finishRace() override;

private:
    float speed;
    bool finishedRace;
    sf::Text determinationText;
    sf::Font font;
    sf::RectangleShape progressBarBackground;
    std::vector<sf::Texture> walkingTextures; // Textures for animation
    size_t frameIndex; // Index of the current texture frame
    sf::Clock frameClock; // Clock to determine when to switch frames
};

#endif // TURTLE_H
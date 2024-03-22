#ifndef FOX_H
#define FOX_H

#include "Entity.h"
#include <functional>
#include <SFML/Graphics/Text.hpp>

class Fox : public Entity {
public:
    Fox();
    void setTexture(sf::Texture& texture) override;
    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void setRaceStartCallback(std::function<void()> callback);
    void setRaceEndCallback(std::function<void(std::string)> callback);
    void startRace();
    void checkForWinner(const Entity& rabbit, const Entity& turtle);

private:
    std::function<void()> raceStartCallback;
    std::function<void(std::string)> raceEndCallback;
    bool raceStarted;
    sf::Text startSignalText;
    sf::Font font;
    bool raceFinished; // Add this line

};

#endif // FOX_H

#ifndef TRACK_H
#define TRACK_H

#include <SFML/Graphics.hpp>

class Track {
public:
    Track();
    void setTexture(const sf::Texture& texture);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getFinishLine() const;
    void update(sf::Time elapsedTime);

private:
    sf::Sprite background; // Sprite for the background
    sf::Sprite laneSprite; // Sprite for the track lane
    sf::Texture backgroundTexture; // Texture for the background
    sf::Texture laneTexture; // Texture for the track lane
    sf::RectangleShape finishLine; // Shape for the finish line
    sf::Font font; // Font for any text

    void loadAssets();
};

#endif // TRACK_H

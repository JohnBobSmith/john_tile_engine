#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
    public:
        Player();
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        sf::Vector2f velocity;
        int maxVelocity;
        sf::Vector2f size;
        float health;
        //Do we render the player?
        bool isActive;
        //Can the player move?
        bool canMove;
        bool setTexture(std::string path);
        void handlePlayerEvents(sf::Event event);
        void movePlayer();
};



#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Camera.h"

class Player
{
    public:
        Player();
        //Players sprite and texture
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f position;
        sf::Vector2f velocity;
        //Player dimensions
        sf::Vector2f size;
        float health;
        //Do we render the player?
        bool isActive;
        //Do we animate the player?
        bool isWalking;
        //Max speed
        int maxVelocity;

        void animate();
        bool setTexture(std::string path);
        void handlePlayerEvents(sf::Event event);
        void movePlayer();
        bool checkCollision(Collision &collision, Camera &camera);
};



#endif // PLAYER_H

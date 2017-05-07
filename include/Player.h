#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Camera.h"

class Player
{
    public:
        //Init the player
        Player();

        //Players sprite
        sf::Sprite sprite;

        //Players texture
        sf::Texture texture;

        //Players position and velocity
        sf::Vector2f position;
        sf::Vector2f velocity;

        //Player dimensions
        sf::Vector2f size;

        //Players health
        float health;

        //Do we render the player?
        bool isActive;

        //Do we animate the player?
        bool isWalking;

        //Max speed
        int maxVelocity;

        //Animate the player
        void animate();

        //Set the texture
        bool setTexture(std::string path);

        //Handle player input
        void handlePlayerEvents(sf::Event event);

        //Move the player
        void movePlayer();

        //Check for collisions against the player and X object.
        bool checkCollision(Collision &collision, Camera &camera);

    private:
        //Keep track of how many keys are pressed.
        int keyCounter;
};



#endif // PLAYER_H

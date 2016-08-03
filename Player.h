#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

//Our player, who interacts with
//the game and its environment
class Player
{
    public:
        //Automatic initialization
        Player();

        //Handle our events ie mouseclick, keydown
        void handleEvents(sf::Event &event);

        //Move the player
        void move(float deltaTime);

        //Get player position
        sf::Vector2f getPlayerPosition() { return position; }

        //Get player sprite
        sf::Sprite getSprite() { return player; }



    private:
        //Player's maximum velocity
        const float PLAYER_VELOCITY = 600.0f;

        //Our player and his texture.
        sf::Texture playerTexture;
        sf::Sprite player;

        //Players velocity
        sf::Vector2f velocity;

        //Players position.
        sf::Vector2f position;
};

#endif // PLAYER_H

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

//Our player, who interacts with
//the game and its environment
class Player
{
    public:
        //Our player sprite
        sf::Sprite player;

        //Automatic initialization
        Player();

        //Handle our events ie mouseclick, keydown
        void handleEvents(sf::Event &event);

        //Move the player
        void move(float deltaTime);

        //Get player position
        sf::Vector2f getPlayerPosition() { return position; }

    private:
        //Our player texture.
        sf::Texture playerTexture;

        //Players position.
        sf::Vector2f position;
};

#endif // PLAYER_H

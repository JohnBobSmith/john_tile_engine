#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collision.h"
#include "Camera.h"

class Player
{
    public:
        //Init the player
        Player();

        //Sprite for our bounding box
        sf::Sprite boundingBoxSprite;
        sf::Texture boundingBoxSpriteTexture;

        //Our respawn text
        sf::Text respawnText;

        //Our death/respawn sounds
        sf::Sound respawnSound;
        sf::Sound deathSound;

        //Spawn time value (not actual seconds)
        float spawnTime = 12.0f;

        //Player sprites and textures
        sf::Sprite body;
        sf::Sprite legs;
        sf::Texture bodyTexture;
        sf::Texture legsTexture;

        //Players position and velocity
        sf::Vector2f position;
        sf::Vector2f velocity;
        int maxVelocity;

        //Player dimensions
        sf::Vector2f size;

        //Players health
        float health;

        //Do we render the player?
        bool isActive;

        //Do we animate the player?
        bool isWalking;

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

        //Play some sounds if the player collides with these tiles
        bool checkAudioCollsion(Collision &collision);

        //Damage the player
        void applyDamage(int ammount);

        //End the players life prematurely.
        void killPlayer();

        //Allow the player to respawn at a random spawn point
        void respawn(Camera &camera, int randomNumber = 0);

    private:
        //Our respawn text's font
        sf::Font squarefont;

        //Our respawn sounds buffer
        sf::SoundBuffer respawnSoundBuffer;
        sf::SoundBuffer deathSoundBuffer;

        //Locations where the player can respawn
        std::vector<sf::Vector2f> spawnPoints;

        //How many spawn points there are
        int MAX_SPAWN_POINTS = 10;

        //Keep track of how many keys are pressed.
        int keyCounter;

        //Which direction is the player facing?
        /*
            0 = up
            1 = down
            2 = left
            3 = right
        */
        int direction = 0;
};

#endif // PLAYER_H

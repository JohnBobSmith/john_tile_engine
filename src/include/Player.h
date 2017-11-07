#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Collision.h"
#include "SoundManager.h"

class Player
{
    public:
        //Init the player
        Player();

        //RectangleShape for our bounding box
        sf::RectangleShape boundingBox;

        //Our respawn time
        sf::Time spawnTime;

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
        
        //Do we play the reload animation?
        bool isReloading;

		//Are we playing the respawn sound
        bool isPlayingRespawnSound;

        //Animate the player
        void animateLegs();
        void animateReload();

        //Load our textures
        bool loadTexture();

        //Handle player input
        void handlePlayerEvents(sf::Event event);

        //Move the player
        void movePlayer();

        //Check for collisions against the player and X object.
        bool checkCollision(Collision &collision, Camera &camera);

        //Play some sounds if the player collides with these tiles
        bool checkAudioCollsion(Collision &collision);

        //Damage the player
        void applyDamage(int ammount, SoundManager &soundmngr);

        //End the players life prematurely.
        void killPlayer(SoundManager &soundmngr);

        //Allow the player to respawn at a random spawn point
        void respawn(Camera &camera, SoundManager &soundmngr, int randomNumber = 0);
        
        //Update play attributes
        void update();

    private:
        //Locations where the player can respawn
        std::vector<sf::Vector2f> spawnPoints;

        //How many spawn points there are
        int MAX_SPAWN_POINTS = 10;
        
        //How many keys are presed
        int keyCounter = 0;
        
        //Our fixed respawn time that doesnt change
        const sf::Time respawnTime = sf::milliseconds(1200);
};

#endif // PLAYER_H

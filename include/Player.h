#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Collision.h"
#include "Camera.h"
#include "SoundManager.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Mouse.h"

class Player
{
    public:
        //Init the player
        Player();

        //RectangleShape for our bounding box
        sf::RectangleShape boundingBox;

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

        //Load our textures
        bool loadTexture();

        //Handle player input
        void handlePlayerEvents(sf::Event event, Weapon &weapon, Bullet &bullet, Mouse &mouse);

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

    private:

        //Our respawn sounds buffer
        sf::SoundBuffer respawnSoundBuffer;
        sf::SoundBuffer deathSoundBuffer;

        //Locations where the player can respawn
        std::vector<sf::Vector2f> spawnPoints;

        //How many spawn points there are
        int MAX_SPAWN_POINTS = 10;

        //Keep track of how many keys are pressed.
        int keyCounter;
};

#endif // PLAYER_H

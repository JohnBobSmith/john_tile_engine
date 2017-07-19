#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <memory>
#include "Mouse.h"
#include "Player.h"

class Bullet
{
    public:
        struct BulletObj
        {
            //The sprite to be drawn
            sf::Sprite bulletSprite;

            //Every bullet must have a texture
            sf::Texture bulletTexture;

            //Velocities and positions
            float velocityX = 0;
            float velocityY = 0;
            float positionX = 0;
            float positionY = 0;

            //do we render this bullet piece?
            bool isActive = false;

            //Every bullet does damage
            const int bulletDamage = 12;
        };

        //Set our textures up automatically
        Bullet();

        //Our working rate of fire
        float rateOfFire = maxRateOfFire;

        //Expose the maximum amount of bullets allowed
        int getMaxbullets() { return maxBullets; };

        //Move our bullets towards the mouse
        void move();

        //Shoot a bullet
        void shoot(Mouse &mouse);

        //Store our bullets in an std::Vector
        std::vector<std::shared_ptr<BulletObj>> bulletStorage;

    private:
        //How fast to shoot
        const float maxRateOfFire = 0.25f;

        //How many bullets may be on screen at a time
        const int maxBullets = 2000;

        //The maximum velocity of a bullet
        const float maximumVelocity = 5.0f;
};

#endif // BULLET_H

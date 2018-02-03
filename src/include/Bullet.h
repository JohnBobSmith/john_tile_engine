#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <cmath>
#include "SoundManager.h"
#include "Weapon.h"
#include "Collision.h"

class Bullet
{
    public:
        struct BulletObj
        {
            //The sprite to be drawn
            sf::Sprite bulletSprite;

            //Every bullet must have a texture
            sf::Texture bulletTexture;

            //The bullet position
            float positionX;
            float positionY;

            //do we render this bullet?
            bool isActive;
            
            //Collision box to simplify collision checking
            sf::RectangleShape bbox;
        };

        //Set our textures up automatically
        Bullet();

        //Expose the maximum amount of bullets allowed
        int getMaxBullets() { return maxBullets; };

        //Move our bullets towards the mouse
        void moveBullet();

        //Shoot a bullet
        void shoot(SoundManager &soundmngr, Weapon &weapon, float mouseAngle, float spread);
        
        //Check collision
        void checkBulletCollision(Collision &collision);

        //Store our bullets in an std::vector
        std::vector<std::shared_ptr<BulletObj>> bulletStorage;

    private:
        //How many bullets may be on screen at a time
        const int maxBullets = 256;

        //The maximum velocity of a bullet
        const float maximumVelocity = 5.0f;
};

#endif // BULLET_H

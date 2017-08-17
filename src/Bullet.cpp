#include "include/Bullet.h"
#include <cmath>
#include <iostream>

Bullet::Bullet()
{
    //Populate our bullet storage
    for (int i = 0; i < maxBullets; ++i) {
        bulletStorage.push_back(std::make_shared<BulletObj>());
        bulletStorage[i]->bulletTexture.loadFromFile("../textures/weapons/bullet.png");
        bulletStorage[i]->bulletSprite.setTexture(bulletStorage[i]->bulletTexture);
        bulletStorage[i]->isActive = false;
        bulletStorage[i]->positionX = 0;
        bulletStorage[i]->positionY = 0;
        bulletStorage[i]->bbox.setSize(sf::Vector2f(5, 5));
        bulletStorage[i]->bbox.setFillColor(sf::Color::Black);
    }
}

//*
void Bullet::shoot(SoundManager &soundmngr, Weapon &weapon, float mouseAngle)
{
    static int currentBullet = 0;
    //Initialize the rate of fire to each weapons rate of fire.
    static sf::Time workingRateOfFire = weapon.rateOfFire;
    workingRateOfFire -= sf::milliseconds(10);
    if (workingRateOfFire.asMilliseconds() <= 0) {
        weapon.ammoInMagazine -= 1;
        soundmngr.playLmgFire();
        //Shoot a bullet towards the mouse.
        bulletStorage[currentBullet]->isActive = true;
        bulletStorage[currentBullet]->positionX = maximumVelocity *
                                (std::cos(mouseAngle * M_PI / 180));

        bulletStorage[currentBullet]->positionY = maximumVelocity *
                                (std::sin(mouseAngle * M_PI / 180));
        //Reset rate of fire
        workingRateOfFire = weapon.rateOfFire;
    }

    //Do not go out of bounds.
    currentBullet += 1;
    if (currentBullet >= maxBullets) {
        currentBullet = 0;
    }
}
//*/

void Bullet::move()
{
    //Move our bullets every frame
    for (int i = 0; i < maxBullets; ++i) {
        if (bulletStorage[i]->isActive) {
            bulletStorage[i]->bulletSprite.move(bulletStorage[i]->positionX,
                                                bulletStorage[i]->positionY);
        }
    }
    //Move the collision box too.
    for (int i = 0; i < maxBullets; ++i) {
        bulletStorage[i]->bbox.setPosition(bulletStorage[i]->bulletSprite.getPosition());
    }
}

void Bullet::checkBulletCollision(Collision &collision)
{
    for (int i = 0; i < maxBullets; ++i) {
        for (int j = 0; j < collision.MAX_COLLISION_BOXES; ++j) {
            //Skip over inactive collision boxes.
            if (!collision.collVector[j]->isActive || !bulletStorage[i]->isActive) {
                continue;
            //Perform the collision checks.
            } else if (collision.checkAABBcollision(bulletStorage[i]->bbox.getPosition().x,
                                                 bulletStorage[i]->bbox.getPosition().y,
                                                 bulletStorage[i]->bulletTexture.getSize().x,
                                                 bulletStorage[i]->bulletTexture.getSize().y,
                                                 collision.collVector[j]->bbox.getPosition().x,
                                                 collision.collVector[j]->bbox.getPosition().y,
                                                 collision.collVector[j]->bbox.getSize().x,
                                                 collision.collVector[j]->bbox.getSize().y)) {
                                                 
                //And kill any bullet that collides.
                bulletStorage[i]->isActive = false;
            }
        }
    }
}
        

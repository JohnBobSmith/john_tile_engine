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
        //bulletStorage[i]->bulletSprite.setScale(0.25, 0.5);
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
    static sf::Time workingRateOfFire = weapon.rateOfFire;
    workingRateOfFire -= sf::milliseconds(10);
    if (workingRateOfFire.asMilliseconds() <= 0) {
        weapon.ammoInMagazine -= 1;
        soundmngr.playLmgFire();
        bulletStorage[currentBullet]->isActive = true;
        bulletStorage[currentBullet]->positionX = maximumVelocity *
                                (std::cos(mouseAngle * M_PI / 180));

        bulletStorage[currentBullet]->positionY = maximumVelocity *
                                (std::sin(mouseAngle * M_PI / 180));
        workingRateOfFire = weapon.rateOfFire;
    }

    currentBullet += 1;
    if (currentBullet >= maxBullets) {
        currentBullet = 0;
    }
}
//*/

void Bullet::move()
{
    for (int i = 0; i < maxBullets; ++i) {
        if (bulletStorage[i]->isActive) {
            bulletStorage[i]->bulletSprite.move(bulletStorage[i]->positionX,
                                                bulletStorage[i]->positionY);
        }
    }
    for (int i = 0; i < maxBullets; ++i) {
        bulletStorage[i]->bbox.setPosition(bulletStorage[i]->bulletSprite.getPosition());
    }
}

bool Bullet::checkBulletCollision(Collision &collision)
{
    for (int i = 0; i < maxBullets; ++i) {
        if (collision.checkAABBcollision(bulletStorage[i]->bbox.getPosition().x,
                                         bulletStorage[i]->bbox.getPosition().y,
                                         5, 5,
                                         collision.collVector[i]->bbox.getPosition().x,
                                         collision.collVector[i]->bbox.getPosition().y,
                                         collision.collVector[i]->bbox.getSize().x,
                                         collision.collVector[i]->bbox.getSize().y)) {
            std::cout << bulletStorage[i]->bbox.getPosition().y << std::endl;
            return true;
        }
    }
    return false;
}
        
        
        
        
        
        
        
        
        

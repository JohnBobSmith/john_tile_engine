#include "include/Bullet.h"
#include <cmath>
#include <iostream>

Bullet::Bullet()
{
    //Populate our bullet storage
    for (int i = 0; i < maxBullets; ++i) {
        bulletStorage.push_back(std::make_shared<BulletObj>());
        bulletStorage[i]->bulletTexture.loadFromFile("textures/weapons/bullet.png");
        bulletStorage[i]->bulletSprite.setTexture(bulletStorage[i]->bulletTexture);
        bulletStorage[i]->bulletSprite.setScale(0.25, 0.5);
        bulletStorage[i]->isActive = false;
        bulletStorage[i]->positionX = 0;
        bulletStorage[i]->positionY = 0;
        bulletStorage[i]->bulletDamage = 12;
    }
}

//*
void Bullet::shoot(float mouseAngle, float rateOfFire)
{
    static int currentBullet = 0;
    static float workingRateOfFire = rateOfFire;
    workingRateOfFire -= 0.01f;
    if (workingRateOfFire <= 0) {
        bulletStorage[currentBullet]->isActive = true;
        bulletStorage[currentBullet]->positionX = maximumVelocity *
                                (std::cos(mouseAngle * M_PI / 180));

        bulletStorage[currentBullet]->positionY = maximumVelocity *
                                (std::sin(mouseAngle * M_PI / 180));

        workingRateOfFire = rateOfFire;
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
}

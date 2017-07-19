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
    }
}

void Bullet::shoot(Mouse &mouse)
{
    static int currentBullet = 0;

    bulletStorage[currentBullet]->isActive = true;
    bulletStorage[currentBullet]->velocityX = maximumVelocity *
                (std::cos(mouse.getMouseAngle() * M_PI / 180));

    bulletStorage[currentBullet]->velocityY = maximumVelocity *
                (std::sin(mouse.getMouseAngle() * M_PI / 180));

    currentBullet += 1;
    if (currentBullet >= maxBullets) {
        currentBullet = 0;
    }
}

void Bullet::move()
{
    for (int i = 0; i < maxBullets; ++i) {
        if (bulletStorage[i]->isActive) {
            bulletStorage[i]->positionX += bulletStorage[i]->velocityX;
            bulletStorage[i]->positionY += bulletStorage[i]->velocityY;
            bulletStorage[i]->bulletSprite.setPosition(bulletStorage[i]->positionX,
                                                      bulletStorage[i]->positionY);
        }
    }
}

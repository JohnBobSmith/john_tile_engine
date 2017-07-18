#include "Bullet.h"
#include <iostream>

Bullet::Bullet()
{
    //Populate our bullet storage
    for (int i = 0; i < maxBullets; ++i) {
        bulletStorage.push_back(std::make_shared<BulletObj>());
        bulletStorage[i]->bulletTexture.loadFromFile("textures/entity/bullet.png");
        bulletStorage[i]->bulletSprite.setTexture(bulletStorage[i]->bulletTexture);
    }
}

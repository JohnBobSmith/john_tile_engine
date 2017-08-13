#include "include/Weapon.h"
#include <iostream>

Weapon::Weapon(std::string path)
{
    weaponTexture.loadFromFile(path.c_str());
    weapSprite.setTexture(weaponTexture);

    //Default attributes
    isEquipped = true;
    damage = 20;
    maxAmmo = 150;
    magazineSize = 25;
    ammoInMagazine = magazineSize;
    rateOfFire = 0.25f;
    canReload = false;
    canShoot = true;
    reloadTime = sf::milliseconds(750);
    baseReloadTime = reloadTime;
    reloadSoundString = "lmg";
    isReloading = false;
}

void Weapon::reload(SoundManager &soundmngr)
{
    isReloading = true;
    if (ammoInMagazine == magazineSize) {
        canReload = false;
    } else {
        canReload = true;
    }
    
    if (maxAmmo > 0 && canReload) {
        maxAmmo -= magazineSize;
        ammoInMagazine = magazineSize;
        if (reloadSoundString == "lmg") {
            soundmngr.playLmgReload();
        }
    } 
}

void Weapon::update()
{
    if (isReloading) {
        canShoot = false;
        reloadTime -= sf::milliseconds(10);
        std::cout << reloadTime.asMilliseconds() << "\n";
        if (reloadTime.asMilliseconds() == 0) {
            isReloading = false;
            canShoot = true;
            reloadTime = baseReloadTime;
            std::cout << "STOPPED\n";
        }
    } 
}








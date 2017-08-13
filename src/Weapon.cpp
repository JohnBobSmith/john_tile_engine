#include "include/Weapon.h"

Weapon::Weapon(std::string path)
{
    weaponTexture.loadFromFile(path.c_str());
    weapSprite.setTexture(weaponTexture);

    //Default attributes
    isEquipped = true;
    isReloading = false; 
    canReload = false;
    canShoot = true;   
    damage = 20;
    maxAmmo = 150;
    magazineSize = 25;
    ammoInMagazine = magazineSize;
    rateOfFire = sf::milliseconds(100);
    reloadTime = sf::milliseconds(750);
    baseReloadTime = reloadTime;
    reloadSoundString = "lmg";

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
        if (reloadTime.asMilliseconds() == 0) {
            isReloading = false;
            canShoot = true;
            reloadTime = baseReloadTime;
        }
    } 
}


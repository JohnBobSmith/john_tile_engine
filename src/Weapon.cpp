#include "include/Weapon.h"

Weapon::Weapon(std::string path, float dmg, int ammoMax, int magSize, 
                    sf::Time RoF, sf::Time reload, std::string name)
{
    weaponTexture.loadFromFile(path.c_str());
    weapSprite.setTexture(weaponTexture);

    //Default attributes
    isEquipped = true;
    isReloading = false; 
    canReload = false;
    canShoot = true;  
     
    damage = dmg;
    maxAmmo = ammoMax;
    magazineSize = magSize;
    ammoInMagazine = magazineSize;
    rateOfFire = RoF;
    reloadTime = reload;
    baseReloadTime = reloadTime;
    reloadSoundString = name;

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
            canShoot = true;
            isReloading = false;
            reloadTime = baseReloadTime;
        }
    } 
}


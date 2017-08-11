#include "include/Weapon.h"

Weapon::Weapon(std::string path)
{
    weaponTexture.loadFromFile(path.c_str());
    weapSprite.setTexture(weaponTexture);

    //Default attributes
    isEquiped = true;
    damage = 20;
    maxAmmo = 150;
    magazineSize = 25;
    ammoInMagazine = magazineSize;
    rateOfFire = 0.25f;
    canReload = false;
}

void Weapon::reload()
{
    if (ammoInMagazine == magazineSize) {
        canReload = false;
    } else {
        canReload = true;
    }
    
    if (maxAmmo > 0 && canReload) {
        maxAmmo -= magazineSize;
        ammoInMagazine = magazineSize;
    } 
}

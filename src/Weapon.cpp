#include "Weapon.h"

Weapon::Weapon()
{
    weaponTexture.loadFromFile("textures/entity/player.anim.png");
    weapSprite.setTexture(weaponTexture);

    isEquiped = true;
    damage = 25;
    maxAmmo = 75;
    magazineSize = 25;
    ammoInMagazine = magazineSize;
    rateOfFire = 12;
}

void Weapon::fire()
{
    if (ammoInMagazine > 0) {
        //Shoot a bullet
    } else {
        //play a click sound. Reload!!!
    }
}

void Weapon::reload()
{
    //Full mag
    if (maxAmmo > magazineSize) {
        maxAmmo -= magazineSize;
        ammoInMagazine = magazineSize;
    } else {
        //Partial mag
        if (maxAmmo > 0) {
            ammoInMagazine = maxAmmo;
            maxAmmo = 0;
        } else {
            //Play a harsher click sound. No ammo!!!
        }
    }
}

void Weapon::animate()
{
    //TODO: Do this after we get all other
    //weapon mechanics fully functional.
}

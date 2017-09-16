#include "include/Weapon.h"
#include "include/Player.h"

Weapon::Weapon(std::string path, float dmg, int ammoMax, int magSize, 
                    sf::Time RoF, sf::Time reload, std::string name)
{
    weaponTexture.loadFromFile(path.c_str());
    weapSprite.setTexture(weaponTexture);

    //Default attributes
    isEquipped = true;
    canFire = true;
    canReload = false; //Starts with a full mag
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
    //Do not fire bullets with no ammo
    //in the magazine.
    if (ammoInMagazine <= 0) {
        canFire = false;
    } else {
        canFire = true;
    }
    //If we have fired at least one bullet, 
    //allow for a reload to occur.
    if (ammoInMagazine < magazineSize) {
        canReload = true;
    } else {
        canReload = false;
    }
}


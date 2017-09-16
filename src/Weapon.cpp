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
    isReloading = false;
    damage = dmg;
    maxAmmo = ammoMax;
    magazineSize = magSize;
    ammoInMagazine = magazineSize;
    rateOfFire = RoF;
    reloadTime = reload;
    weaponName = name;
}

void Weapon::reload(SoundManager &soundmngr)
{   
    if (maxAmmo > 0 && canReload) {
        isReloading = true;
        maxAmmo -= magazineSize;
        ammoInMagazine = magazineSize;
        if (weaponName == "lmg") {
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
        if (isReloading) {
            canFire = false;
        } else {
            canFire = true;
        }
    }
    //If we have fired at least one bullet, 
    //allow for a reload to occur.
    if (ammoInMagazine < magazineSize) {
        canReload = true;
    } else { //Full magazine
        canReload = false;
    }
    
    if (isReloading) {
        static sf::Time workingTime = reloadTime;
        workingTime -= sf::milliseconds(10);
        if (workingTime.asMilliseconds() <= 0) {
            workingTime = reloadTime;
            isReloading = false;   
        }
    }
}









#include "include/Weapon.h"

Weapon::Weapon(std::string path, float dmg, int ammoMax, int magSize, 
                    sf::Time RoF, sf::Time reload, std::string name)
{
    weaponTexture.loadFromFile(path.c_str());
    weapSprite.setTexture(weaponTexture);

    //Default attributes
    isEquipped = false;
    canFire = true;
    canReload = false; //Starts with a full mag
    isReloading = false;
    damage = dmg;
    maxAmmo = ammoMax;
    startingAmmo = maxAmmo;
    magazineSize = magSize;
    ammoInMagazine = magazineSize;
    rateOfFire = RoF;
    reloadTime = reload;
    weaponName = name;
    baseReloadTime = reload;
}

void Weapon::reload(SoundManager &soundmngr)
{   
    if (maxAmmo > 0 && canReload) {
        isReloading = true;
        if (maxAmmo <= magazineSize) {
        	ammoInMagazine = maxAmmo;
        	maxAmmo = 0;
        } else {
			maxAmmo -= magazineSize;
			ammoInMagazine = magazineSize;
        }
        if (weaponName == "lmg") {
            soundmngr.playSoundByID(soundmngr.bnkWeaponEffects, "lmgReload");
        }
        if (weaponName == "pistol") {
        	soundmngr.playSoundByID(soundmngr.bnkWeaponEffects, "lmgReload");
        }
    }
}

void Weapon::resetWeapParams()
{
	ammoInMagazine = magazineSize;
	maxAmmo = startingAmmo;
}

void Weapon::update(Player &player)
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
    
    //Perform the reload
    if (isReloading) {
    	canReload = false;
        player.isReloading = true;
        reloadTime -= sf::milliseconds(10);
        if (reloadTime.asMilliseconds() <= 0) {
            reloadTime = baseReloadTime;
            player.isReloading = false;
            isReloading = false;   
        }
    }
}


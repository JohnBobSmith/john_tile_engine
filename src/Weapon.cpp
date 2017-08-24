#include "include/Weapon.h"
#include "include/Player.h"

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

void Weapon::update(Player &player)
{
    if (isReloading) {
        canShoot = false;
        reloadTime -= sf::milliseconds(10);
        if (reloadTime.asMilliseconds() <= 0) {
            canShoot = true;
            isReloading = false;
            reloadTime = baseReloadTime;
        }
        //Reload animation
        //*
        static int counter = 0;
        static sf::Time timer = sf::milliseconds(50);
        if (!canShoot) {
            timer -= sf::milliseconds(10);
            if (timer.asMilliseconds() <= 0.0f) {
                //Cycle through our body sheet
                player.body.setTextureRect(sf::IntRect(counter, 32, 22, 32));
                timer = sf::milliseconds(50);
            }
            counter += 22; //22 is the width of one sprite on the sheet
            //If we reached the end of the sheet, reset.
            if (counter == 88) {
                counter = 0;
            }
        }
        //*/
    } 
}















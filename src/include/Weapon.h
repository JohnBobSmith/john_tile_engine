#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "SoundManager.h"
#include "Player.h"

//Every weapon must have...
class Weapon
{
    public:
        //A way to load the texture and set default attributes
        Weapon(std::string path, float dmg, int ammoMax, int magSize, 
                    sf::Time RoF, sf::Time reload, std::string name);

        //A sprite
        sf::Sprite weapSprite;

        //A position
        sf::Vector2f position;

        //A way to know if we are using it or not
        bool isEquipped;
        
        //A way to know if we can fire the weapon or not
        bool canFire;
        
        //A way to know if we can reload the weapon or not
        bool canReload;
        
        //Are we in the act of reloading? 
        //Used to for our reload time mechanic.
        bool isReloading;
        
        //The damage that the weapon does
        float damage;

        //The maximum ammo
        int maxAmmo;
        
		//How much ammo we start with. 
		//This is a fixed value, used to
		//resuply and respawn as well.
		int startingAmmo;

        //Ammo in the magazine
        int ammoInMagazine;

        //Size of magazine
        int magazineSize;

        //How fast to shoot
        sf::Time rateOfFire;
        
        //A way to identify our weapon
        std::string weaponName;
        
        //How long our reload should last
        sf::Time reloadTime;

        //Reload our gun
        void reload(SoundManager &soundmngr);
        
        //Reset weapon paramaters
        void resetWeapParams();

        //Update the sprite
        void update(Player &player);

    private:
        //The weapons texture
        sf::Texture weaponTexture;
        
        //Our base reload time used to reset reloadTime
        sf::Time baseReloadTime;
};

#endif // WEAPON_H

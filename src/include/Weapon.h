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
        
        //Can we reload?
        bool canReload;
        
        //Can we shoot (used to prevent reloading 
        //and shooting at the same time)
        bool canShoot;
        
        //The damage that the weapon does
        float damage;

        //The maximum ammo
        int maxAmmo;

        //Ammo in the magazine
        int ammoInMagazine;

        //Size of magazine
        int magazineSize;

        //How fast to shoot
        sf::Time rateOfFire;
        
        //A way to identify our reload sound
        std::string reloadSoundString;
        
        //How long our reload should last
        sf::Time reloadTime;

        //Reload our gun
        void reload(SoundManager &soundmngr);

        //Update the sprite
        void update(Player &player);

    private:
        //The weapons texture
        sf::Texture weaponTexture;
        
        //Are we in the act of reloading?
        //To prevent shooting/reloading at the same time
        bool isReloading;
        
        //Our base reload time, used to reset reloadTime;
        sf::Time baseReloadTime;
};

#endif // WEAPON_H

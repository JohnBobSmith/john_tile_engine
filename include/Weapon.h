#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>

//Every weapon must have...
class Weapon
{
    public:
        Weapon();

        //A sprite
        sf::Sprite weapSprite;

        //A position
        sf::Vector2f position;

        //A way to know if we are using it or not
        bool isEquiped;

        //The damage that the weapon does
        float damage;

        //The maximum ammo
        int maxAmmo;

        //Ammo in the magazine
        int ammoInMagazine;

        //Size of magazine
        int magazineSize;

        //How fast to shoot
        float rateOfFire;

        //Shoot
        void fire();

        //Reload
        void reload();

        //Animate
        void animate();

    private:
        //The weapons texture
        sf::Texture weaponTexture;
};

#endif // WEAPON_H

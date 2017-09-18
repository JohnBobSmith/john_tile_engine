#ifndef RESUPLYSYSTEM_H
#define RESUPLYSYSTEM_H

#include <SFML/Graphics.hpp>
#include "Collision.h"
#include "Weapon.h"
#include "Player.h"

class ResuplySystem
{
    public:
        ResuplySystem();
        
        //We need the bounding box
        sf::RectangleShape bbox;
        
        //A way to check for collisions
        bool checkCollision(Collision &collison, Player &player);    
        
        //How much ammo to resupply
        int amountOfAmmo;
        
        //How much ammo the supply system has
        int maxAmmoSupply;
        
        //Perform the resuply.
        void resuply(Weapon &weapon);
};

#endif //RESUPPLYSYSTEM_H

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
        sf::RectangleShape ammoBox;
        sf::RectangleShape healthBox;
        
        //A way to check for collisions
        bool checkAmmoBoxCollision(Collision &collison, Player &player);    
        bool checkHealthBoxCollision(Collision &collision, Player &player);
        
        //How much ammo to resupply
        int amountOfAmmo;
        
        //How much ammo the supply system has
        int maxAmmoSupply;
        
        //How much health resupply
        int amountOfHealth;
        
        //How much health the supply system has
        int maxHealthSupply;
        
        //Perform the resuply.
        void resuplyAmmo(Weapon &weapon);
        void resuplyHealth(Player &player);
};

#endif //RESUPPLYSYSTEM_H

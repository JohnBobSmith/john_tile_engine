#include "include/ResuplySystem.h"
#include <iostream>

ResuplySystem::ResuplySystem()
{
    amountOfAmmo = 1;
    amountOfHealth = 2;
    maxAmmoSupply = 9999;
    maxHealthSupply = 9999;
    ammoBox.setOutlineColor(sf::Color::Green);
    ammoBox.setOutlineThickness(1);
    ammoBox.setFillColor(sf::Color::Transparent);
    ammoBox.setSize(sf::Vector2f(160, 128));
    ammoBox.setPosition(224, -224);
    healthBox.setOutlineColor(sf::Color::Green);
    healthBox.setOutlineThickness(1);
    healthBox.setFillColor(sf::Color::Transparent);
    healthBox.setSize(sf::Vector2f(96, 96));
    healthBox.setPosition(256, -128);
}

bool ResuplySystem::checkAmmoBoxCollision(Collision &collision, Player &player) 
{
    if (collision.checkAABBcollision(ammoBox.getPosition().x, ammoBox.getPosition().y,
                                    ammoBox.getSize().x, ammoBox.getSize().y,
                                    player.boundingBox.getPosition().x,
                                    player.boundingBox.getPosition().y,
                                    player.size.x, player.size.y)) {
        
        return true;   
    }
    return false;
}

bool ResuplySystem::checkHealthBoxCollision(Collision &collision, Player &player)
{
    if (collision.checkAABBcollision(healthBox.getPosition().x, healthBox.getPosition().y,
                                    healthBox.getSize().x, healthBox.getSize().y,
                                    player.boundingBox.getPosition().x,
                                    player.boundingBox.getPosition().y,
                                    player.size.x, player.size.y)) {
        
        return true;   
    }
    return false;
}

void ResuplySystem::resuplyAmmo(Weapon &weapon)
{
	static sf::Time timer = sf::milliseconds(100);
	timer -= sf::milliseconds(10);
	if (timer.asMilliseconds() <= 0) {
		if (maxAmmoSupply > 0 && weapon.maxAmmo < weapon.startingAmmo) {
		    weapon.maxAmmo += amountOfAmmo;
		    maxAmmoSupply -= amountOfAmmo;
		}
		timer = sf::milliseconds(100);
	}
}

void ResuplySystem::resuplyHealth(Player &player)
{
	static sf::Time timer = sf::milliseconds(100);
	timer -= sf::milliseconds(10);
	if (timer.asMilliseconds() <= 0) {
		if (maxHealthSupply > 0 && player.health < player.startingHealth) {
		    player.health += amountOfHealth;
		    maxHealthSupply -= amountOfHealth;
		}
		timer = sf::milliseconds(100);
	}
}

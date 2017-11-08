#include "../include/ResuplySystem.h"

ResuplySystem::ResuplySystem()
{
    amountOfAmmo = 1;
    maxAmmoSupply = 150;
    ammoBox.setOutlineColor(sf::Color::Black);
    ammoBox.setOutlineThickness(5);
    ammoBox.setFillColor(sf::Color::Transparent);
    ammoBox.setSize(sf::Vector2f(160, 128));
    ammoBox.setPosition(224, -224);
}

bool ResuplySystem::checkCollision(Collision &collision, Player &player) 
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

void ResuplySystem::resuply(Weapon &weapon)
{
	static sf::Time timer = sf::milliseconds(100);
	static int weaponMaxAmmo = weapon.maxAmmo;
	timer -= sf::milliseconds(10);
	if (timer.asMilliseconds() <= 0) {
		if (maxAmmoSupply > 0 && weapon.maxAmmo < weaponMaxAmmo) {
		    weapon.maxAmmo += amountOfAmmo;
		    maxAmmoSupply -= amountOfAmmo;
		}
		timer = sf::milliseconds(100);
	}
}


#include "../include/ResuplySystem.h"

ResuplySystem::ResuplySystem()
{
    amountOfAmmo = 1;
    maxAmmoSupply = 150;
    bbox.setOutlineColor(sf::Color::Black);
    bbox.setOutlineThickness(5);
    bbox.setFillColor(sf::Color::Transparent);
    bbox.setSize(sf::Vector2f(160, 128));
    bbox.setPosition(224, -224);
}

bool ResuplySystem::checkCollision(Collision &collision, Player &player) 
{
    if (collision.checkAABBcollision(bbox.getPosition().x, bbox.getPosition().y,
                                    bbox.getSize().x, bbox.getSize().y,
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
	timer -= sf::milliseconds(10);
	if (timer.asMilliseconds() <= 0) {
		if (weapon.maxAmmo < 150 && maxAmmoSupply > 0) {
		    weapon.maxAmmo += amountOfAmmo;
		    maxAmmoSupply -= amountOfAmmo;
		}
		timer = sf::milliseconds(100);
	}
}


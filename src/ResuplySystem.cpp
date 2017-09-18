#include "include/ResuplySystem.h"

ResuplySystem::ResuplySystem()
{
    amountOfAmmo = 25;
    maxAmmoSupply = 100;
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
    if (weapon.maxAmmo < 150 && maxAmmoSupply > 0) {
        weapon.maxAmmo += amountOfAmmo;
        maxAmmoSupply -= amountOfAmmo;
    }
}


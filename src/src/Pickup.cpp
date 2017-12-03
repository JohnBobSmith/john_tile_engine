#include "../include/Pickup.h"
#include <iostream>

Pickup::Pickup(sf::Vector2i objSize, std::string path)
{
	isPickedUp = false;

	size.x = objSize.x;
	size.y = objSize.y;
	
	if (!pickupTexture.loadFromFile(path.c_str())) {
		std::cout << "Missing texture file for Pickup::Pickup()...\n";
	}
	
	pickupSprite.setTexture(pickupTexture);
}

bool Pickup::load(sf::Vector2i objSize, std::string path)
{
	isPickedUp = false;
	
	size.x = objSize.x;
	size.y = objSize.y;
	
	if (!pickupTexture.loadFromFile(path.c_str())) {
		return false;
	}
	
	pickupSprite.setTexture(pickupTexture);
}

void Pickup::equip()
{
	isPickedUp = true;
}

void Pickup::drop()
{
	isPickedUp = false;
}

void Pickup::update()
{
	static int rotation = 0;
	rotation += 1;
	pickupSprite.setOrigin(7, 15);
	pickupSprite.setRotation(rotation);
}

bool Pickup::checkPickupCollision(Collision &collision, int xPos, int yPos, int width, int height)
{
	if (collision.checkAABBcollision(pickupSprite.getPosition().x, pickupSprite.getPosition().y,
									size.x, size.y, xPos, yPos, width, height)) {
		equip();
	}	
}


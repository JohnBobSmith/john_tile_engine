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
	
	if (isPickedUp) {
		static sf::Time timer = sf::milliseconds(1000);
		timer -= sf::milliseconds(1);
		if (timer.asMilliseconds() <= 0) {
			isPickedUp = false;
			timer = sf::milliseconds(1000);
		}
	}
}

bool Pickup::checkPickupCollision(Collision &collision, int xPos, int yPos, int width, int height)
{
	if (collision.checkAABBcollision(pickupSprite.getPosition().x, pickupSprite.getPosition().y,
									size.x, size.y, xPos, yPos, width, height)) {
		equip();
		return true;
	}
	return false;	
}

bool Pickup::spawn(int pointNumber) 
{
	if (pointNumber < 0 || pointNumber > MAX_SPAWN_POINTS) {
		return false;
	}
	
    for (int i = 0; i < MAX_SPAWN_POINTS; ++i) {
        spawnPoints.push_back(sf::Vector2f(0, 0));
    }
    spawnPoints[0].x = 75;
    spawnPoints[0].y = -300;
    spawnPoints[1].x = 200;
    spawnPoints[1].y = 50;
	spawnPoints[2].x = 300;
	spawnPoints[2].y = 50;
    spawnPoints[3].x = 400;
    spawnPoints[3].y = 50;
    spawnPoints[4].x = 500;
    spawnPoints[4].y = 50;
	spawnPoints[5].x = 600;
	spawnPoints[5].y = 50;
    spawnPoints[6].x = 700;
    spawnPoints[6].y = 50;
    spawnPoints[7].x = 800;
    spawnPoints[7].y = 50;
	spawnPoints[8].x = 900;
	spawnPoints[8].y = 50;
	spawnPoints[9].x = 1000;
	spawnPoints[9].y = 50;	
    
    pickupSprite.setPosition(spawnPoints[pointNumber]);
    
	return true;
}


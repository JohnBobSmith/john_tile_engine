#ifndef PICKUP_H
#define PICKUP_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Collision.h"

class Pickup
{
	public:
		Pickup(sf::Vector2i objSize, std::string path);
		sf::Sprite pickupSprite;
		sf::Texture pickupTexture;
		sf::Vector2i size;
	
		bool isPickedUp;
	
		bool load(sf::Vector2i objSize, std::string path);
		
		bool checkPickupCollision(Collision &collision, int xPos, int yPos, int width, int height);

		void equip();
		void drop();	
		void update();	
};

#endif //PICKUP_H

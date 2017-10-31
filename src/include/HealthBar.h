#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class HealthBar
{
	public:
		HealthBar();
	
		sf::RectangleShape healthBar;
	
		void update(Player &player);
};

#endif //HEALTH_BAR_H

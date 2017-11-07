#ifndef HEALTH_BAR_H
#define HEALTH_BAR_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class HealthBar
{
	public:
		HealthBar();
		
		//Our health bar shape	
		sf::RectangleShape healthBar;
		
		//Update everything
		void update(Player &player);
};

#endif //HEALTH_BAR_H

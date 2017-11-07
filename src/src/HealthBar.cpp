#include "../include/HealthBar.h"
#include <iostream>

HealthBar::HealthBar()
{
	healthBar.setFillColor(sf::Color::Red);
	healthBar.setSize(sf::Vector2f(50, 25));
}

void HealthBar::update(Player &player) 
{
	//Set the color acording to HP remaining
	sf::Color hpBarColor(player.health * 1.5, 0, 0);
	healthBar.setPosition(player.body.getPosition().x - 85,
          	           	  player.body.getPosition().y + 50);
	healthBar.setScale(player.health / 100, 1);
	healthBar.setFillColor(hpBarColor);
	if (player.health <= 0) {
		healthBar.setScale(0, 1);
	}
	std::cout << player.health << std::endl;
}

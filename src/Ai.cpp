#include "include/Ai.h"
#include <iostream>
#include <cmath>

Ai::Ai(std::string path)
{
	if (!aiSpriteTexture.loadFromFile(path.c_str())) {
		std::cerr << "Missing texture file:" << path;
	}
	
	aiSprite.setTexture(aiSpriteTexture);
	aiSprite.setTextureRect(sf::IntRect(0, 0, 22, 32));
	
	aiVision.setFillColor(sf::Color::Transparent);
	aiVision.setOutlineThickness(2);
	aiVision.setOutlineColor(sf::Color::Green);
	aiVision.setRadius(80);
	aiVision.setPointCount(50);
	aiVision.setPosition(100, -100);
}

void Ai::update()
{
	//std::cout << aiSprite.getPosition().x << " " << aiSprite.getPosition().y <<
	//			" " << aiVision.getPosition().x << " " << aiVision.getPosition().y << std::endl;
				
	aiVision.setPosition(aiSprite.getPosition().x - aiSprite.getPosition().x / 2,
						 aiSprite.getPosition().y + aiSprite.getPosition().y / 2);
}

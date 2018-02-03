#include "include/Ai.h"

Ai::Ai(std::string path)
{
	if (!aiSpriteTexture.loadFromFile(path.c_str())) {
		std::cerr << "Missing texture file:" << path;
	}
	
	aiSprite.setTexture(aiSpriteTexture);
	aiSprite.setTextureRect(sf::IntRect(0, 0, 22, 32));
	aiSprite.setOrigin(11, 16);
	
	aiVision.setFillColor(sf::Color::Transparent);
	aiVision.setOutlineThickness(2);
	aiVision.setOutlineColor(sf::Color::Green);
	aiVision.setRadius(80);
	aiVision.setPointCount(50);
	aiVision.setPosition(100, -300);
}

void Ai::trackTarget(Player &player)
{
	//Calcualte the sprites rotatiion with atan2.
    float angle = std::atan2(aiSprite.getPosition().y - player.body.getPosition().y,
    						aiSprite.getPosition().x - player.body.getPosition().x);
    angle = angle * 180 / M_PI;
    angle += 180;
    if (angle < 0) {
        angle = 360 -(-angle);
    }
    aiSprite.setRotation(90 + angle);
}

void Ai::update()
{
	//std::cout << aiSprite.getPosition().x << " " << aiSprite.getPosition().y <<
	//			" " << aiVision.getPosition().x << " " << aiVision.getPosition().y << std::endl;
				
	aiVision.setPosition(aiSprite.getPosition().x - aiSprite.getPosition().x / 2 - 22,
						 aiSprite.getPosition().y + aiSprite.getPosition().y / 2 - 16);
}

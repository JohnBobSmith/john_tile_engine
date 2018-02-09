#include "include/Ai.h"
#include <cmath>

void Ai::registerNewAi(std::vector<std::shared_ptr<jteAi>> &bnk)
{
    //Initialize our Ai's attributes.
    static int counter = 0;
    //Reset for a new bank.
    if (bnk.size() == 0) {
        counter = 0;
    }
    //Populate our ai bank.
    for (int i = counter; counter < i + 1; counter++) {
        bnk.push_back(std::make_shared<jteAi>());
        bnk[i]->aiTexture.loadFromFile("../textures/entity/ai.png");
        bnk[i]->aiSprite.setTexture(bnk[i]->aiTexture);
        bnk[i]->aiSprite.setOrigin(11, 16);
        bnk[i]->aiSprite.setTextureRect(sf::IntRect(0, 0, 22, 32));
		bnk[i]->aiVision.setFillColor(sf::Color::Transparent);
		bnk[i]->aiVision.setOutlineThickness(2);
		bnk[i]->aiVision.setOutlineColor(sf::Color::Green);
		bnk[i]->aiVision.setRadius(80);
		bnk[i]->aiVision.setPointCount(50);
    }
}

void Ai::trackTarget(Player &player, std::vector<std::shared_ptr<jteAi>> &bnk)
{
	//Calcualte the sprites rotatiion with atan2.
	for (int i = 0; i < bnk.size(); ++i) {
		bnk[i]->aiAngle = std::atan2(bnk[i]->aiSprite.getPosition().y - player.body.getPosition().y,
									bnk[i]->aiSprite.getPosition().x - player.body.getPosition().x);
		bnk[i]->aiAngle = bnk[i]->aiAngle * 180 / M_PI;
		bnk[i]->aiAngle += 180; //Invert the angle
		if (bnk[i]->aiAngle < 0) {
		    bnk[i]->aiAngle = 360 -(-bnk[i]->aiAngle);
		}
		bnk[i]->aiSprite.setRotation(90 + bnk[i]->aiAngle);
	}
}

void Ai::update(std::vector<std::shared_ptr<jteAi>> &bnk)
{				
	for (int i = 0; i < bnk.size(); ++i) {
		bnk[i]->aiSprite.setPosition(100, -100);
		bnk[i]->aiVision.setOrigin(bnk[i]->aiVision.getRadius(), bnk[i]->aiVision.getRadius());
		bnk[i]->aiVision.setPosition(bnk[i]->aiSprite.getPosition().x, bnk[i]->aiSprite.getPosition().y);	
	}
}


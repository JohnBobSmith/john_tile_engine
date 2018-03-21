#include "include/Ai.h"
#include <cmath>
#include <iostream>

void Ai::registerNewAi(std::vector<std::shared_ptr<jteAi>> &bnk, int spawnPointX, int spawnPointY)
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
		bnk[i]->aiVision.setRadius(110);
		bnk[i]->aiVision.setPointCount(50);
		bnk[i]->aiPersonalSpace.setFillColor(sf::Color::Transparent);
		bnk[i]->aiPersonalSpace.setOutlineThickness(2);
		bnk[i]->aiPersonalSpace.setOutlineColor(sf::Color::Blue);
		bnk[i]->aiPersonalSpace.setRadius(25);
		bnk[i]->aiPersonalSpace.setPointCount(50);
		bnk[i]->aiSpeed = 0.5;
		bnk[i]->aiSize.x = 15;
		bnk[i]->aiSize.y = 15;
		bnk[i]->bbox.setPosition(spawnPointX, spawnPointY);
        bnk[i]->bbox.setSize(sf::Vector2f(bnk[i]->aiSize.x, bnk[i]->aiSize.y));
        bnk[i]->bbox.setFillColor(sf::Color::Magenta);
    }
}

void Ai::trackTarget(Player &player, std::vector<std::shared_ptr<jteAi>> &bnk)
{
	//Calcualte the sprites rotatiion with atan2.
	for (unsigned int i = 0; i < bnk.size(); ++i) {
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

bool Ai::checkPlayerCollision(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk)
{
	for (unsigned int i = 0; i < bnk.size(); ++i) {
		if (collision.checkCircleToRectCollision(bnk[i]->aiVision, player.boundingBox.getPosition().x,
									player.boundingBox.getPosition().y, player.size.x, player.size.y)) {
									
			return true;
		}
	}
	return false;
}

bool Ai::checkPersonalSpaceCollision(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk)
{
	for (unsigned int i = 0; i < bnk.size(); ++i) {
		if (collision.checkCircleToRectCollision(bnk[i]->aiPersonalSpace, player.boundingBox.getPosition().x,
										   player.boundingBox.getPosition().y, player.size.x, player.size.y)) {							
			
			return true;
		}
	}
	return false;
}

bool Ai::checkLevelCollision(Collision &collision, std::vector<std::shared_ptr<jteAi>> &bnk)
{
	for (unsigned int i = 0; i < bnk.size(); ++i) {
		for (int j = 0; j < collision.MAX_COLLISION_BOXES; ++j) {
	    	if (collision.checkAABBcollision(bnk[i]->bbox.getPosition().x,
	    						bnk[i]->bbox.getPosition().y,
	    						bnk[i]->bbox.getSize().x, bnk[i]->bbox.getSize().y,
								collision.collVector[j]->bbox.getPosition().x,	
								collision.collVector[j]->bbox.getPosition().y,
								collision.collVector[j]->bbox.getSize().x,
								collision.collVector[j]->bbox.getSize().y)) {					

                return true;
			}
		}
	}
	return false;
}

void Ai::resolveCollisions(Collision &collision, std::vector<std::shared_ptr<jteAi>> &bnk)
{
	for (unsigned int i = 0; i < bnk.size(); ++i) {
		 if (checkLevelCollision(collision, bnk)) {
		    if (bnk[i]->aiDirectionY < 0) {
			    bnk[i]->bbox.move(0, bnk[i]->aiSpeed / 2);
		    }
		    if (bnk[i]->aiDirectionY > 0) {
			    bnk[i]->bbox.move(0, -bnk[i]->aiSpeed / 2);
		    }
		    if (bnk[i]->aiDirectionX < 0) {
			    bnk[i]->bbox.move(bnk[i]->aiSpeed / 2, 0);
		    } 
		    if (bnk[i]->aiDirectionX > 0) {
			    bnk[i]->bbox.move(-bnk[i]->aiSpeed / 2, 0);
		    }
		}
	}
}

void Ai::moveAi(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk)
{	
	float newDirX = 0;
	float newDirY = 0;

	for (unsigned int i = 0; i < bnk.size(); ++i) {
		if (!checkPersonalSpaceCollision(collision, player, bnk)) {	
			if (bnk[i]->aiSprite.getPosition().x - player.body.getPosition().x < 0) {
				newDirX = bnk[i]->aiSpeed;
			}
			if (bnk[i]->aiSprite.getPosition().x - player.body.getPosition().x > 0) {
				newDirX = -bnk[i]->aiSpeed;
			}
			if (bnk[i]->aiSprite.getPosition().y - player.body.getPosition().y < 0) {
				newDirY = bnk[i]->aiSpeed;
			} 
			if (bnk[i]->aiSprite.getPosition().y - player.body.getPosition().y > 0) {
				newDirY = -bnk[i]->aiSpeed;
			}
		}
		
		bnk[i]->aiDirectionX = newDirX;
		bnk[i]->aiDirectionY = newDirY;
		bnk[i]->bbox.move(bnk[i]->aiDirectionX, bnk[i]->aiDirectionY);
		bnk[i]->aiSprite.setPosition(bnk[i]->bbox.getPosition().x + 11, bnk[i]->bbox.getPosition().y + 11);
	}
}

void Ai::update(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk)
{				
	for (unsigned int i = 0; i < bnk.size(); ++i) {
		bnk[i]->aiVision.setPosition(bnk[i]->aiSprite.getPosition().x - bnk[i]->aiVision.getRadius(), 
									bnk[i]->aiSprite.getPosition().y - bnk[i]->aiVision.getRadius());	
									
		bnk[i]->aiPersonalSpace.setPosition(bnk[i]->aiSprite.getPosition().x - bnk[i]->aiPersonalSpace.getRadius(), 
											bnk[i]->aiSprite.getPosition().y - bnk[i]->aiPersonalSpace.getRadius());
							
		if (checkPersonalSpaceCollision(collision, player, bnk)) {
			//player.health -= 0.5;
		}
	}
}


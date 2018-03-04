#ifndef AI_H
#define AI_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Player.h"
#include "Collision.h"

class Ai
{
    public:
    	//Store our AI structs in an std::vector
    	struct jteAi
    	{
    		sf::Sprite aiSprite;
    		sf::Texture aiTexture;
    		sf::CircleShape aiVision;
    		sf::CircleShape aiPersonalSpace;
    		sf::Vector2i aiSize;
    		sf::RectangleShape bbox;
	    	float aiAngle;
	    	float aiDirectionX;
	    	float aiDirectionY;
	    	float aiSpeed;
	    	bool isRoaming;
	    	bool canMoveX;
	    	bool canMoveY;
    	};

        void registerNewAi(std::vector<std::shared_ptr<jteAi>> &bnk);
		void trackTarget(Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	void update(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	void moveAi(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	void resolveCollisions(Collision &collision, std::vector<std::shared_ptr<jteAi>> &bnk);
    	bool checkLevelCollision(Collision &collision, std::vector<std::shared_ptr<jteAi>> &bnk);
    	bool checkPlayerCollision(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	bool checkPersonalSpaceCollision(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	    	
        std::vector<std::shared_ptr<jteAi>> bnkAi;
};

#endif //AI_H

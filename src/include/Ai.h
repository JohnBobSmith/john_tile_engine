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
    		//Sprite and texture
    		sf::Sprite aiSprite;
    		sf::Texture aiTexture;
    		
    		//The AI's vision. Allows the AI to "see" the player.
    		sf::CircleShape aiVision;
    		
    		//Know when the player is too close to the AI. 
    		//Allows the AI to melee the player.
    		sf::CircleShape aiPersonalSpace;
    		
    		//The AI's size in pixels
    		sf::Vector2i aiSize;
    		
    		//The AI's bounding box.
    		sf::RectangleShape bbox;
    		
    		//The AI's rotation
	    	float aiAngle;
	    	
	    	//The AI's direction. A positive or negative value.
	    	//-1 is up or left, +1 is down or right
	    	float aiDirectionX;
	    	float aiDirectionY;
	    	
	    	//How fast is the AI?
	    	float aiSpeed;
    	};

		//Add an AI to the game
        void registerNewAi(std::vector<std::shared_ptr<jteAi>> &bnk, int spawnPointX, int spawnPointY);
        
        //Track the player
		void trackTarget(Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
		
		//Update things here. Called every frame.
    	void update(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);

		//Move the AI towards the player
    	void moveAi(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	
    	//Take care of collision checking.
    	void resolveCollisions(Collision &collision, std::vector<std::shared_ptr<jteAi>> &bnk);
    	
    	//Check vairous collisions. Returns true if collision else false.
    	bool checkLevelCollision(Collision &collision, std::vector<std::shared_ptr<jteAi>> &bnk);
    	bool checkPlayerCollision(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	bool checkPersonalSpaceCollision(Collision &collision, Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	
    	//The vector of AI's. 
        std::vector<std::shared_ptr<jteAi>> bnkAi;
};

#endif //AI_H

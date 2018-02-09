#ifndef AI_H
#define AI_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Player.h"

class Ai
{
    public:
    	//Store our AI structs in an std::vector
    	struct jteAi
    	{
    		sf::Sprite aiSprite;
    		sf::Texture aiTexture;
    		sf::CircleShape aiVision;
	    	float aiAngle;
    	};

        void registerNewAi(std::vector<std::shared_ptr<jteAi>> &bnk);
		void trackTarget(Player &player, std::vector<std::shared_ptr<jteAi>> &bnk);
    	void update(std::vector<std::shared_ptr<jteAi>> &bnk);
    	
        std::vector<std::shared_ptr<jteAi>> bnkAi;
};

#endif //AI_H

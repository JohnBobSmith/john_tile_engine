#ifndef AI_H
#define AI_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cmath>
#include "Player.h"
#include "Bullet.h"

class Ai : public Bullet
{
    public:
    	Ai(std::string path);
    	
        sf::Sprite aiSprite;
    	
    	sf::CircleShape aiVision;
    	
		void trackTarget(Player &player);
    	
    	void update();
    	
    private:
        sf::Texture aiSpriteTexture;
};

#endif //AI_H

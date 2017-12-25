#include "../include/Ai.h"
#include <iostream>

Ai::Ai(std::string path)
{
	if (!aiSpriteTexture.loadFromFile(path.c_str())) {
		std::cerr << "Missing texture file:" << path;
	}
	
	aiSprite.setTexture(aiSpriteTexture);
}

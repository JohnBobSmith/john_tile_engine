#ifndef AI_H
#define AI_H

#include <SFML/Graphics.hpp>
#include <string>

class Ai
{
    public:
    	Ai(std::string path);
        sf::Sprite aiSprite;
    
    private:
        sf::Texture aiSpriteTexture;
};

#endif //AI_H

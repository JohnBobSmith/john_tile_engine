#ifndef SHADERS_H
#define SHADERS_H

#include <SFML/Graphics.hpp>

class Shader
{
    public:
        Shader();
        sf::Shader deathShader;
        sf::CircleShape deathShape;
};

#endif // SHADERS_H
#ifndef SHADERS_H
#define SHADERS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Shader
{
    public:
        Shader();
        //Our shader and a shape to draw it on
        sf::Shader deathShader;
        sf::CircleShape deathShape;

        //Animate our shader, with an on/off switch.
        void animate(bool isAnimated);
};

#endif // SHADERS_H

#ifndef ANIMATEDPROPS_H
#define ANIMATEDPROPS_H

#include <SFML/Graphics.hpp>

class AnimatedProps
{
    public:
        AnimatedProps();
        //Run the animations
        void animate();
        //Required sprites
        sf::Sprite windmill;

    private:
        //The required texture file
        sf::Texture texture;
};

#endif // ANIMATEDPROPS_H

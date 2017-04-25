#ifndef ANIMATEDPROPS_H
#define ANIMATEDPROPS_H

#include <SFML/Graphics.hpp>

class AnimatedProps
{
    public:
        AnimatedProps();
        //Do the animations
        void animate();
        //Required sprites. Max 4
        sf::Sprite windmill;

    private:
        //The require texture file
        sf::Texture texture;
};

#endif // ANIMATEDPROPS_H

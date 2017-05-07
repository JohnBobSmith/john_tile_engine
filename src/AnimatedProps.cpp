#include "../include/AnimatedProps.h"
#include <iostream>

AnimatedProps::AnimatedProps()
{
    if (!texture.loadFromFile("textures/level/animatedprops.png")) {
        std::cerr << "Failed to load textures/level/animatedprops.png...\n";
    }
    windmill.setTexture(texture);
    windmill.setPosition(0, 0);
    windmill.setTextureRect(sf::IntRect(32, 32, 32, 32));
}

void AnimatedProps::animate()
{
    //Animate the props
    static int counter = 32;
    static float timer = 20.0f;
    timer -= 1.0f;
    if (timer <= 1.0f) {
        //Cycle through our sprite sheet
        windmill.setTextureRect(sf::IntRect(counter, 0, 32, 32));
        timer = 20.0f;
    }
    counter += 32; //32 is the width of one sprite on the sheet
    //If we reached the end of the sheet, reset.
    if (counter == 96) {
        counter = 32;
    }
}

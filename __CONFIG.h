#ifndef __CONFIG_H
#define __CONFIG_H

#include <SFML/Graphics.hpp>
#include <string>

class __CONFIG
{
    public: //Allow for easy access of all variables.
        std::string getAppName() { return APP_NAME; }
        int getScreenWidth() { return SCREEN_WIDTH; }
        int getScreenHeight() { return SCREEN_HEIHGT; }
        sf::Color getWindowClearColor() { return WIN_CLEAR_COLOR; }

        //Defined in __CONFIG.cpp
        sf::Color setWindowClearColor(sf::Color color);

    private: //Explanations below...
        //The window name
        std::string APP_NAME = "The Adventures of Ironville";
        //Screen dimensions
        int SCREEN_WIDTH = 480;
        int SCREEN_HEIHGT = 480;

        //The window.clear() color.
        //Changing this may be useful if we want
        //to fake the appearance of a skyline or other
        //background without additional sprites/textures.
        sf::Color WIN_CLEAR_COLOR = sf::Color::White;
};

#endif // __CONFIG_H

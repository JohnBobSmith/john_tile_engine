#ifndef __CONFIG_H
#define __CONFIG_H

#include <SFML/Graphics.hpp>
#include <string>

class __CONFIG
{
    public: //Allow for easy access of all variables.
        __CONFIG();
        std::string getAppName() { return APP_NAME; }
        int getScreenWidth() { return SCREEN_WIDTH; }
        int getScreenHeight() { return SCREEN_HEIHGT; }
        sf::Vector2i getScreenSize() { return SCREEN_SIZE; }

    private:
        //The window name
        std::string APP_NAME = "The Adventures of Squareville";
        //Screen dimensions
        int SCREEN_WIDTH = 480;
        int SCREEN_HEIHGT = 480;

        //Screen dimensions, using a vector.
        sf::Vector2i SCREEN_SIZE;
};

#endif // __CONFIG_H

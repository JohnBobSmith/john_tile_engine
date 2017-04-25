#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
#include <string>

class Config
{
    public:
        Config();
        std::string getAppName() { return appName; }
        int getScreenWidth() { return screenWidth; }
        int getScreenHeight() { return screenHeight; }
        sf::Vector2i getScreenSize() { return screenSize; }

        //The level that is loaded
        std::string LEVEL_STRING = "grassland";

    private:
        //The window name
        std::string appName = "World Testing";
        //Screen dimensions
        int screenWidth = 480;
        int screenHeight = 480;
        //Screen dimensions, using an sf::Vector.
        sf::Vector2i screenSize;
};

#endif //CONFIG_H

#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
#include <unordered_set>
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

        const std::unordered_set<int> objectsInGrassland = {3, 6, 7, 10, 11, 12};
        const std::unordered_set<int> objectsInFarmland = {3, 7, 8};
        const std::unordered_set<int> objectsInAnimprop = {1, 4};

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

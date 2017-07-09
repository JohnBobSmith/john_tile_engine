#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/Graphics.hpp>
#include <unordered_set>
#include <string>

class Config
{
    public:
        //Init our variables
        Config();

        //Self explanatory functions for retrieving data
        std::string getAppName() { return appName; }
        int getScreenWidth() { return screenWidth; }
        int getScreenHeight() { return screenHeight; }
        sf::Vector2i getScreenSize() { return screenSize; }

        //The objects in our tilemap to collide with
        const std::unordered_set<int> objectsInGrassland = {0, 3, 6, 7, 10, 11, 12};
        const std::unordered_set<int> objectsInFarmland = {0, 3, 7, 8, 9, 10, 11, 13, 14, 15};
        const std::unordered_set<int> objectsInAnimprop = {1, 4};
        const std::unordered_set<int> objectsInRockland = {0, 3, 5, 10, 11, 14, 15};
        const std::unordered_set<int> objectsInJungleland = {0, 3};

        //Audio collision boxes
        const std::unordered_set<int> grasslandGrass = {1, 4, 5, 8, 9};
        const std::unordered_set<int> grasslandShrubs = {2};
        const std::unordered_set<int> farmlandGrass{1};
        const std::unordered_set<int> farmlandRoad{12};
        const std::unordered_set<int> farmlandCropAndShrub{2, 4, 5, 6};
        const std::unordered_set<int> rocklandGrass{1, 2};
        const std::unordered_set<int> rocklandDirt{4, 6, 7};

    private:
        //The window name
        std::string appName = "The Adventures of Stickman";
        //Screen dimensions
        int screenWidth = 480;
        int screenHeight = 480;
        //Screen dimensions, using an sf::Vector.
        sf::Vector2i screenSize;
};

#endif //CONFIG_H

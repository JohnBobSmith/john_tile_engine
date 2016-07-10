#include "World.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

void World::clearLevel()
{
    //Empty the current level vector.
    currentLevel.clear();
}

bool World::loadNewLevel(std::string levelName, std::string tileset)
{
    //Clear the contents of our level
    clearLevel();

    //Load new contents in its place
    if (!loadLevelFromDisk(levelName)) {
        return false;
    }

    //Apply them to the engine
    if (!load(tileset, sf::Vector2u(32, 32), 15, 15)) {
        return false; //Error no tile image
    }

    return true;
}

bool World::loadLevelFromDisk(std::string pathToMapFile)
{
    //Our file object
    std::ifstream file(pathToMapFile);

    //Store our characters
    char charOne, charTwo;

    //store our working data
    int dataOne, dataTwo;

    //Final data
    int finalData;

    if (!file.is_open()) {
        //Error...
        return false;
    } else { //File is ready to use
         while (file)
        {
            //Grab a single character
            charOne = file.get();

            //Grab a second character
            charTwo = file.get();

            //Compare the two characters...
            //If charOne contains a number and charTwo contains a comma...
            if ((charOne >= '0' && charOne <= '9') && charTwo == ',') {
                //We've ran into a single digit number.
                //Convert charOne to ASCII integer and
                //use this value in our final data.
                dataOne = charOne - 48;
                finalData = dataOne;
            }

            //Repeat with inverse char's checked
            if ((charTwo >= '0' && charTwo <= '9') && charOne == ',') {
                //We've ran into a single digit number.
                //Convert charTwo to ASCII integer and
                //use this value in our final data.
                dataTwo = charTwo - 48;
                finalData = dataTwo;
            }

            //However, if both values contain a number,
            //we have a compound number IE 12.
            if ((charOne >= '0' && charOne <= '9') && (charTwo >= '0' && charTwo <= '9')) {
                //Convert both to ASCII integers
                dataOne = charOne - 48;
                dataTwo = charTwo - 48;

                //Add the integers together + 9
                //This allows for numbers > 9.
                finalData = ((dataOne + dataTwo) + 9);
            }

            //update our level vector.
            currentLevel.push_back(finalData);
        }
    }
    return true;
}

bool World::load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height)
{
    //Do we have our m_tileset texture?
    if (!m_tileset.loadFromFile(tileset)) {
        return false;
    }

    //Fit the vertex array to the texture
    m_vertecies.setPrimitiveType(sf::Quads);
    m_vertecies.resize(width * height * 4);

    //Populate the vertex array, one quad per tile
    for (unsigned int i = 0; i < width; ++i) {
        for (unsigned int j = 0; j < height; ++j) {

            //Grab the current tile
            int tileNumber = currentLevel[i + j * width];

            //std::cout << tileNumber;

            //Find its position on the texture
            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            //Get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertecies[(i + j * width) * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            // define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    }
    return true;
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    //Apply all transformations and texture information.
    states.transform *= getTransform(); //Inherited function from sf::Transformable
    states.texture = &m_tileset;

    //Draw everything
    target.draw(m_vertecies, states);
}

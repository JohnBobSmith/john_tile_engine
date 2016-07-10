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

    //Store contents of file
    char tempData;

    if (!file.is_open()) {
        //Error...
        return false;
    } else { //File is ready to use
         while (file)
        {
            //Grab one character.
            tempData = file.get();

            //Discard newline and other junk characters.
            if ( tempData < '0' || tempData > '9' ) {
                continue;
            }

            //Convert that character to ascii integer
            int data = tempData - 48;

            //Our level vector.
            currentLevel.push_back(data);
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

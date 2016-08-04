#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

//Setup our game engine/world as a tiling engine
class World : public sf::Drawable, public sf::Transformable
{
    public:
        //Prevent level errors...
        World();

        //Clear previous level data
        void clearLevel();

        //Do stuff with out data IE validate it.
        bool processLevelData(std::string pathToMapFile);

        //Change levels
        bool loadNewLevel(std::string levelName, std::string tileset, sf::Vector2u tileSize,
                                        unsigned int tileWidth, unsigned int tileHeight);

        //Load our level file from disk
        bool loadLevelFromDisk(std::string pathToMapFile);

        /*
            Load our tile map into the application.

            Arguments from left to right:
            -The texture file to load
            -The size in pixels of each tile on the map
            -The width of the tile map
            -The height of the tile map
        */
        bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);

    private:
        //Our modified draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //Store texture and vertex data
        sf::VertexArray m_vertecies;
        sf::Texture m_tileset;

        //Store our level as a vector
        std::vector<long int> currentLevel;
};

#endif // WORLD_H

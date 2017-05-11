#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

//Setup our game engine/world as a tiling engine
class World : public sf::Drawable, public sf::Transformable
{
    public:
        //Init and cleanup our world
        World();
        ~World();

        //Maximum collision boxes, for bounds checking and what not
        static const int MAX_COLLISION_BOXES = 2048;

        //Clear previous level data
        void clearLevel();

        //Do stuff with our data IE validate it.
        bool processLevelData(std::string pathToMapFile);

        //Change and load levels
        bool loadNewLevel(std::string levelName, std::string tileset);
        /*
            Load our tile map into the application.

            Arguments from left to right:
            -The texture file to load
            -The size in pixels of each tile on the map
            -The width of the tile map
            -The height of the tile map
        */
        bool load(const std::string& tileset, sf::Vector2u tileSize, unsigned int width, unsigned int height);

        //Store our level as a vector
        std::vector<long int> currentLevel;

    private:
        //Our modified draw function
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        //Store texture and vertex data
        sf::VertexArray m_vertecies;
        sf::Texture m_tileset;
};

#endif // WORLD_H

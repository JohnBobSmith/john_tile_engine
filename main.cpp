#include <SFML/Graphics.hpp>
#include "__CONFIG.h"
#include "World.h"
#include <iostream>

int main()
{
    //Allow for use of __CONFIG
    __CONFIG config;

    //Should the game/main loop run?
    bool isRunning = true;

    //Allow for event handling
    sf::Event event;

    //Setup our render window using variables from __CONFIG.
    sf::RenderWindow window(sf::VideoMode(config.getScreenWidth(),\
                                        config.getScreenHeight()),\
                                        config.getAppName());
    //World object
    World world;

    //Load our level file
    world.loadLevelFromDisk("mapfile.map");

    //Set it up to work in-game.
    if (!world.load("textures/tilemap.png", sf::Vector2u(32, 32), 16, 16)) {
        isRunning = false;
        return -1; //Error no tile image
    }

    while (isRunning)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
        }
        //Basic window stuff here.
        window.clear(config.getWindowClearColor());
        window.draw(world);
        window.display();
    }
    return 0; //No error
}

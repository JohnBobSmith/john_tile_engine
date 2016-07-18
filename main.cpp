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

    //World object
    World world;

    //Setup our render window using variables from __CONFIG.
    sf::RenderWindow window(sf::VideoMode(config.getScreenWidth(),\
                                        config.getScreenHeight()),\
                                        config.getAppName());

    if (!world.loadNewLevel("levels/level01.map", "textures/base/level01.png")) {
        std::cout << "cannot load level...";
        return -1;
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

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

    world.loadNewLevel("mapfile.map");
    int time = 9000;

    while (isRunning)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
        }

        time--;
        std::cout << time;

        if (time <= 0) {
            world.loadNewLevel("level01.map");
        }

        //Basic window stuff here.
        window.clear(config.getWindowClearColor());
        window.draw(world);
        window.display();
    }
    return 0; //No error
}

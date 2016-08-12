#include <SFML/Graphics.hpp>
#include "__CONFIG.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
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

    //Camera object
    Camera camera;

    //Player object
    Player player;

    //Setup our render window using variables from __CONFIG.
    sf::RenderWindow window(sf::VideoMode(config.getScreenWidth(),\
                                        config.getScreenHeight()),\
                                        config.getAppName());

    window.setFramerateLimit(60); //Cap frame rate.
    window.setKeyRepeatEnabled(false); //Disable key repeating

    //Center camera on player once.
    camera.setCamCenter(player.getPlayerPosition());

    //Zoom it in just slightly.
    camera.zoomCam(-2.0);

    //Load levels
    if (!world.loadNewLevel("levels/level01.map", "textures/levels/level01.png")) {
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
            player.handleEvents(event);
        }

        //Basic window stuff here.
        window.clear(config.getWindowClearColor());

        //Move our player
        player.move(1/60.0f);

        //Update camera
        camera.moveCam(player.getPlayerPosition().x, player.getPlayerPosition().y);
        window.setView(camera.getCamera());

        //Draw and display the world.
        window.draw(world);
        window.draw(player.player);
        window.display();
    }
    return 0; //No error
}

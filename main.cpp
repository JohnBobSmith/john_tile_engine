#include <SFML/Graphics.hpp>
#include "__CONFIG.h"
#include "World.h"
#include "Camera.h"
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
                camera.zoomCam(1.1f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                camera.zoomCam(0.9f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                camera.moveCam(-5.0f, 0.0f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                camera.moveCam(5.0f, 0.0f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                camera.moveCam(0.0f, -5.0f);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                camera.moveCam(0.0f, 5.0f);
            }
        }

        //Basic window stuff here.
        window.clear(config.getWindowClearColor());

        //Update camera
        window.setView(camera.getCamera());

        //Draw and display the world.
        window.draw(world);
        window.display();
    }
    return 0; //No error
}

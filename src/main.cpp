#include <SFML/Graphics.hpp>
#include "Config.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "Collision.h"
#include <iostream>

int main()
{
    //Initialize our objects
    Config config;
    //Base world without collision
    World world;
    //Additional "worlds" which we will
    //check collision against.
    World brickland;
    //Our collision class
    Collision collision;
    Camera camera;
    Player player;

    //Initialize SFML
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(config.getScreenWidth(),\
                                        config.getScreenHeight()),\
                                        config.getAppName());
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    //Are we running the game?
    bool isRunning = true;

    //Determine which level we are loading
    std::string LEVEL_STRING = "grassland";

    //Load our levels
    if (!world.loadNewLevel("map/grassland.map", "textures/level/tileset.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: grassland.map";
        return -1;
    }

    if (!brickland.loadNewLevel("map/brickland.map", "textures/level/tileset.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: brickland.map";
        return -1;
    }

    //We need a sprite to display our cloud image
    sf::Sprite cloudsBackground;
    sf::Texture cloudsTexture;
    cloudsTexture.setRepeated(true);
    cloudsTexture.loadFromFile("textures/level/clouds.png");
    cloudsBackground.setTexture(cloudsTexture);
    cloudsBackground.setTextureRect(sf::IntRect(0, 0, config.getScreenWidth() * 4, config.getScreenHeight() * 4));
    cloudsBackground.setPosition(-500, -500);

    //Init the player
    player.sprite.setPosition(280, 280);
    player.setTexture("textures/entity/player.png");

    //Init the camera
    camera.setCamCenter(player.sprite.getPosition());

    //Position our collision boxes
    static int x = 0;
    static int y = 0;
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        collision.collVector[i]->setPosition(x, y);
        x += 32;
        if (i == 15) {
            x = 32;
            y = 480;
        }
    }
    y = 0;
    for (int i = 30; i < collision.MAX_COLLISION_BOXES; ++i) {
        collision.collVector[i]->setPosition(0, y);
        y += 32;

    }
    y = 0;
    for (int i = 46; i < collision.MAX_COLLISION_BOXES; ++i) {
        collision.collVector[i]->setPosition(480, y);
        y += 32;
    }


    //Game loop.
    while (isRunning) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
            player.handlePlayerEvents(event);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                LEVEL_STRING = "grassland";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                LEVEL_STRING = "brickland";
            }
        }

        //Clear, move, and draw
        window.clear();
        window.draw(cloudsBackground);
        window.setView(camera.getCamera());
        if (LEVEL_STRING == "grassland") {
            window.draw(world);
        }
        if (LEVEL_STRING == "brickland") {
            window.draw(brickland);
        }
        //Draw collision boxes
        /*
        for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
            window.draw(*collision.collVector[i]);
        }
        //*/
        //Resolve collisions before moving the player
        for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
            if (collision.checkAABBcollision(player.sprite.getPosition().x, player.sprite.getPosition().y,
                                             player.size.x, player.size.y,
                                             collision.collVector[i]->getPosition().x,
                                             collision.collVector[i]->getPosition().y,
                                             collision.collVector[i]->getSize().x,
                                             collision.collVector[i]->getSize().y)) {
                if (player.position.x == -1) {
                    player.sprite.move(1, 0);
                }
                if (player.position.x == 1) {
                    player.sprite.move(-1, 0);
                }
                if (player.position.y == 1) {
                    player.sprite.move(0, -1);
                }
                if (player.position.y == -1) {
                    player.sprite.move(0, 1);
                }
                camera.setCamCenter(sf::Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y));
            }
        }
        player.movePlayer();
        camera.moveCam(player.position.x, player.position.y);
        window.draw(player.sprite);

        window.display();
    }
    return 0;
}

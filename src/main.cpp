#include <SFML/Graphics.hpp>
#include "Config.h"
#include "World.h"
#include "Camera.h"
#include "Player.h"
#include "Collision.h"
#include "AnimatedProps.h"
#include <iostream>

int main()
{
    //Initialize our objects
    Config config;
    //Load our worlds
    World grassland;
    World farmland;
    World flags;
    //Animated props
    World animPropsWorld;
    AnimatedProps animprops;
    //Store a different set of collision
    //boxes for different events.
    Collision collision;
    Collision flagsCollision;
    Collision grasslandCollision;
    Collision farmlandCollision;
    //Change flagsCollision fill color
    for (int i = 0; i < flagsCollision.MAX_COLLISION_BOXES; ++i) {
        flagsCollision.collVector[i]->setFillColor(sf::Color::Magenta);
    }
    //Change grasslandCollision fill color
    for (int i = 0; i < grasslandCollision.MAX_COLLISION_BOXES; ++i) {
        grasslandCollision.collVector[i]->setFillColor(sf::Color::Yellow);
    }
    //Change farmlandCollision fill color
    for (int i = 0; i < farmlandCollision.MAX_COLLISION_BOXES; ++i) {
        farmlandCollision.collVector[i]->setFillColor(sf::Color::White);
    }
    //Camera and player
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

    //Load our levels
    if (!grassland.loadNewLevel("map/grassland.map", "textures/level/grassland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: grassland.map";
        return -1;
    }

    if (!farmland.loadNewLevel("map/farmland.map", "textures/level/farmland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: farmland.map";
        return -1;
    }

    if (!flags.loadNewLevel("map/flags.map", "textures/level/flags.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: flags.map";
        return -1;
    }

    if (!animPropsWorld.loadNewLevel("map/animprops.map", "textures/level/animatedprops.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: animprops.map";
        return -1;
    }

    //We need a sprite to display our cloud background image
    sf::Sprite cloudsBackground;
    sf::Texture cloudsTexture;
    cloudsTexture.setRepeated(true);
    cloudsTexture.loadFromFile("textures/level/clouds.png");
    cloudsBackground.setTexture(cloudsTexture);
    cloudsBackground.setTextureRect(sf::IntRect(0, 0, config.getScreenWidth() * 4, config.getScreenHeight() * 4));
    cloudsBackground.setPosition(-500, -500);

    //Init the player
    player.sprite.setPosition(32, 32);
    player.setTexture("textures/entity/player.anim.png");
    player.sprite.setTextureRect(sf::IntRect(0, 0, 22, 32));

    //Init the camera
    camera.setCamCenter(player.sprite.getPosition());

    //Position collision boxes on the edge of the map
    collision.positionBoundaryCollisionBoxes();
    //Position our world/level collision boxes
    grasslandCollision.positionWorldCollisionBoxes(grassland.currentLevel, "grassland");
    farmlandCollision.positionWorldCollisionBoxes(farmland.currentLevel, "farmland");
    //Position the collision boxes for our flags
    for (int i = 0; i < flagsCollision.MAX_COLLISION_BOXES; ++i) {
        flagsCollision.collVector[i]->setPosition(0, 0);
    }
    //Top flag
    flagsCollision.collVector[0]->setPosition(224, 32);
    //Left flag
    flagsCollision.collVector[1]->setPosition(32, 224);
    //Right flag
    flagsCollision.collVector[2]->setPosition(448, 224);
    //Bottom flag
    flagsCollision.collVector[3]->setPosition(224, 448);

    //Game loop.
    while (isRunning) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
            player.handlePlayerEvents(event);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
                config.LEVEL_STRING = "grassland";
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                config.LEVEL_STRING = "farmland";
            }
        }

        //Clear, move, and draw
        window.clear();
        window.draw(cloudsBackground);
        window.setView(camera.getCamera());
        if (config.LEVEL_STRING== "grassland") {
            window.draw(grassland);
        }
        if (config.LEVEL_STRING== "farmland") {
            window.draw(farmland);
            //Position the animated prop
            animprops.windmill.setPosition(128, 320);
            animprops.animate();
            //Draw the sprite on top of the world
            window.draw(animPropsWorld);
            window.draw(animprops.windmill);
        }
        window.draw(flags);
        //Draw collision boxes
        /*
        for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
            window.draw(*collision.collVector[i]);
            window.draw(*flagsCollision.collVector[i]);
            window.draw(*grasslandCollision.collVector[i]);
            window.draw(*farmlandCollision.collVector[i]);
        }
        //*/
        //Resolve collisions before moving the player
        player.checkCollision(collision, camera);

        //Collisions within our grasslands levels
        if (config.LEVEL_STRING == "grassland") {
            for (int i = 0; i < grasslandCollision.MAX_COLLISION_BOXES; ++i) {
                if (grasslandCollision.checkAABBcollision(player.sprite.getPosition().x, player.sprite.getPosition().y,
                                                 player.size.x - 8, player.size.y,
                                                 grasslandCollision.collVector[i]->getPosition().x,
                                                 grasslandCollision.collVector[i]->getPosition().y,
                                                 grasslandCollision.collVector[i]->getSize().x,
                                                 grasslandCollision.collVector[i]->getSize().y)) {

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
        }

        //Collisions within our farmland levels
        if (config.LEVEL_STRING == "farmland") {
            for (int i = 0; i < farmlandCollision.MAX_COLLISION_BOXES; ++i) {
                if (farmlandCollision.checkAABBcollision(player.sprite.getPosition().x, player.sprite.getPosition().y,
                                                 player.size.x - 8, player.size.y,
                                                 farmlandCollision.collVector[i]->getPosition().x,
                                                 farmlandCollision.collVector[i]->getPosition().y,
                                                 farmlandCollision.collVector[i]->getSize().x,
                                                 farmlandCollision.collVector[i]->getSize().y)) {

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
        }

        //Did the player touch a flag?
        //If so, change levels.
        static bool isLevelChanged = false;
        for (int i = 0; i < flagsCollision.MAX_COLLISION_BOXES; ++i) {
            if (collision.checkAABBcollision(player.sprite.getPosition().x, player.sprite.getPosition().y,
                                             player.size.x - 8, player.size.y,
                                             flagsCollision.collVector[i]->getPosition().x,
                                             flagsCollision.collVector[i]->getPosition().y,
                                             flagsCollision.collVector[i]->getSize().x,
                                             flagsCollision.collVector[i]->getSize().y)) {

                if (config.LEVEL_STRING == "farmland" && !isLevelChanged) {
                    config.LEVEL_STRING = "grassland";
                    isLevelChanged = true;
                }
                if (config.LEVEL_STRING == "grassland" && !isLevelChanged) {
                    config.LEVEL_STRING = "farmland";
                    isLevelChanged = true;
                }
                //Position our player depending on which
                //flag he hit.
                //Left Flag
                if (player.sprite.getPosition().x < 80) {
                    player.sprite.setPosition(400, 224);
                }
                //Right flag
                if (player.sprite.getPosition().x > 410) {
                    player.sprite.setPosition(85, 224);
                }
                //Top flag
                if (player.sprite.getPosition().y < 80) {
                    player.sprite.setPosition(224, 400);
                }
                //Bottom flag
                if (player.sprite.getPosition().y > 410) {
                    player.sprite.setPosition(224, 85);
                }
                camera.setCamCenter(sf::Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y));
            }
        }
        if (isLevelChanged) {
            isLevelChanged = false;
        }
        player.animate();
        player.movePlayer();
        camera.moveCam(player.position.x, player.position.y);
        window.draw(player.sprite);
        window.display();
    }
    return 0;
}

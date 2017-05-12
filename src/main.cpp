#include <SFML/Graphics.hpp>
#include "../include/Config.h"
#include "../include/World.h"
#include "../include/Camera.h"
#include "../include/Player.h"
#include "../include/Collision.h"
#include "../include/AnimatedProps.h"
#include "../include/Flags.h"
#include <iostream>

int main()
{
    //Initialize our objects
    Config config;
    Flags flagObject;
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
    Collision animPropsCollision;
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
    //Change animPropsCollision fill color
    for (int i = 0; i < animPropsCollision.MAX_COLLISION_BOXES; ++i) {
        animPropsCollision.collVector[i]->setFillColor(sf::Color::Green);
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
    cloudsBackground.setTextureRect(sf::IntRect(0, 0, config.getScreenWidth() * 4,
                                                   config.getScreenHeight() * 4));
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
    grasslandCollision.positionWorldCollisionBoxes(grassland.currentLevel, config.objectsInGrassland);
    farmlandCollision.positionWorldCollisionBoxes(farmland.currentLevel, config.objectsInFarmland);
    flagObject.positionFlags(flagsCollision);

    //Game loop.
    while (isRunning) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
            player.handlePlayerEvents(event);
        }

        //Clear, move, and draw
        window.clear();
        window.draw(cloudsBackground);
        window.setView(camera.getCamera());
        //Resolve collisions before moving the player
        player.checkCollision(collision, camera);
        player.checkCollision(animPropsCollision, camera);
        flagObject.checkCollision(flagsCollision, camera, player, config);
        //Draw the specific levels
        if (config.LEVEL_STRING== "grassland") {
            player.checkCollision(grasslandCollision, camera);
            window.draw(grassland);
        }
        if (config.LEVEL_STRING== "farmland") {
            player.checkCollision(farmlandCollision, camera);
            window.draw(farmland);
            //Position the animated prop
            animprops.windmill.setPosition(128, 320);
            animPropsCollision.positionWorldCollisionBoxes(animPropsWorld.currentLevel,
                                                             config.objectsInAnimprop);
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
        player.animate();
        player.movePlayer();
        camera.moveCam(player.position.x, player.position.y);
        window.draw(player.sprite);
        window.display();
    }
    return 0;
}

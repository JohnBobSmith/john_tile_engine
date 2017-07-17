#include <SFML/Graphics.hpp>
#include "../include/Config.h"
#include "../include/World.h"
#include "../include/Camera.h"
#include "../include/Player.h"
#include "../include/Collision.h"
#include "../include/AnimatedProps.h"
#include "../include/SoundManager.h"
#include "../include/Shader.h"
#include "../include/Mouse.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main()
{
    //Random numbers
    srand(time(NULL));

    //Initialize our objects
    Config config;
    SoundManager soundmngr;
    Shader shader;
    Mouse mouse;

    //Load our worlds
    World grassland;
    World farmland;
    World rockland;
    World jungleland;

    //Animated props
    World animPropsWorld;
    AnimatedProps animprops;

    //Store a different set of collision
    //boxes for different events.
    Collision grasslandCollision(sf::Color::Black);
    Collision farmlandCollision(sf::Color::Black);
    Collision animPropsCollision(sf::Color::Black);
    Collision rocklandCollision{sf::Color::Black};
    Collision junglelandCollision{sf::Color::Black};
    Collision collision; //Bounds checking

    //Audio collision boxes
    Collision grasslandGrass(sf::Color::Green);
    Collision grasslandShrubs(sf::Color::Blue);
    Collision farmlandGrass{sf::Color::White};
    Collision farmlandRoad{sf::Color::Yellow};
    Collision farmlandCropAndShrub{sf::Color::Red};
    Collision rocklandDirt{sf::Color::Magenta};
    Collision rocklandGrass{sf::Color::Cyan};
    Collision junglelandGrass{sf::Color::Blue};
    Collision junglelandShrub{sf::Color::Cyan};

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

    if (!rockland.loadNewLevel("map/rockland.map", "textures/level/rockland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: rockland.map";
        return -1;
    }

    if (!animPropsWorld.loadNewLevel("map/animprops.map", "textures/level/animatedprops.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: animprops.map";
        return -1;
    }

    if (!jungleland.loadNewLevel("map/jungleland.map", "textures/level/jungleland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: jungleland.map";
        return -1;
    }

    //We need a sprite to display our cloud background image
    sf::Sprite cloudsBackground;
    sf::Texture cloudsTexture;
    cloudsTexture.setRepeated(true);
    cloudsTexture.loadFromFile("textures/level/clouds.png");
    cloudsBackground.setTexture(cloudsTexture);
    cloudsBackground.setTextureRect(sf::IntRect(0, 0, config.getScreenWidth() * 8,
                                                   config.getScreenHeight() * 8));
    cloudsBackground.setPosition(-1000, -1000);

    //Init the player
    player.boundingBoxSprite.setPosition(64, 64);
    player.setTexture("textures/entity/player.anim.png");
    player.body.setTextureRect(sf::IntRect(0, 0, 22, 32));

    //Init the camera
    camera.setCamCenter(player.boundingBoxSprite.getPosition());

    //Position our worlds
    rockland.setPosition(512, 0);
    farmland.setPosition(0, -512);
    animPropsWorld.setPosition(0, -512);
    jungleland.setPosition(512, -512);

    //Position the animated prop
    animprops.windmill.setPosition(128, -192);

    //Position collision boxes
    grasslandCollision.positionCollisionBoxes(grassland.currentLevel, config.objectsInGrassland, 0, 0);
    farmlandCollision.positionCollisionBoxes(farmland.currentLevel, config.objectsInFarmland, 0, -512);
    animPropsCollision.positionCollisionBoxes(animPropsWorld.currentLevel, config.objectsInAnimprop, 0, -512);
    rocklandCollision.positionCollisionBoxes(rockland.currentLevel, config.objectsInRockland, 512, 0);
    junglelandCollision.positionCollisionBoxes(jungleland.currentLevel, config.objectsInJungleland, 512, -512);

    //Audio collision boxes
    grasslandGrass.positionCollisionBoxes(grassland.currentLevel, config.grasslandGrass, 0, 0);
    grasslandShrubs.positionCollisionBoxes(grassland.currentLevel, config.grasslandShrubs, 0, 0);
    farmlandGrass.positionCollisionBoxes(farmland.currentLevel, config.farmlandGrass, 0, -512);
    farmlandRoad.positionCollisionBoxes(farmland.currentLevel, config.farmlandRoad, 0, -512);
    farmlandCropAndShrub.positionCollisionBoxes(farmland.currentLevel, config.farmlandCropAndShrub, 0, -512);
    rocklandDirt.positionCollisionBoxes(rockland.currentLevel, config.rocklandDirt, 512, 0);
    rocklandGrass.positionCollisionBoxes(rockland.currentLevel, config.rocklandGrass, 512, 0);
    junglelandGrass.positionCollisionBoxes(jungleland.currentLevel, config.junglelandGrass, 512, -512);
    junglelandShrub.positionCollisionBoxes(jungleland.currentLevel, config.junglelandShrub, 512, -512);

    //Register our sounds with the sound manager.
    //Footsteps sounds, to go into bnkFootsteps (defined in SoundManager.h).
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps01.wav", "footsteps01");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps02.wav", "footsteps02");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps03.wav", "footsteps03");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps04.wav", "footsteps04");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps05.wav", "footsteps05");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps06.wav", "footsteps06");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps07.wav", "footsteps07");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps08.wav", "footsteps08");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps/footsteps09.wav", "footsteps09");

    //Game loop.
    while (isRunning) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
            //Check for player.isActive to ensure we only die/spawn once.
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player.isActive) {
                player.killPlayer();
            }
            player.handlePlayerEvents(event);
            mouse.handleMouseEvents(event, window);
        }
        player.body.setOrigin(11, 27);
        player.body.setRotation(90 + mouse.getMouseAngle());

        /*
        for (int i = 0; i < grasslandCollision.MAX_COLLISION_BOXES; ++i) {
            if (grasslandCollision.collVector[i]->isTouching) {
                grassland.changeLevelData(i, 9);
                grasslandCollision.collVector[i]->bbox.setPosition(-9999, 9999);
                std::cout << grasslandCollision.collVector[i]->id << "\n";
            }
        }
        */

        //Check our audio collision
        if (player.isActive) {
            if (player.checkAudioCollsion(grasslandGrass) && player.isWalking) {
                int randomNumber = rand() % 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(grasslandShrubs) && player.isWalking) {
                int randomNumber = rand() % (6 - 3) + 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(farmlandGrass) && player.isWalking) {
                int randomNumber = rand() % 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(farmlandCropAndShrub) && player.isWalking) {
                int randomNumber = rand() % (6 - 3) + 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(farmlandRoad) && player.isWalking) {
                int randomNumber = rand() % (9 - 6) + 6;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(rocklandGrass) && player.isWalking) {
                int randomNumber = rand() % (6 - 3) + 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(rocklandDirt) && player.isWalking) {
                int randomNumber = rand() % (9 - 6) + 6;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(junglelandGrass) && player.isWalking) {
                int randomNumber = rand() % 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(junglelandShrub) && player.isWalking) {
                int randomNumber = rand() % (6 - 3) + 3;
                soundmngr.playFootsteps(randomNumber);
            }

        }

        //Regular collision checking
        player.checkCollision(farmlandCollision, camera);
        player.checkCollision(animPropsCollision, camera);
        player.checkCollision(grasslandCollision, camera);
        player.checkCollision(rocklandCollision, camera);
        player.checkCollision(junglelandCollision, camera);

        //Clear, move, and draw
        window.clear();
        window.draw(cloudsBackground);
        window.setView(camera.getCamera());

        //Draw the worlds
        window.draw(farmland);
        window.draw(grassland);
        window.draw(rockland);
        window.draw(jungleland);

        //Draw the animated sprite on top of the world
        animprops.animate();
        window.draw(animPropsWorld);
        window.draw(animprops.windmill);

        //Draw collision boxes
        /*
        for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
            window.draw(grasslandCollision.collVector[i]->bbox);
            window.draw(grasslandGrass.collVector[i]->bbox);
            window.draw(grasslandShrubs.collVector[i]->bbox);
            window.draw(farmlandCollision.collVector[i]->bbox);
            window.draw(farmlandGrass.collVector[i]->bbox);
            window.draw(farmlandRoad.collVector[i]->bbox);
            window.draw(farmlandCropAndShrub.collVector[i]->bbox);
            window.draw(animPropsCollision.collVector[i]->bbox);
            window.draw(rocklandCollision.collVector[i]->bbox);
            window.draw(rocklandDirt.collVector[i]->bbox);
            window.draw(rocklandGrass.collVector[i]->bbox);
            window.draw(junglelandCollision.collVector[i]->bbox);
            window.draw(junglelandGrass.collVector[i]->bbox);
            window.draw(junglelandShrub.collVector[i]->bbox);
            window.draw(player.boundingBoxSprite);
        }
        //*/

        //Animate and render the player,
        //above the collision boxes.
        if (player.isActive) {
            player.animate();
            player.movePlayer();
            camera.moveCam(player.position.x, player.position.y);
            window.draw(player.body);
        }

        //Draw shader testing stuff and fluffs.
        //*
        if (!player.isActive) {
            shader.deathShape.setPosition(player.body.getPosition().x - 100,
                                        player.body.getPosition().y - 100);
            player.respawnText.setPosition(player.body.getPosition().x - 75,
                                        player.body.getPosition().y - 75);
            shader.animate(true);
            window.draw(shader.deathShape, &shader.deathShader);
            window.draw(player.respawnText);
            //Automatically respawn
            static float timer = player.spawnTime;
            timer -= 0.1f;
            if (timer < 0.0f) {
                timer =  player.spawnTime;
                int randomNumber = rand() % 10;
                player.respawn(camera, randomNumber);
            }
        } else {
            shader.animate(false);
        }
        //*/

        //Run the application
        window.display();
    }
}

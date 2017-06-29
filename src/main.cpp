#include <SFML/Graphics.hpp>
#include "../include/Config.h"
#include "../include/World.h"
#include "../include/Camera.h"
#include "../include/Player.h"
#include "../include/Collision.h"
#include "../include/AnimatedProps.h"
#include "../include/Flags.h"
#include "../include/SoundManager.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

int main()
{
    //Random numbers
    srand(time(NULL));

    //Initialize our objects
    Config config;
    Flags flagObject;
    SoundManager soundmngr;

    //Load our worlds
    World grassland;
    World farmland;
    World rockland;
    World flags;

    //Animated props
    World animPropsWorld;
    AnimatedProps animprops;

    //Store a different set of collision
    //boxes for different events.
    Collision collision(sf::Color::Black);
    Collision flagsCollision(sf::Color::Black);
    Collision grasslandCollision(sf::Color::Black);
    Collision farmlandCollision(sf::Color::Black);
    Collision animPropsCollision(sf::Color::Black);
    Collision rocklandCollision{sf::Color::Black};

    //Audio collision boxes
    Collision grasslandGrass(sf::Color::Green);
    Collision grasslandShrubs(sf::Color::Blue);
    Collision farmlandGrass{sf::Color::White};
    Collision farmlandRoad{sf::Color::Yellow};
    Collision farmlandCropAndShrub{sf::Color::Red};
    Collision rocklandDirt{sf::Color::Magenta};
    Collision rocklandGrass{sf::Color::Cyan};

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

    //Position collision boxes
    grasslandCollision.positionCollisionBoxes(grassland.currentLevel, config.objectsInGrassland);
    farmlandCollision.positionCollisionBoxes(farmland.currentLevel, config.objectsInFarmland);
    animPropsCollision.positionCollisionBoxes(animPropsWorld.currentLevel, config.objectsInAnimprop);
    flagObject.positionFlags(flagsCollision);
    rocklandCollision.positionCollisionBoxes(rockland.currentLevel, config.objectsInRockland);

    //Audio collision boxes
    grasslandGrass.positionCollisionBoxes(grassland.currentLevel, config.grasslandGrass);
    grasslandShrubs.positionCollisionBoxes(grassland.currentLevel, config.grasslandShrubs);
    farmlandGrass.positionCollisionBoxes(farmland.currentLevel, config.farmlandGrass);
    farmlandRoad.positionCollisionBoxes(farmland.currentLevel, config.farmlandRoad);
    farmlandCropAndShrub.positionCollisionBoxes(farmland.currentLevel, config.farmlandCropAndShrub);
    rocklandDirt.positionCollisionBoxes(rockland.currentLevel, config.rocklandDirt);
    rocklandGrass.positionCollisionBoxes(rockland.currentLevel, config.rocklandGrass);

    //Register our sounds with the sound manager.
    //Footsteps sounds, to go into bnkFootsteps (defined in SoundManager.h).
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps01.wav", "footsteps01");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps02.wav", "footsteps02");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps03.wav", "footsteps03");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps04.wav", "footsteps04");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps05.wav", "footsteps05");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps06.wav", "footsteps06");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps07.wav", "footsteps07");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps08.wav", "footsteps08");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "audio/footsteps09.wav", "footsteps09");

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
        flagObject.checkCollision(flagsCollision, camera, player, config);
        //Draw the specific levels
        if (config.LEVEL_STRING == "grassland") {
            //Check our audio collision
            if (player.checkAudioCollsion(grasslandGrass) && player.isWalking) {
                int randomNumber = rand() % 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(grasslandShrubs) && player.isWalking) {
                int randomNumber = rand() % (6 - 3) + 3;
                soundmngr.playFootsteps(randomNumber);
            }
            //Object collision
            player.checkCollision(grasslandCollision, camera);
            //Draw!
            window.draw(grassland);
        }

        if (config.LEVEL_STRING == "farmland") {
            //Check the audio collsion.
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
            //Regular collision
            player.checkCollision(farmlandCollision, camera);
            player.checkCollision(animPropsCollision, camera);
            window.draw(farmland);
            //Position the animated prop
            animprops.windmill.setPosition(128, 320);
            animprops.animate();
            //Draw the sprite on top of the world
            window.draw(animPropsWorld);
            window.draw(animprops.windmill);
        }

        if (config.LEVEL_STRING == "rockland") {
            if (player.checkAudioCollsion(rocklandGrass) && player.isWalking) {
                int randomNumber = rand() % (6 - 3) + 3;
                soundmngr.playFootsteps(randomNumber);
            }
            if (player.checkAudioCollsion(rocklandDirt) && player.isWalking) {
                int randomNumber = rand() % (9 - 6) + 6;
                soundmngr.playFootsteps(randomNumber);
            }
            player.checkCollision(rocklandCollision, camera);
            window.draw(rockland);
        }
        //Draw collision boxes
        /*
        for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
            window.draw(*collision.collVector[i]);
            window.draw(*flagsCollision.collVector[i]);
            if (config.LEVEL_STRING == "grassland") {
                window.draw(*grasslandCollision.collVector[i]);
                window.draw(*grasslandGrass.collVector[i]);
                window.draw(*grasslandShrubs.collVector[i]);
            }
            if (config.LEVEL_STRING == "farmland") {
                window.draw(*farmlandCollision.collVector[i]);
                window.draw(*farmlandGrass.collVector[i]);
                window.draw(*farmlandRoad.collVector[i]);
                window.draw(*farmlandCropAndShrub.collVector[i]);
                window.draw(*animPropsCollision.collVector[i]);
            }
        }
        //*/
        //Always draw our flags
        window.draw(flags);
        //Animate and render the player
        player.animate();
        player.movePlayer();
        camera.moveCam(player.position.x, player.position.y);
        window.draw(player.sprite);
        //Run the application
        window.display();
    }
    return 0;
}

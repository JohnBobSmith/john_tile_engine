#include <SFML/Graphics.hpp>
#include "../include/Config.h"
#include "../include/World.h"
#include "../include/Camera.h"
#include "../include/Player.h"
#include "../include/Collision.h"
#include "../include/AnimatedProps.h"
#include "../include/SoundManager.h"
#include "../include/Shader.h"
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

    //Load our worlds
    World grassland;
    World farmland;
    World rockland;

    //Animated props
    World animPropsWorld;
    AnimatedProps animprops;

    //Store a different set of collision
    //boxes for different events.
    Collision grasslandCollision(sf::Color::Black);
    Collision farmlandCollision(sf::Color::Black);
    Collision animPropsCollision(sf::Color::Black);
    Collision rocklandCollision{sf::Color::Black};
    Collision collision; //Bounds checking

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

    //Position our worlds
    rockland.setPosition(512, 0);
    farmland.setPosition(0, -512);
    animPropsWorld.setPosition(0, -512);

    //Position the animated prop
    animprops.windmill.setPosition(128, -192);

    //Position collision boxes
    grasslandCollision.positionCollisionBoxes(grassland.currentLevel, config.objectsInGrassland, 0, 0);
    farmlandCollision.positionCollisionBoxes(farmland.currentLevel, config.objectsInFarmland, 0, -512);
    animPropsCollision.positionCollisionBoxes(animPropsWorld.currentLevel, config.objectsInAnimprop, 0, -512);
    rocklandCollision.positionCollisionBoxes(rockland.currentLevel, config.objectsInRockland, 512, 0);

    //Audio collision boxes
    grasslandGrass.positionCollisionBoxes(grassland.currentLevel, config.grasslandGrass, 0, 0);
    grasslandShrubs.positionCollisionBoxes(grassland.currentLevel, config.grasslandShrubs, 0, 0);
    farmlandGrass.positionCollisionBoxes(farmland.currentLevel, config.farmlandGrass, 0, -512);
    farmlandRoad.positionCollisionBoxes(farmland.currentLevel, config.farmlandRoad, 0, -512);
    farmlandCropAndShrub.positionCollisionBoxes(farmland.currentLevel, config.farmlandCropAndShrub, 0, -512);
    rocklandDirt.positionCollisionBoxes(rockland.currentLevel, config.rocklandDirt, 512, 0);
    rocklandGrass.positionCollisionBoxes(rockland.currentLevel, config.rocklandGrass, 512, 0);

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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                player.isActive = false;
                shader.deathShape.setPosition(player.sprite.getPosition().x, player.sprite.getPosition().y);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                player.isActive = true;
            }
        }

        //Clear, move, and draw
        window.clear();
        window.draw(cloudsBackground);
        window.setView(camera.getCamera());

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
        }

        //Regular collision checking
        player.checkCollision(farmlandCollision, camera);
        player.checkCollision(animPropsCollision, camera);
        player.checkCollision(grasslandCollision, camera);
        player.checkCollision(rocklandCollision, camera);

        //Draw the worlds
        window.draw(farmland);
        window.draw(grassland);
        window.draw(rockland);

        //Draw the animated sprite on top of the world
        animprops.animate();
        window.draw(animPropsWorld);
        window.draw(animprops.windmill);

        //Draw collision boxes
        /*
        for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
            window.draw(*collision.collVector[i]);
            window.draw(*grasslandCollision.collVector[i]);
            window.draw(*grasslandGrass.collVector[i]);
            window.draw(*grasslandShrubs.collVector[i]);
            window.draw(*farmlandCollision.collVector[i]);
            window.draw(*farmlandGrass.collVector[i]);
            window.draw(*farmlandRoad.collVector[i]);
            window.draw(*farmlandCropAndShrub.collVector[i]);
            window.draw(*animPropsCollision.collVector[i]);
            window.draw(*rocklandCollision.collVector[i]);
            window.draw(*rocklandDirt.collVector[i]);
            window.draw(*rocklandGrass.collVector[i]);
        }
        //*/

        //Animate and render the player,
        //above the collision boxes.
        if (player.isActive) {
            player.animate();
            player.movePlayer();
            camera.moveCam(player.position.x, player.position.y);
            window.draw(player.sprite);
        }

        //Draw shader testing stuff and fluffs.
        /*
        if (!player.isActive) {
            window.draw(shader.deathShape, &shader.deathShader);
        }
        //*/

        //Run the application
        window.display();
    }
    return 0;
}

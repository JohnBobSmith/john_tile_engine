#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include "../include/AnimatedProps.h"
#include "../include/Bullet.h"
#include "../include/Camera.h"
#include "../include/Collision.h"
#include "../include/Config.h"
#include "../include/Font.h"
#include "../include/Mouse.h"
#include "../include/Player.h"
#include "../include/Shader.h"
#include "../include/SoundManager.h"
#include "../include/Weapon.h"
#include "../include/World.h"
#include "../include/ResuplySystem.h"
#include "../include/Ai.h"
#include "../include/HealthBar.h"

int main()
{
    //Random numbers
    srand(time(NULL));

    //Initialize our objects
    Config config;
    SoundManager soundmngr;
    Shader shader;
    Mouse mouse;
    Font font;
    HealthBar hpbar;

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

    //Our weapons
    Bullet bullet;
    
    //Our resuply system
    ResuplySystem resuplysystem;
    
    //LMG
    sf::Time lmgRof = sf::milliseconds(100);
    sf::Time lmgReloadTime = sf::milliseconds(750);
    Weapon lmg("../textures/weapons/lmg.png", 20, 150, 30, lmgRof, lmgReloadTime, "lmg");

    //Are we running the game?
    bool isRunning = true;

    //Load our levels
    if (!grassland.loadNewLevel("../map/grassland.map", "../textures/level/grassland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: grassland.map";
        return -1;
    }

    if (!farmland.loadNewLevel("../map/farmland.map", "../textures/level/farmland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: farmland.map";
        return -1;
    }

    if (!rockland.loadNewLevel("../map/rockland.map", "../textures/level/rockland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: rockland.map";
        return -1;
    }

    if (!animPropsWorld.loadNewLevel("../map/animprops.map", "../textures/level/animatedprops.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: animprops.map";
        return -1;
    }

    if (!jungleland.loadNewLevel("../map/jungleland.map", "../textures/level/jungleland.png")) {
        std::cerr << "FATAL ERROR: Missing required mapfile: jungleland.map";
        return -1;
    }

    //We need a sprite to display our cloud background image
    sf::Sprite cloudsBackground;
    sf::Texture cloudsTexture;
    cloudsTexture.setRepeated(true);
    cloudsTexture.loadFromFile("../textures/level/clouds.png");
    cloudsBackground.setTexture(cloudsTexture);
    cloudsBackground.setTextureRect(sf::IntRect(0, 0, config.getScreenWidth() * 8,
                                                   config.getScreenHeight() * 8));
    cloudsBackground.setPosition(-1000, -1000);

    //Init the player
    if (!player.loadTexture()) {
        return -1; //Error missing required texture files.
    }
    
    //Setup the player's position and texture
    player.boundingBox.setPosition(64, 64);
    player.body.setTextureRect(sf::IntRect(0, 0, 22, 32));

    //Init our fonts
    if (!font.load()) {
        return -1; //Error missing required font files.
    }

    //Init the camera
    camera.setCamCenter(player.boundingBox.getPosition());

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
    //Footsteps sounds
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps01.wav", "footstep01");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps02.wav", "footstep02");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps03.wav", "footstep03");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps04.wav", "footstep04");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps05.wav", "footstep05");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps06.wav", "footstep06");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps07.wav", "footstep07");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps08.wav", "footstep08");
    soundmngr.registerNewSound(soundmngr.bnkFootsteps, "../audio/footsteps/footsteps09.wav", "footstep09");
    //Our spawn/death sounds
    soundmngr.registerNewSound(soundmngr.bnkSpawnEffects, "../audio/effects/deathrespawn/respawn.wav", "respawn");
    soundmngr.registerNewSound(soundmngr.bnkSpawnEffects, "../audio/effects/deathrespawn/death.wav", "death");
    //Our weapon shooting and handling sounds
    soundmngr.registerNewSound(soundmngr.bnkWeaponEffects, "../audio/effects/weapons/outOfAmmo.wav", "outOfAmmo");
    soundmngr.registerNewSound(soundmngr.bnkWeaponEffects, "../audio/effects/weapons/lmg/lmgFire.wav", "lmgFire");
    soundmngr.registerNewSound(soundmngr.bnkWeaponEffects, "../audio/effects/weapons/lmg/lmgReload.wav", "lmgReload");

    //Setup the ammo counter font
    if (lmg.isEquipped) {
        font.ammoCounterText.setString(std::to_string(lmg.ammoInMagazine));
        font.maxAmmoCounterText.setString("/" + std::to_string(lmg.maxAmmo));
    }
    
    //Initialize SFML
    sf::Event event;
    sf::RenderWindow window(sf::VideoMode(config.getScreenWidth(),\
                                        config.getScreenHeight()),\
                                        config.getAppName());
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    //Game loop.
    while (isRunning) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                isRunning = false;
            }
            player.handlePlayerEvents(event);
            mouse.update(event, window);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (lmg.ammoInMagazine <= 0) {
                soundmngr.playSoundByID(soundmngr.bnkWeaponEffects, "outOfAmmo");
            }
            if (lmg.isEquipped && lmg.canFire) {
                bullet.shoot(soundmngr, lmg, mouse.getMouseAngle());
                font.ammoCounterText.setString(std::to_string(lmg.ammoInMagazine));
                font.maxAmmoCounterText.setString("/" + std::to_string(lmg.maxAmmo));   
            }

        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (lmg.isEquipped /*&& lmg.maxAmmo > 0*/) {
                lmg.reload(soundmngr);
                font.ammoCounterText.setString(std::to_string(lmg.ammoInMagazine));
                font.maxAmmoCounterText.setString("/" + std::to_string(lmg.maxAmmo));             
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            player.killPlayer(soundmngr);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        	player.health -= 10.0f;
        }
        
        //Kill the player if we have < 0 health
        if (player.health <= 0) {
        	player.killPlayer(soundmngr);
        }

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
        
	    //Bullet collision checking
        bullet.checkBulletCollision(farmlandCollision);
        bullet.checkBulletCollision(grasslandCollision);
        bullet.checkBulletCollision(rocklandCollision);
        bullet.checkBulletCollision(junglelandCollision);
        bullet.checkBulletCollision(animPropsCollision);
        
        //COLLISION TESTING - RESUPLY SYSTEM
        if (resuplysystem.checkAmmoBoxCollision(collision, player)) {
            resuplysystem.ammoBox.setOutlineColor(sf::Color::White);
            resuplysystem.resuplyAmmo(lmg);
            font.ammoCounterText.setString(std::to_string(lmg.ammoInMagazine));
            font.maxAmmoCounterText.setString("/" + std::to_string(lmg.maxAmmo)); 
        } else {
            resuplysystem.ammoBox.setOutlineColor(sf::Color::Black);
        }
        
        if (resuplysystem.checkHealthBoxCollision(collision, player)) {
            resuplysystem.healthBox.setOutlineColor(sf::Color::White);
            resuplysystem.resuplyHealth(player);        
        } else {
        	resuplysystem.healthBox.setOutlineColor(sf::Color::Black);
        }
        
        //COLLISION TESTING - CIRCLE COLLISION DETECTION
        sf::CircleShape circle(50);
        circle.setPosition(100, -100);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(-2);
        circle.setOutlineColor(sf::Color::Blue);
        
        if (collision.checkCircleToRectCollision(circle, player.boundingBox.getPosition().x,
                                                         player.boundingBox.getPosition().y, 
                                                         player.size.x, player.size.y)) {

            circle.setOutlineColor(sf::Color::Red); 
        }

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
        }
        //*/
        //Draw the bullet collision boxes
        /*
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
            window.draw(bullet.bulletStorage[i]->bbox);
        }        
        //*/
        /*
        //Draw player collision box
        window.draw(player.boundingBox);
        //*/

        //Draw our bullets below everything else
        float xPosition = 37 * cos(mouse.getMouseAngle() * M_PI / 180);
        float yPosition = 37 * sin(mouse.getMouseAngle() * M_PI / 180);
        for (int i = 0; i < bullet.getMaxBullets(); ++i) {
            if (!bullet.bulletStorage[i]->isActive) {
                bullet.bulletStorage[i]->bulletSprite.setPosition(lmg.weapSprite.getPosition().x + xPosition,
                                                                 lmg.weapSprite.getPosition().y + yPosition);
                                                            
            }
            if (bullet.bulletStorage[i]->isActive) {
                window.draw(bullet.bulletStorage[i]->bulletSprite);
                if (bullet.bulletStorage[i]->bulletSprite.getPosition().x > 500 + player.body.getPosition().x) {
                    bullet.bulletStorage[i]->isActive = false;
                }
                if (bullet.bulletStorage[i]->bulletSprite.getPosition().x < -500 - player.body.getPosition().x) {
                    bullet.bulletStorage[i]->isActive = false;
                }
                if (bullet.bulletStorage[i]->bulletSprite.getPosition().y > 500 + player.body.getPosition().y) {
                    bullet.bulletStorage[i]->isActive = false;
                }
                if (bullet.bulletStorage[i]->bulletSprite.getPosition().y < -500 + player.body.getPosition().y) {
                    bullet.bulletStorage[i]->isActive = false;
                }
            }
        }

        //Animate and render the player,
        //above the collision boxes.
        if (player.isActive) {
            player.animateLegs();
            player.movePlayer();
            camera.moveCam(player.position.x, player.position.y);
            player.body.setRotation(90 + mouse.getMouseAngle());
            player.legs.setRotation(90 + mouse.getMouseAngle());
            player.legs.setPosition(player.body.getPosition().x, player.body.getPosition().y);
            window.draw(player.legs);
            //Put our weapons above the legs but below the player body.
            if (lmg.isEquipped) {
                lmg.weapSprite.setPosition(player.body.getPosition().x, player.body.getPosition().y);
                lmg.weapSprite.setOrigin(6, 37);
                lmg.weapSprite.setRotation(90 + mouse.getMouseAngle());
                window.draw(lmg.weapSprite);
            }
            //Draw the body.
            window.draw(player.body);
            
            //Move our text to the correct possition
            font.ammoCounterText.setPosition(player.body.getPosition().x + 25, player.body.getPosition().y + 50);
            font.maxAmmoCounterText.setPosition(player.body.getPosition().x + 50, player.body.getPosition().y + 60);
        	font.hpBarText.setPosition(player.body.getPosition().x - 108, player.body.getPosition().y + 50);
			
			//Draw our HUD elements
			window.draw(font.ammoCounterText);
			window.draw(font.maxAmmoCounterText); 
			window.draw(hpbar.healthBar);
			window.draw(font.hpBarText);
        }
        
        /**UPDATE EVERYTHING HERE**/

        //Move our bullets
        bullet.move();
        
        //Update weapon parameters
        lmg.update(player);

        //Update misc. player functions
        player.update();
        
        //Update the status of our health bar
        hpbar.update(player);

        //Player respawn and shader work
        //*
        if (!player.isActive) {
            shader.deathShape.setPosition(player.body.getPosition().x - 100,
                                        player.body.getPosition().y - 100);
            font.respawnText.setPosition(player.body.getPosition().x - 75,
                                        player.body.getPosition().y - 75);
            shader.animate(true);
            window.draw(shader.deathShape, &shader.deathShader);
            window.draw(font.respawnText);
            //Automatically respawn
            int randomNumber = rand() % 10;
            player.respawn(camera, soundmngr, randomNumber);
        } else {
            shader.animate(false);
        }
        //*/

        //DRAW OUR COLLISION TESTS
        window.draw(circle); 
        window.draw(resuplysystem.ammoBox); 
        window.draw(resuplysystem.healthBox);
        
        //Run the application
        window.display();
    }
}

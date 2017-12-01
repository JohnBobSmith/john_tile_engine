#include "../include/Player.h"
#include <iostream>
#include <string>
#include "../include/Camera.h"
#include "../include/Collision.h"
#include "../include/SoundManager.h"

Player::Player()
{
    //Initialize our base values
    keyCounter = 0;
    isActive = true;
    isWalking = false;
    isReloading = false;
    isPlayingRespawnSound = false;
    position.x = 32;
    position.y = 32;
    velocity.x = 0;
    velocity.y = 0;
    maxVelocity = 1;
    size.x = 19;
    size.y = 19;
    health = 100.0f;
    startingHealth = health;
    boundingBox.setSize(sf::Vector2f(size.x, size.y));
    boundingBox.setFillColor(sf::Color::White);
    spawnTime = respawnTime;

    //Setup our spawn points.
    for (int i = 0; i < MAX_SPAWN_POINTS; ++i) {
        spawnPoints.push_back(sf::Vector2f(0, 0));
    }
    spawnPoints[0].x = 50;
    spawnPoints[0].y = 50;
    spawnPoints[1].x = 230;
    spawnPoints[1].y = -460;
    spawnPoints[2].x = 774;
    spawnPoints[2].y = -284;
    spawnPoints[3].x = 945;
    spawnPoints[3].y = -50;
    spawnPoints[4].x = 870;
    spawnPoints[4].y = 280;
    spawnPoints[5].x = 776;
    spawnPoints[5].y = 320;
    spawnPoints[6].x = 175;
    spawnPoints[6].y = 400;
    spawnPoints[7].x = 328;
    spawnPoints[7].y = -99;
    spawnPoints[8].x = 517;
    spawnPoints[8].y = 5;
    spawnPoints[9].x = 867;
    spawnPoints[9].y = -441;

    //Initialize our leg sprite.
    legs.setTextureRect(sf::IntRect(0, 0, 22, 32));
    legs.setOrigin(12, 22);

    //Initialize our body sprite.
    body.setOrigin(12, 22);
}

bool Player::loadTexture(std::string bodyPath)
{
    //If we cannot load the texture, error out.
    if (!bodyTexture.loadFromFile(bodyPath.c_str())) {
        std::cerr << "Error: Missing required texture file...";
        return false;
    }

    if (!legsTexture.loadFromFile("../textures/entity/player.anim_legs.png")) {
        std::cerr << "Error: Missing required texture file...";
        return false;
    }

    body.setTexture(bodyTexture);
    legs.setTexture(legsTexture);

    return true;
}

void Player::movePlayer()
{
    position.x = velocity.x;
    position.y = velocity.y;
    boundingBox.move(position);
    body.setPosition(boundingBox.getPosition().x + 11, boundingBox.getPosition().y + 11);
}

void Player::handlePlayerEvents(sf::Event event)
{
    //Switch our event type, which should be key pressed/released.
    switch(event.type)
    {
        case sf::Event::KeyPressed:
            //Then determine which key we pressed.
            switch(event.key.code) 
            {
            //Do something with that information, repeat.
            case sf::Keyboard::W:
                velocity.y -= maxVelocity;
                keyCounter += 1;
                isWalking = true;    
                break;
            case sf::Keyboard::S:
                velocity.y += maxVelocity;
                keyCounter += 1;
                isWalking = true;
                break;
            case sf::Keyboard::A:
                velocity.x -= maxVelocity;
                keyCounter += 1;
                isWalking = true;
                break;
            case sf::Keyboard::D:
                velocity.x += maxVelocity;
                keyCounter += 1;
                isWalking = true;
                break;
            default:
                //Do not handle other kinds of events.
                break;
            }
        break; //case sf::Event::KeyPressed:
        
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
            case sf::Keyboard::W:
                velocity.y += maxVelocity;
                keyCounter -= 1;
                if (keyCounter <= 0) {
                    isWalking = false;
                }
                break;
            case sf::Keyboard::S:
                velocity.y -= maxVelocity;
                keyCounter -= 1;
                if (keyCounter <= 0) {
                    isWalking = false;
                }
                break;
            case sf::Keyboard::A:
                velocity.x += maxVelocity;
                keyCounter -= 1;
                if (keyCounter <= 0) {
                    isWalking = false;
                }
                break;
            case sf::Keyboard::D:
                velocity.x -= maxVelocity;
                keyCounter -= 1;
                if (keyCounter <= 0) {
                    isWalking = false;
                }
                break;
            default:
                //Do not handle other kinds of events.
                break;
            }
        break; //case sf::Event::KeyReleased:
        
        default:
            //Do not handle other kinds of events.
            break;
    }
}

void Player::animateLegs()
{
    static int counter = 0;
    static sf::Time timer = sf::milliseconds(50);
    timer -= sf::milliseconds(10);
    if (isWalking) {
        if (timer.asMilliseconds() <= 0) {
            //Cycle through our sprite sheet
            legs.setTextureRect(sf::IntRect(counter, 0, 22, 32));
            timer = sf::milliseconds(50);
        }
        counter += 22; //22 is the width of one sprite on the sheet
        //If we reached the end of the sheet, reset.
        if (counter == 88) {
            counter = 0;
        }
    }
}

void Player::animateReload()
{
    static int counter = 0;
    static sf::Time timer = sf::milliseconds(50);
    timer -= sf::milliseconds(10);
    if (timer.asMilliseconds() <= 0) {
        //Cycle through our sprite sheet
        body.setTextureRect(sf::IntRect(counter, 32, 22, 32));
        timer = sf::milliseconds(50);
    }
    counter += 22; //22 is the width of one sprite on the sheet
    //If we reached the end of the sheet, reset.
    if (counter == 66) {
        counter = 0;
    }  
}

bool Player::checkCollision(Collision &collision, Camera &camera)
{
    //If there is a collision, move the player back.
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(boundingBox.getPosition().x,
                                         boundingBox.getPosition().y,
                                         size.x, size.y, //Players size
                                         collision.collVector[i]->bbox.getPosition().x,
                                         collision.collVector[i]->bbox.getPosition().y,
                                         collision.collVector[i]->bbox.getSize().x,
                                         collision.collVector[i]->bbox.getSize().y)) {

            collision.collVector[i]->isTouching = true;
            if (position.x == -1) {
                boundingBox.move(1, 0);
            }
            if (position.x == 1) {
                boundingBox.move(-1, 0);
            }
            if (position.y == 1) {
                boundingBox.move(0, -1);
            }
            if (position.y == -1) {
                boundingBox.move(0, 1);
            }
            //Update the camera
            camera.setCamCenter(sf::Vector2f(boundingBox.getPosition().x,
                                           boundingBox.getPosition().y));

            //Collided
            return true;
        } else {
            //Reset isTouching
            collision.collVector[i]->isTouching = false;
        }
    }
    //Did not collide
    return false;
}

bool Player::checkAudioCollsion(Collision &collision)
{
    for (int i = 0; i < collision.MAX_COLLISION_BOXES; ++i) {
        if (collision.checkAABBcollision(boundingBox.getPosition().x,
                                         boundingBox.getPosition().y,
                                         size.x, size.y, //Players size
                                         collision.collVector[i]->bbox.getPosition().x,
                                         collision.collVector[i]->bbox.getPosition().y,
                                         collision.collVector[i]->bbox.getSize().x,
                                         collision.collVector[i]->bbox.getSize().y)) {
            //Collided
            return true;
        }
    }
    //Did not collide
    return false;
}

void Player::applyDamage(int ammount, SoundManager &soundmngr)
{
    health -= ammount;
    if (health <= 0) {
        killPlayer(soundmngr);
    }
}

void Player::killPlayer(SoundManager &soundmngr)
{
    if (!isPlayingRespawnSound) {
        soundmngr.playSoundByID(soundmngr.bnkSpawnEffects, "death");
        isPlayingRespawnSound = true;
    }
    health = -999;
    isActive = false;
}

void Player::respawn(Camera &camera, SoundManager &soundmngr, int randomNumber)
{
    spawnTime -= sf::milliseconds(10);
    if (spawnTime.asMilliseconds() <= 0) {
        spawnTime = respawnTime;
        soundmngr.playSoundByID(soundmngr.bnkSpawnEffects, "respawn");
        health = 100;
        isActive = true;
        isPlayingRespawnSound = false;

        //Randomly spawn the player, then update the camera.
        boundingBox.setPosition(spawnPoints[randomNumber]);
        camera.setCamCenter(sf::Vector2f(boundingBox.getPosition().x, boundingBox.getPosition().y));
    }
}

void Player::update()
{   
    //Animate the player's reload
    if (isReloading) {
        animateReload();
    } else {
        //Crude but effective
        //Manually reset the animation to the starting position.
        body.setTextureRect(sf::IntRect(66, 32, 22, 32));
    }
    
    //If not walking, reset the animation
    if (!isWalking) {
    	legs.setTextureRect(sf::IntRect(0, 32, 22, 32));
    }
}

